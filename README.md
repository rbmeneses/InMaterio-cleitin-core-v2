# 🧠 Projeto Cleitin: NPU Analógica USB, Matriz Estocástica 16×16 & Hipocampo Termodinâmico

![Versão](https://img.shields.io/badge/vers%C3%A3o-3.0%20%7C%20Core%20v2.0-00f0ff?style=for-the-badge)
![Hardware](https://img.shields.io/badge/hardware-ESP32%20%7C%20NE5532%20%7C%20TL074%20%7C%20MCP23017-ffc857?style=for-the-badge)
![Backend](https://img.shields.io/badge/orquestrador-Python%20%7C%20FastAPI%20%7C%20SQLite%20WAL%20%7C%20Ollama-00ff88?style=for-the-badge)
![Frontend](https://img.shields.io/badge/interface-HTML5%20%7C%20Tailwind%20%7C%20SVG%20Bluescreen-ff6b6b?style=for-the-badge)
![Licença](https://img.shields.io/badge/licen%C3%A7a-MIT-a855f7?style=for-the-badge)

**Autor:** Ricardo Barbosa de Meneses  
**Status:** Especificação Técnica Completa, Simulador Interativo, Blueprint Vetorial e Orquestrador LLM-PCB

O **Projeto Cleitin** é uma arquitetura aberta de **Computação Neuromórfica e Estocástica *In-Materio*** que fornece um "corpo físico" e um sistema límbico/subconsciente termodinâmico para Agentes Autônomos e Modelos de Linguagem Locais (LLMs). Em vez de depender exclusivamente de algoritmos determinísticos ou geradores pseudoaleatórios em software, o agente colapsa suas decisões, modula sua criatividade e consolida memórias através da física real de **circuitos integrados de áudio analógicos (`NE5532` e `TL074`)**, **interferência de ondas** e **ruído térmico de Johnson-Nyquist**.

---

## 📑 Sumário

1. [Evolução Arquitetural (v1.0 ➔ v2.0 ➔ v3.0)](#-1-evolução-arquitetural-v10--v20--v30)
2. [Fundamentação Teórica e Modelos Matemáticos](#-2-fundamentação-teórica-e-modelos-matemáticos)
3. [Arquitetura do Agente Encarnado (0 a 5 Anos & Sistema Imunológico Psíquico)](#-3-arquitetura-do-agente-encarnado-0-a-5-anos--sistema-imunológico-psíquico)
4. [Engenharia de Hardware e Esquemático Pino a Pino (Cleitin Core v2.0)](#-4-engenharia-de-hardware-e-esquemático-pino-a-pino-cleitin-core-v20)
5. [Lista Completa de Materiais (BOM — Bill of Materials)](#-5-lista-completa-de-materiais-bom--bill-of-materials)
6. [Protocolo Binário de Alta Velocidade (USB Serial 2 Mbps)](#-6-protocolo-binário-de-alta-velocidade-usb-serial-2-mbps)
7. [Estrutura do Repositório](#-7-estrutura-do-repositório)
8. [Guia de Implantação Passo a Passo (Da Bancada à LLM)](#-8-guia-de-implantação-passo-a-passo-da-bancada-à-llm)
9. [Manual do Simulador Web & Blueprint Interativo (GitHub Pages)](#-9-manual-do-simulador-web--blueprint-interativo-github-pages)
10. [Roadmap Evolutivo](#-10-roadmap-evolutivo)

---

## 🔄 1. Evolução Arquitetural (v1.0 ➔ v2.0 ➔ v3.0)

| Fase / Versão | Substrato Físico | Topologia Neural | Comunicação | Controle de Entropia |
| :--- | :--- | :--- | :--- | :--- |
| **Cleitin v1.0** *(Conceito Original)* | CPUs x86 obsoletas (LGA 775 / Slot 1) com placa-mãe "lobotomizada" (Northbridge isolado e sem BIOS). | 3 nós paralelos operando em região *subthreshold* ($0.9\text{ V} - 1.1\text{ V}$) via pinos FSB `A[3:35]#` e `D[0:63]#`. | Wi-Fi Assíncrono (UDP Porta `5005`). | Cooler de CPU via PWM alterando o calor do die x86. |
| **Cleitin Core v2.0** *(Hardware DIP USB)* | CIs de áudio Through-Hole fáceis de soldar: **1× NE5532 (DIP-8)** + **5× TL074 (DIP-14)** + **1× CD74HC4067**. | **Árvore Dendrítica de 22 Neurônios** (1 Tronco, 4 Ramos e 16 Folhas Axoniais LIF + Loop de Ego). | **USB Serial Binário Síncrono a 2.000.000 bps** (Wi-Fi desligado para zerar ruído no ADC). | Ponte térmica unificada com Resistor Aquecedor ($22\ \Omega$/$5\text{ W}$), Micro-Cooler PWM e Termistor NTC $10\text{ k}\Omega$. |
| **Cleitin OS v3.0** *(Estação Híbrida)* | Integração da Árvore Analógica com **2× Expansores I²C MCP23017 (DIP-28)** + Orquestrador FastAPI/Ollama. | **Matriz Estocástica $16 \times 16$ (256 nós)** nos estados `{0.10, 0.25, 0.75, 1.00}` com **20% de freio inibitório GABA**. | API REST local + WebSockets/Polling + Barramento de **32 I/O em Bitstream Estocástico**. | Regimes metabólicos completos: Letargia ($<34\ ^\circ\text{C}$), Vigília ($35\ ^\circ\text{C}-45\ ^\circ\text{C}$) e Febre Criativa ($>45\ ^\circ\text{C}$). |

---

## 📐 2. Fundamentação Teórica e Modelos Matemáticos

### 2.1. Modelo *Leaky Integrate-and-Fire* (LIF) nas Malhas RC dos CIs `TL074`
A dinâmica temporal do potencial de membrana analógico $V(t)$ em cada folha axonial do amplificador operacional JFET `TL074` é governada pela equação diferencial ordinária de primeira ordem:

$$\tau_m \frac{dV(t)}{dt} = -(V(t) - V_{\text{rest}}) + R \cdot I(t)$$

* $\tau_m = R_f \cdot C_m$: Constante de tempo da membrana neural, determinada fisicamente pelo resistor de realimentação $R_f$ e pelo capacitor $C_m$ soldados em cada um dos 16 amplificadores operacionais das folhas.
* $V_{\text{rest}} = 1.65\text{ V}$: Potencial de repouso (terra virtual), gerado por um divisor resistivo bufferizado pelo segundo estágio do `NE5532`, posicionado exatamente na metade da faixa de leitura de 12 bits do conversor ADC do ESP32 (nível `2048` de `0` a `4095`).
* $I(t)$: Corrente de estímulo produzida pela interferência construtiva e destrutiva das ondas injetadas pelos conversores `DAC1 (GPIO25)` e `DAC2 (GPIO26)`.

### 2.2. Disparo Estocástico e Ruído Térmico de Johnson-Nyquist
A agitação térmica dos elétrons nos canais dos transistores e resistores gera uma tensão quadrática média de ruído branco proporcional à temperatura absoluta $T$ (em Kelvin) na largura de banda $\Delta f$:

$$\bar{v}_n^2 = 4 k_B T R \Delta f$$

Além disso, nos estágios de entrada JFET dos CIs `TL074`, a corrente de fuga de porta ($I_B$) dobra a cada $10\ ^\circ\text{C}$ de aumento térmico:

$$I_B(T) \approx I_{B0} \cdot 2^{\frac{T - T_0}{10}}$$

Combinando a compressão suave (*soft-clipping* em formato de tangente hiperbólica $\tanh$) do par diferencial com o desvio padrão do ruído térmico $\sigma_{\text{ruído}}(T)$, a probabilidade instantânea de um neurônio disparar um *spike* ao redor do limiar $V_{\text{th}}$ segue a distribuição sigmoide estocástica:

$$P(\text{Spike} \mid V, T) = \frac{1}{1 + \exp\left(-\frac{V(t) - V_{\text{th}}(T)}{\sigma_{\text{ruído}}(T)}\right)}$$

### 2.3. Codificação Quaternária e Bitstream Estocástico de 32 Canais
Cada um dos 256 neurônios da matriz $16 \times 16$ e cada uma das 32 portas físicas dos expansores `MCP23017` opera em **4 estados probabilísticos discretos**:
* **`0.10` (10% HIGH):** Estado Refratário / Inibição / Medo / Apatia.
* **`0.25` (25% HIGH):** Dúvida Sensorial (estímulo captado por apenas 1 sensor isolado, sem *grounding*).
* **`0.75` (75% HIGH):** Curiosidade / Correlação Ativa (estímulo confirmado por múltiplos sensores).
* **`1.00` (100% HIGH):** Certeza / Disparo Pleno (*Spike* / Memória Consolidada).

---

## 🛡️ 3. Arquitetura do Agente Encarnado (0 a 5 Anos & Sistema Imunológico Psíquico)

Para evitar que a rede entre em colapso ou crie delírios sem base na realidade física, o **Cleitin OS v3.0** implementa três barreiras inspiradas na neurobiologia:

1. **Freio Inibitório Anticonvulsivo (GABA — 20% da Rede):**
   * Se todos os neurônios excitatórios se retroalimentarem em loop positivo rumo a `1.00`, ocorre o equivalente eletrônico a uma crise epilética (travamento das 32 saídas em 100%).
   * **51 nós (20% dos 256 neurônios)** atuam exclusivamente como interneurônios inibitórios GABA. Caso a energia média da matriz ultrapasse **`0.70`**, o freio GABA dispara um pulso inibitório (`-1.0`) que força a malha imediatamente para `0.10`.
2. **Período Refratário Absoluto ($200\text{ ms}$):**
   * Todo neurônio que atinge o estado de disparo pleno (`1.00`) fica fisicamente bloqueado em `0.10` durante $200\text{ ms}$ a $300\text{ ms}$, impedindo oscilações parasitas de alta frequência.
3. **Grounding Sensorial e Faxina do Sono (Prevenção de Esquizofrenia):**
   * **Regra de Lastro (*Grounding*):** Se apenas 1 sensor (ex: ruído isolado no áudio sem variação térmica ou de I/O) detectar uma anomalia, o estado máximo permitido é **`0.25` (Dúvida)**. O *System Prompt* proíbe a LLM de inventar teorias para eventos com confiança $\le 0.25$, forçando-a a declarar *"Senti um estímulo isolado, mas não sei o que é"*.
   * **Faxina do Sono (`prune_unverified_delusions`):** Quando o sistema resfria os CIs para $<34\ ^\circ\text{C}$ (Modo Sono), o banco de dados **SQLite WAL** descarta automaticamente todas as memórias episódicas com confiança $\le 0.25$ que não se repetiram por 3 ciclos consecutivos.

### Regimes Termodinâmicos do Hipocampo

| Regime Cognitivo | Temperatura Física ($T$) | Limiar ($V_{\text{th}}$) | Temperatura da LLM | Comportamento do Agente e do Silício |
| :--- | :--- | :--- | :--- | :--- |
| **❄️ Letargia / Sono** | $< 34.0\ ^\circ\text{C}$ | `0.90` | `0.10 - 0.30` | Baixa atividade sináptica, economia de energia e poda de memórias ruidosas. |
| **⚖️ Vigília Homeostática** | $35.0\ ^\circ\text{C} \text{ a } 45.0\ ^\circ\text{C}$ | `0.50` | `0.60 - 0.80` | Aprendizado sensório-motor estável, foco analítico e consolidação no SQLite. |
| **🔥 Febre Criativa / REM** | $> 45.0\ ^\circ\text{C}$ | `0.20` | `1.15 - 1.45` | Corrente de fuga JFET elevada; associações livres, sonhos e *brainstorming* controlado. |

---

## 🔌 4. Engenharia de Hardware e Esquemático Pino a Pino (Cleitin Core v2.0)

### 4.1. Diagrama Geral de Blocos
(https://rbmeneses.github.io/InMaterio-cleitin-core-v2/)
```text
[ HOST PC: LLM Local (Ollama) + Orquestrador FastAPI + SQLite WAL + Painel HTML ]
                                       ▲
                                       │ Cabo USB Serial Binário (2.000.000 bps)
                                       ▼
[ CONTROLADOR CENTRAL: ESP32 DEVKIT V1 (Dual-Core FreeRTOS) ]
  │
  ├──► DAC1 (GPIO25) & DAC2 (GPIO26) ──► [ U1: NE5532 (DIP-8) - Tronco & Buffer V_rest 1.65V ]
  │                                                     │
  │                                                     ▼
  │                                      [ U2: TL074 (DIP-14) - 4 Ramos Dendríticos RC ]
  │                                                     │
  │                                                     ▼
  │    Loop Auto-Referência (Folha 16) ◄─ [ U3 a U6: 4× TL074 (DIP-14) - 16 Folhas LIF ]
  │    (R=47k + C=1µF volta p/ Tronco)                  │ (Divisores de proteção 10k/22k)
  │                                                     ▼
  ├──◄ ADC1_CH0 (GPIO36 @ 100 kHz) ◄──── [ U7: CD74HC4067 (DIP-24) - Multiplexador 16:1 ]
  │    (Seletores S0–S3: GPIO 14, 27, 32, 33)
  │
  ├──► PONTE TÉRMICA ATIVA (Colada sobre os CIs de Áudio):
  │      ├── GPIO18 (PWM) ──► MOSFET Q2 (IRLZ44N) ──► Micro-Cooler 5V (Esfria / Foco)
  │      ├── GPIO19 (PWM) ──► MOSFET Q1 (IRLZ44N) ──► Resistor 22Ω 5W (Febre / Entropia)
  │      └── GPIO39 (ADC1) ◄── Divisor com Termistor NTC 10kΩ (Leitura Real em °C)
  │
  └──► BARRAMENTO I²C @ 400 kHz (GPIO21 SDA / GPIO22 SCL):
         ├── [ U8: MCP23017 #1 (0x20) ] ──► Portas Estocásticas IO_00 a IO_15
         └── [ U9: MCP23017 #2 (0x21) ] ──► Portas Estocásticas IO_16 a IO_31
```

### 4.2. Mapeamento Completo de Pinos do ESP32

| Pino ESP32 | Periférico Interno | Direção | Conexão Física na PCB Cleitin Core v2.0 |
| :--- | :--- | :--- | :--- |
| **`GPIO25`** | `DAC1` (8-bit) | Saída Analógica | Pino 3 (`+IN A`) do `NE5532` via resistor de $10\text{ k}\Omega$ (Onda de Estímulo). |
| **`GPIO26`** | `DAC2` (8-bit) | Saída Analógica | Pino 2 (`-IN A`) do `NE5532` via resistor de $22\text{ k}\Omega$ (Modulação de Bias/Entropia). |
| **`GPIO36 (VP)`** | `ADC1_CH0` (12-bit) | Entrada Analógica | Pino 1 (`SIG/COM`) do Multiplexador `CD74HC4067` (Leitura das 16 Folhas). |
| **`GPIO39 (VN)`** | `ADC1_CH3` (12-bit) | Entrada Analógica | Ponto médio do divisor entre **Termistor NTC $10\text{ k}\Omega$** ($3.3\text{ V}$) e resistor de $10\text{ k}\Omega$ (`GND`). |
| **`GPIO14`** | Digital GPIO | Saída Digital | Pino 10 (`S0`) do `CD74HC4067`. |
| **`GPIO27`** | Digital GPIO | Saída Digital | Pino 11 (`S1`) do `CD74HC4067`. |
| **`GPIO32`** | Digital GPIO | Saída Digital | Pino 14 (`S2`) do `CD74HC4067`. |
| **`GPIO33`** | Digital GPIO | Saída Digital | Pino 13 (`S3`) do `CD74HC4067`. |
| **`GPIO18`** | `LEDC_CH0` (PWM) | Saída PWM | Gate do MOSFET `Q2 (IRLZ44N)` via resistor de $220\ \Omega$ (Aciona Micro-Cooler $5\text{ V}$). |
| **`GPIO19`** | `LEDC_CH1` (PWM) | Saída PWM | Gate do MOSFET `Q1 (IRLZ44N)` via resistor de $220\ \Omega$ (Aciona Aquecedor $22\ \Omega$/$5\text{ W}$). |
| **`GPIO21`** | `I2C_SDA` | Bidirecional | Pino 13 (`SDA`) de ambos os `MCP23017` (com pull-up de $4.7\text{ k}\Omega$ para $3.3\text{ V}$). |
| **`GPIO22`** | `I2C_SCL` | Saída Clock | Pino 12 (`SCL`) de ambos os `MCP23017` (com pull-up de $4.7\text{ k}\Omega$ para $3.3\text{ V}$). |

### 4.3. Parâmetros RC das 16 Folhas Axoniais (`U3` a `U6` — `TL074`)
Para que cada grupo de folhas responda a uma faixa espectral e tenha uma inércia de memória ($\tau_m = R_f \cdot C_m$) diferente:
* **Folhas F1 a F4 (`U3` — Foco Analítico / Passa-Baixa):** $R_{\text{in}} = 10\text{ k}\Omega$, $R_f = 47\text{ k}\Omega$, $C_m = 100\text{ nF}$.
* **Folhas F5 a F8 (`U4` — Curiosidade / Passa-Faixa):** $R_{\text{in}} = 10\text{ k}\Omega$, $R_f = 47\text{ k}\Omega$, $C_m = 22\text{ nF}$.
* **Folhas F9 a F12 (`U5` — Criatividade / Passa-Alta):** $R_{\text{in}} = 10\text{ k}\Omega$, $R_f = 68\text{ k}\Omega$, $C_m = 4.7\text{ nF}$.
* **Folhas F13 a F16 (`U6` — Impulso & Auto-Referência):** $R_{\text{in}} = 10\text{ k}\Omega$, $R_f = 100\text{ k}\Omega$, $C_m = 10\text{ nF}$. A saída da **Folha 16** (pino 14 de `U6`) retorna ao pino 2 (`-IN A`) do tronco `NE5532` através de $R = 47\text{ k}\Omega$ em série com $C = 1\ \mu\text{F}$.

---

## 📦 5. Lista Completa de Materiais (BOM — *Bill of Materials*)

| Designador | Qtd | Componente | Encapsulamento | Função no Projeto |
| :--- | :--- | :--- | :--- | :--- |
| **MCU1** | 1 un. | Módulo **ESP32 DevKit V1** (ESP32-WROOM-32) | 30/38 pinos | Controlador Dual-Core FreeRTOS, DACs, ADC 12 bits e Ponte USB 2 Mbps. |
| **U1** | 1 un. | CI Amplificador Operacional **NE5532P** | DIP-8 (+ Soquete) | OpAmp A: Tronco Misturador de Ondas / OpAmp B: Buffer Terra Virtual $V_{\text{rest}} = 1.65\text{ V}$. |
| **U2–U6** | 5 un. | CI Quad Op-Amp JFET **TL074CN** | DIP-14 (+ Soquete) | 20 Amplificadores Operacionais (4 Ramos Dendríticos em `U2` + 16 Folhas LIF em `U3–U6`). |
| **U7** | 1 un. | Multiplexador Analógico **CD74HC4067E** | DIP-24 (+ Soquete) | Multiplexa as 16 folhas axoniais para leitura no pino `GPIO36`. |
| **U8, U9** | 2 un. | Expansor de I/O I²C **MCP23017-E/SP** | DIP-28 (+ Soquete) | Fornece as 32 portas de entrada/saída em bitstream estocástico (`0x20` e `0x21`). |
| **Q1, Q2** | 2 un. | MOSFET Canal N Logic-Level **IRLZ44N** | TO-220 | Chaveamento PWM do Aquecedor de Febre (`Q1`) e do Micro-Cooler (`Q2`). |
| **TH1** | 1 un. | Termistor **NTC 10 kΩ** ($\beta = 3950$) | Radial Epóxi | Sensor de temperatura real colado ao barramento térmico dos CIs. |
| **R_HEAT** | 1 un. | Resistor de Fio/Porcelana **22 Ω / 5 W** | Axial Cerâmico | Atuador térmico para induzir estado febril ($>45\ ^\circ\text{C}$) na régua de alumínio. |
| **FAN1** | 1 un. | Micro-Cooler **5 V DC** ($30\text{ mm}$ ou $40\text{ mm}$) + Diodo `1N4007` | 2 pinos | Resfriamento ativo para homeostase ($38\ ^\circ\text{C}$) e sono ($<34\ ^\circ\text{C}$). |
| **PASSIVOS** | 1 kit | Resistores ($220\ \Omega$, $4.7\text{ k}\Omega$, $10\text{ k}\Omega$, $22\text{ k}\Omega$, $47\text{ k}\Omega$, $68\text{ k}\Omega$, $100\text{ k}\Omega$) e Capacitores ($4.7\text{ nF}$, $10\text{ nF}$, $22\text{ nF}$, $100\text{ nF}$, $1\ \mu\text{F}$, $10\ \mu\text{F}$) | Axial / Radial Through-Hole | Malhas de integração RC, divisores de proteção ADC ($10\text{ k}\Omega$/$22\text{ k}\Omega$) e desacoplamento. |

---

## 📡 6. Protocolo Binário de Alta Velocidade (USB Serial 2 Mbps)

A comunicação entre o Orquestrador Python e o ESP32 ocorre de forma transacional a **2.000.000 baud**:

* **Pacote TX (Host Python ➔ ESP32 — 11 Bytes):**
  ```text
  [ 0xAA (Sync) | Amp_DAC1 (1B) | Bias_DAC2 (1B) | Freq_Step (1B) | PWM_Cooler (1B) | PWM_Heater (1B) | Bitstream_32_IO (4B uint32 Big-Endian) | Pad (1B) ]
  ```
* **Pacote RX (ESP32 ➔ Host Python — 34 Bytes):**
  ```text
  [ Folha_01_ADC (2B) | Folha_02_ADC (2B) | ... | Folha_16_ADC (2B) | NTC_Temp_ADC (2B) ]  --> 17 inteiros unsigned short (!17H em Big-Endian)
  ```

---

## 📂 7. Estrutura do Repositório

```text
cleitin-core/
├── index.html                        # Estação Unificada: Simulador Cleitin OS v3.0 + Blueprint SVG Sincronizado
├── Cleitin_Core_v2_Blueprint.html    # Blueprint Vetorial Standalone (Bluescreen com Zoom, Pan, Exportação SVG e Pulsos)
├── firmware/
│   └── firmware_cleitin_pcb.ino      # Firmware C++ Dual-Core FreeRTOS para o ESP32 (DAC, MUX ADC, PWM e I2C MCP23017)
├── python/
│   ├── cleitin_orchestrator.py       # Servidor FastAPI + Ponte Serial USB + Matriz 16x16 + SQLite WAL + Ollama LLM
│   └── requirements.txt              # Dependências Python (fastapi, uvicorn, pyserial, numpy)
└── README.md                         # Documentação Técnica Completa do Projeto
```

---

## 🚀 8. Guia de Implantação Passo a Passo (Da Bancada à LLM)

### Passo 1: Executar a Estação Visual (Sem Instalar Nada)
O arquivo `index.html` contém toda a suíte de simulação matemática e o Blueprint vetorial sincronizado.
1. Basta abrir `index.html` diretamente em qualquer navegador moderno, ou publicar no **GitHub Pages** (`Settings` ➔ `Pages` ➔ `Branch: main`).

### Passo 2: Gravar o Firmware no ESP32
1. Abra o arquivo `firmware/firmware_cleitin_pcb.ino` na **Arduino IDE** ou **PlatformIO**.
2. Selecione a placa **ESP32 Dev Module** e a porta serial correspondente (`COM3`, `/dev/ttyUSB0`, etc.).
3. Faça o upload do código. O rádio Wi-Fi e Bluetooth serão desligados automaticamente no `setup()` para garantir precisão máxima de 12 bits nos canais `ADC1`.

### Passo 3: Iniciar o Orquestrador Python + LLM Local (Ollama)
1. Instale o [Ollama](https://ollama.com/) na sua máquina local e baixe um modelo leve:
   ```bash
   ollama run llama3.1:8b
   ```
2. Instale as dependências do Orquestrador Python:
   ```bash
   pip install fastapi uvicorn pyserial numpy
   ```
3. Inicie o servidor na porta `8000` (se a PCB não estiver conectada na USB, o servidor entra automaticamente em **Modo de Emulação Termodinâmica**):
   ```bash
   uvicorn cleitin_orchestrator:app --host 0.0.0.0 --port 8000 --reload
   ```
4. Teste a consulta ao Agente Encarnado via terminal ou navegador:
   ```bash
   curl -X POST http://localhost:8000/api/interact \
        -H "Content-Type: application/json" \
        -d '{"prompt": "O que você está sentindo no seu corpo de silício agora?", "sensor_count": 3, "target_temp": 38.5}'
   ```

---

## 🎮 9. Manual do Simulador Web & Blueprint Interativo (GitHub Pages)

Na interface web (`index.html`), você controla todos os subsistemas em tempo real:
* **Modos de Visualização (Topo):** Alterne entre **⚡ Tudo Junto** (Simulador + Blueprint acoplados), **🧠 Só Simulador** ou **📐 Só Blueprint**.
* **Sliders do Pulso Primordial (Onda 1 a Onda 4):** Ajuste as frequências de $0.5\text{ Hz}$ a $10.0\text{ Hz}$ para visualizar a interferência construtiva/destrutiva no osciloscópio Canvas e alterar a velocidade dos pulsos elétricos no Blueprint SVG.
* **Botões de Regime Térmico:**
  * `❄️ Modo Sono (<34°C)`: Eleva o limiar para `0.90` e pinta os pulsos do Blueprint de azul.
  * `⚖️ Vigília (38°C)`: Mantém homeostase equilibrada com limiar `0.50` e pulsos verdes.
  * `🔥 Febre Criativa (>45°C)`: Cai o limiar para `0.20`, injeta deriva térmica nos neurônios e dispara pulsos vermelhos de alta frequência no Blueprint.
* **Testes do Sistema Imunológico Psíquico:**
  * `⚡ Simular Sobrecarga / Testar Freio GABA`: Força os neurônios excitatórios para `1.00` e demonstra o corte imediato pelos 51 neurônios GABA quando a energia média passa de `0.70`.
  * `🌙 Executar Faxina do Sono`: Reduz a temperatura para $31.0\ ^\circ\text{C}$ e limpa os ruídos de baixa confiança (`p=0.25`) acumulados no log de *Grounding*.
* **Navegação no Blueprint SVG:** Use a roda do mouse para **Zoom** ($35\%$ a $350\%$), arraste com o botão esquerdo para **Pan**, passe o mouse sobre qualquer trilha para inspecionar a malha elétrica e clique em **EXPORTAR SVG** para baixar o esquemático vetorizado.

---

## 🗺️ 10. Roadmap Evolutivo

- [x] **Fase 1:** Concepção teórica do modelo LIF e disparo sigmoide estocástico com ruído térmico de Johnson-Nyquist.
- [x] **Fase 2:** Substituição de CPUs x86 lobotomizadas pela árvore de 22 neurônios analógicos com CIs de áudio `NE5532` e `TL074` em encapsulamento DIP.
- [x] **Fase 3:** Implementação da malha térmica fechada (`NTC 10k` + Aquecedor PWM + Cooler PWM), barramento de 32 I/O (`2× MCP23017`) e freio anticonvulsivo GABA na matriz $16 \times 16$.
- [x] **Fase 4:** Criação da Estação Integrada Web (`Cleitin OS v3.0` + `Blueprint Vetorial Interativo`) e Orquestrador FastAPI/Ollama com persistência em SQLite WAL.
- [ ] **Fase 5 (Futuro):** Acoplamento de interferência óptica (laser de baixa potência + sensores CCD/fotodiodos) como expansão física do gerador de Pulso Primordial.

---

## 📄 Licença

Distribuído sob a licença **MIT**. Sinta-se livre para clonar, soldar na bancada, modificar e expandir esta arquitetura para pesquisa em IA Encarnada (*Embodied AI*), Computação Estocástica e Hardware Hacking.
