#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <math.h>

// Mapeamento de Pinos da PCB (Revisão Blueprint Core v2.0)
#define PIN_DAC1_WAVE     25
#define PIN_DAC2_BIAS     26
#define PIN_ADC_MUX_SIG   36
#define PIN_ADC_NTC       39

#define PIN_PWM_FAN       18
#define PIN_PWM_HEATER    19
#define PIN_I2C_SDA       21
#define PIN_I2C_SCL       22

// Endereços I2C dos Expansores de 32 Portas Estocásticas
#define MCP1_ADDR         0x20
#define MCP2_ADDR         0x21
#define MCP_IODIRA        0x00
#define MCP_IODIRB        0x01
#define MCP_GPIOA         0x12
#define MCP_GPIOB         0x13

#define SYNC_BYTE         0xAA

const int mux_sel_pins[4] = {14, 27, 32, 33};

// Variáveis Voláteis Compartilhadas entre Core 0 e Core 1
volatile uint8_t  g_amp_dac1   = 100;
volatile uint8_t  g_bias_dac2  = 128; // 1.65V (V_rest)
volatile uint8_t  g_freq_step  = 8;
volatile uint16_t g_leaves[16];
volatile uint16_t g_ntc_raw    = 2048;

uint8_t sine_lut[256];

void write_mcp_reg(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void update_32_io_bitstream(uint32_t bitstream) {
  // Atualiza MCP23017 #1 (Portas IO_00 a IO_15)
  Wire.beginTransmission(MCP1_ADDR);
  Wire.write(MCP_GPIOA);
  Wire.write((uint8_t)(bitstream & 0xFF));
  Wire.write((uint8_t)((bitstream >> 8) & 0xFF));
  Wire.endTransmission();

  // Atualiza MCP23017 #2 (Portas IO_16 a IO_31)
  Wire.beginTransmission(MCP2_ADDR);
  Wire.write(MCP_GPIOA);
  Wire.write((uint8_t)((bitstream >> 16) & 0xFF));
  Wire.write((uint8_t)((bitstream >> 24) & 0xFF));
  Wire.endTransmission();
}

// CORE 0: Geração Contínua de Onda e Leitura Analógica das 16 Folhas (TL074)
void TaskCore0_AnalogMesh(void *pvParameters) {
  uint8_t phase = 0;
  uint8_t ch = 0;

  for (;;) {
    // 1. Injeta a onda senoidal escalada no Tronco NE5532 (GPIO25) e o Bias no GPIO26
    uint8_t wave = 128 + ((int16_t)(sine_lut[phase] - 128) * g_amp_dac1) / 255;
    dacWrite(PIN_DAC1_WAVE, wave);
    dacWrite(PIN_DAC2_BIAS, g_bias_dac2);
    phase += g_freq_step;

    // 2. Lê a folha atual no ADC1 (12-bits: 0 a 4095) e avança o MUX CD74HC4067
    g_leaves[ch] = analogRead(PIN_ADC_MUX_SIG);
    ch = (ch + 1) & 0x0F;
    for (int b = 0; b < 4; b++) {
      digitalWrite(mux_sel_pins[b], (ch >> b) & 0x01);
    }

    // 3. A cada ciclo de 16 folhas, amostra o Termistor NTC 10k no GPIO39
    if (ch == 0) {
      g_ntc_raw = analogRead(PIN_ADC_NTC);
    }

    delayMicroseconds(10); // Amostragem a ~100 kHz
  }
}

// CORE 1: Ponte Transacional USB (2 Mbps) + Atuadores PWM + Barramento I2C
void TaskCore1_USBOrchestrator(void *pvParameters) {
  uint8_t rx_buf[10];
  uint8_t tx_buf[34];

  for (;;) {
    // Aguarda Frame de 11 Bytes vindo do Orquestrador Python:
    // [0xAA, Amp_DAC1, Bias_DAC2, Freq, PWM_Cooler, PWM_Heater, IO_B3, IO_B2, IO_B1, IO_B0, Checksum]
    if (Serial.available() >= 11) {
      if (Serial.read() == SYNC_BYTE) {
        Serial.readBytes(rx_buf, 10);

        g_amp_dac1  = rx_buf[0];
        g_bias_dac2 = rx_buf[1];
        g_freq_step = rx_buf[2];

        // Aciona MOSFETs Q2 (Cooler) e Q1 (Resistor de Aquecimento 22R)
        analogWrite(PIN_PWM_FAN,    rx_buf[3]);
        analogWrite(PIN_PWM_HEATER, rx_buf[4]);

        // Reconstrói os 32 bits estocásticos e envia para os 2x MCP23017 via I2C
        uint32_t io_bits = ((uint32_t)rx_buf[5] << 24) |
                           ((uint32_t)rx_buf[6] << 16) |
                           ((uint32_t)rx_buf[7] << 8)  |
                           ((uint32_t)rx_buf[8]);
        update_32_io_bitstream(io_bits);

        // Aguarda propagação física da nova onda pelos capacitores dos TL074
        delayMicroseconds(160);

        // Empacota as 16 Folhas + 1 NTC (34 Bytes em Big-Endian) e responde via USB
        for (int i = 0; i < 16; i++) {
          uint16_t val = g_leaves[i];
          tx_buf[i * 2]     = (val >> 8) & 0xFF;
          tx_buf[i * 2 + 1] = val & 0xFF;
        }
        uint16_t ntc = g_ntc_raw;
        tx_buf[32] = (ntc >> 8) & 0xFF;
        tx_buf[33] = ntc & 0xFF;

        Serial.write(tx_buf, 34);
      }
    } else {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
  }
}

void setup() {
  // Desativa rádios para eliminar ruído no ADC e liberar corrente na PCB
  WiFi.mode(WIFI_OFF);
  btStop();

  Serial.begin(2000000);
  analogReadResolution(12);

  for (int b = 0; b < 4; b++) pinMode(mux_sel_pins[b], OUTPUT);
  pinMode(PIN_PWM_FAN, OUTPUT);
  pinMode(PIN_PWM_HEATER, OUTPUT);

  // Inicializa Barramento I2C a 400 kHz e configura as 32 portas como SAÍDA
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000);
  write_mcp_reg(MCP1_ADDR, MCP_IODIRA, 0x00);
  write_mcp_reg(MCP1_ADDR, MCP_IODIRB, 0x00);
  write_mcp_reg(MCP2_ADDR, MCP_IODIRA, 0x00);
  write_mcp_reg(MCP2_ADDR, MCP_IODIRB, 0x00);

  for (int i = 0; i < 256; i++) {
    sine_lut[i] = (uint8_t)(128.0 + 127.0 * sin(2.0 * M_PI * i / 256.0));
  }

  xTaskCreatePinnedToCore(TaskCore0_AnalogMesh,      "AnalogMesh", 4096, NULL, 3, NULL, 0);
  xTaskCreatePinnedToCore(TaskCore1_USBOrchestrator, "USBBridge",  4096, NULL, 2, NULL, 1);
}

void loop() {}