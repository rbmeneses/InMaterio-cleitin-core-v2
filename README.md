# 🧠 Cleitin OS v3.0 & Blueprint Core v2.0 — Estação Neuromórfica Integrada

![Versão](https://img.shields.io/badge/vers%C3%A3o-3.0-00f0ff?style=for-the-badge)
![Arquitetura](https://img.shields.io/badge/arquitetura-NPU%20Anal%C3%B3gica%20USB-ffc857?style=for-the-badge)
![Tecnologias](https://img.shields.io/badge/stack-HTML5%20%7C%20TailwindCSS%20%7C%20SVG%20%7C%20JS-00ff88?style=for-the-badge)
![Licença](https://img.shields.io/badge/licen%C3%A7a-MIT-ff6b6b?style=for-the-badge)

O **Cleitin OS v3.0 & Blueprint Core v2.0** é uma suíte de simulação e instrumentação em tempo real para um processador neuromórfico (NPU - *Neural Processing Unit*) analógico acoplado via USB. 

A aplicação unifica, em uma interface única baseada em navegador, um **simulador matemático de dinâmica neural de estocasticidade quaternária** e um **blueprint esquemático interativo em SVG** sincronizado em tempo real via telemetria física simulada.

---

## 📋 Sumário

- [Visão Geral da Arquitetura](#-visão-geral-da-arquitetura)
- [Funcionalidades Principais](#-funcionalidades-principais)
- [Estrutura dos Módulos do Sistema](#-estrutura-dos-módulos-do-sistema)
  - [1. Pulso Primordial (Interferência de Ondas)](#1-pulso-primordial-interfer%C3%AAncia-de-4-ondas)
  - [2. Controle Térmico & Ruído Johnson-Nyquist](#2-controle-t%C3%A9rmico--ru%C3%ADdo-johnson-nyquist)
  - [3. Matriz Estocástica 16×16 & Dinâmica GABA](#3-matriz-estoc%C3%A1stica-1616--din%C3%A2mica-gaba)
  - [4. Sistema Imunológico Psíquico & Grounding](#4-sistema-imunol%C3%B3gico-ps%C3%ADquico--grounding)
  - [5. Barramento 32 I/O (2× MCP23017)](#5-barramento-32-io-2-mcp23017)
  - [6. Blueprint Técnico Interativo (Bluescreen SVG)](#6-blueprint-t%C3%A9cnico-interativo-bluescreen-svg)
- [Mapeamento de Pinos & Telemetria Hardware (ESP32)](#-mapeamento-de-pinos--telemetria-hardware-esp32)
- [Lista de Materiais (BOM - Bill of Materials)](#-lista-de-materiais-bom---bill-of-materials)
- [Como Executar](#-como-executar)
- [Controles de Interatividade](#-controles-de-interatividade)

---

## 🔬 Visão Geral da Arquitetura

O sistema simula um ambiente de hardware analógico e computação neuromórfica híbrida onde:
1. **Ondas harmônicas** alimentam o tronco analógico (*OpAmp NE5532*).
2. **Amplificadores Operacionais JFET (*TL074*)** formam redes de integração por vazamento (*Leaky Integrate-and-Fire - LIF*).
3. **Sensores NTC e atuadores térmicos (PWM/MOSFET)** controlam a temperatura dos CIs, alterando dinamicamente o ruído térmico de Johnson-Nyquist e modulando o limiar de disparo dos neurônios.
4. **Uma matriz de 256 neurônios (16×16)** opera sob lógica estocástica quaternária com malha inibitória **GABA** (20% da matriz) para evitar surtos epileptiformes (realimentação positiva descontrolada).

```
   [ Host PC / LLM Local ] 
             │  (USB Serial 2 Mbps)
             ▼
      ┌──────────────┐      Sinais Analógicos (DAC1/2)      ┌─────────────────────────┐
      │  ESP32 DevKit│ ───────────────────────────────────► │  NE5532 + TL074 (Audio) │
      │  (FreeRTOS)  │ ◄─────────────────────────────────── │  (16 Folhas LIF Axoniais)│
      └──────┬───────┘       Amostragem MUX (ADC1)          └────────────┬────────────┘
             │                                                           │
             │ I²C (400 kHz)                                             │ Modulação Térmica
             ▼                                                           ▼
     ┌──────────────┐                                           ┌─────────────────┐
     │ 2x MCP23017  │ ◄─── Sincronia de Estado Quaternário ───  │ Sensores NTC &  │
     │ (32 I/O Bus) │                                           │ MOSFETs Heater  │
     └──────────────┘                                           └─────────────────┘
```

---

## ⚡ Funcionalidades Principais

* **Simulação Quaternária de Estados:** Estados discretos de energia representados por $P \in \{0.10, 0.25, 0.75, 1.00\}$ (Refratário, Dúvida, Curiosidade e Spike).
* **Bluescreen Esquema Veto-Sincronizado:** Renderização dinâmica em SVG com animações vetoriais via `requestAnimationFrame` que modulam velocidade e cor dos pulsos conforme temperatura e energia global.
* **Malha Inibitória GABA:** Detecção automática de energia total $>0.70$, forçando despolarização de proteção para estado refratário.
* **Poda de Memória no Sono:** Mecanismo para descarte de ruídos não confirmados (sem *Grounding* sensorial) ao resfriar o sistema para regimes de sono ($<34^\circ\text{C}$).
* **Exportação Vetorial:** Capacidade de exportação em alta resolução (`.svg`) do esquema eletrônico interativo.

---

## 🛠️ Estrutura dos Módulos do Sistema

### 1. Pulso Primordial (Interferência de 4 Ondas)
Gera uma forma de onda resultante injetada via DAC1 (GPIO25) e DAC2 (GPIO26) do microcontrolador.
* **Onda 1 (Base/Tronco):** Frequência de 0.5 Hz a 10 Hz.
* **Onda 2 (Harmônica):** Segunda componente harmônica.
* **Onda 3 (Modulação):** Frequência de envelope e modulação de amplitude.
* **Onda 4 (Entropia Fase):** Componente estocástica para variabilidade de fase.
* **Cálculo da Soma Harmônica:** Renderizado em Canvas 2D (1024 passos virtuais de fase), produzindo um **Peso Resultante ($W_{int}$)** entre $0.10$ e $1.00$.

### 2. Controle Térmico & Ruído Johnson-Nyquist
Divisão da circuito analógico em 4 *clusters* térmicos associados aos CIs TL074 (Quadrantes NO, NE, SO, SE).
* **Modo Sono ($<34.0^\circ\text{C}$):** Limiar de disparo elevado ($0.90$), ruído negativo, supressão de atividade.
* **Modo Vigília ($35.0^\circ\text{C} - 45.0^\circ\text{C}$):** Limiar nominal ($0.50$), operação estável equilibrada.
* **Modo Febre Criativa ($>45.0^\circ\text{C}$):** Limiar baixo ($0.20$), alto ruído de despolarização, potencial de tempestade elétrica.
* **Atuação Térmica:** Acionamento de malha fechada via MOSFET Q1 (Aquecedor de $22\Omega/5\text{W}$ em GPIO19) e MOSFET Q2 (Cooler PWM em GPIO18).

### 3. Matriz Estocástica 16×16 & Dinâmica GABA
Array de 256 nós processados individualmente:
* **Neurônios GABA (Inibitórios):** 51 nós sorteados aleatoriamente (~20% da matriz) com anel visual em tom esmeralda.
* **Equação de Atualização de Potencial:**
  $$Drive = (P_{atual} \times 0.55) + (W_{int} \times 0.35) + Ru\acute{\iota}do(T)$$
* **Janela Refratária:** Trava de pulso de $220\text{ ms}$ a $300\text{ ms}$ após o disparo ($P = 1.00$).

### 4. Sistema Imunológico Psíquico & Grounding
* **Corte Imunológico (GABA Brake):** Se a energia média da matriz ultrapassar o limite crítico de $0.70$, o freio inibitório força instantaneamente $75\%$ da rede e $100\%$ dos nós GABA para estado refratário ($0.10$).
* **Filtro de Grounding:** Registra contatos sensoriais episódicos. Estímulos não confirmados por múltiplos sensores acumulam-se no contador de ruído e são eliminados durante a **Faxina do Sono** (`runSleepPruning()`).

### 5. Barramento 32 I/O (2× MCP23017)
* Mapeamento dos 256 neurônios em grupos de 8 para amostragem estocástica de saída.
* Retorna estados lógicos digitais (HIGH/LOW) para 32 pinos expandidos via I²C ($400\text{ kHz}$) nos endereços `0x20` (U8) e `0x21` (U9).

### 6. Blueprint Técnico Interativo (Bluescreen SVG)
* **Viewport Zoom & Pan:** Suporte a zoom via roda do mouse (escala $35\%$ a $350\%$), translação via clique-e-arraste.
* **Realce de Malha:** Troca de estados estáticos para iluminação destacada ao passar o cursor sobre as trilhas do esquema (*Trace Hovering*).
* **Telemetria de Folhas LIF:** Mudança dinâmica da cor de preenchimento e borda dos 16 blocos de folhas axoniais (F1 a F16) de acordo com o potencial médio real da matriz.

---

## 📌 Mapeamento de Pinos & Telemetria Hardware (ESP32)

| Pino ESP32 | Função no Circuito | Descrição Elétrica / Destino |
| :--- | :--- | :--- |
| **GPIO25** | `DAC1` | Onda Analógica Base 1 (Entrada NE5532 OpAmp A) |
| **GPIO26** | `DAC2` | Onda Analógica Base 2 (Entrada NE5532 OpAmp A) |
| **GPIO36** | `ADC1_CH0` | Leitura de Saída do MUX CD74HC4067 (Pino SIG) |
| **GPIO39** | `ADC1_CH3` | Leitura da Ponte Térmica via Divisor NTC 10k |
| **GPIO14** | `DIGITAL OUT` | Seletor MUX Bit `S0` |
| **GPIO27** | `DIGITAL OUT` | Seletor MUX Bit `S1` |
| **GPIO32** | `DIGITAL OUT` | Seletor MUX Bit `S2` |
| **GPIO33** | `DIGITAL OUT` | Seletor MUX Bit `S3` |
| **GPIO18** | `PWM OUT` | Controle de Velocidade do Cooler (MOSFET Q2) |
| **GPIO19** | `PWM OUT` | Controle de Aquecimento (MOSFET Q1 - Resistor $22\Omega$) |
| **GPIO21** | `I2C SDA` | Barramento de Dados para MCP23017 (#1 e #2) |
| **GPIO22** | `I2C SCL` | Barramento de Clock I²C ($400\text{ kHz}$) |

---

## 📦 Lista de Materiais (BOM - Bill of Materials)

| Componente | Designador | Qtd | Descrição / Parâmetros |
| :--- | :--- | :--- | :--- |
| **ESP32 DevKit V1** | MCU1 | 1 un. | Dual-Core, Wi-Fi/BT, 2x DAC 8-bit, 12-bit ADC |
| **NE5532P** | U1 | 1 un. | Dual Low-Noise OpAmp (Misturador de Ondas + Vrest 1.65V) |
| **TL074CN** | U2–U6 | 5 un. | Quad JFET OpAmp (4 Ramos Dendríticos + 16 Folhas LIF) |
| **CD74HC4067E** | U7 | 1 un. | Multiplexador Analógico 16:1 (DIP-24) |
| **MCP23017** | U8, U9 | 2 un. | Expansor de I/O de 16-bits I²C (DIP-28) |
| **IRLZ44N** | Q1, Q2 | 2 un. | MOSFET N-Channel Logic-Level (Controle Térmico) |
| **NTC 10k** | TH1 | 1 un. | Sensor de Temperatura NTC 10k $\beta=3950$ |
| **Capacitores Filme** | C1–C16 | 16 un. | 4x $100\text{nF}$, 4x $22\text{nF}$, 4x $4.7\text{nF}$, 4x $100\text{pF}$ (Inércia Axonial) |

---

## 🚀 Como Executar

Por ser uma suíte autoverificável desenvolvida em **HTML5**, **Tailwind CSS (via CDN)** e **Vanilla JavaScript (ES6+)**, não há necessidade de instalação de dependências via `npm` ou compiladores adicionais.

1. Baixe ou clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/cleitin-os-npu.git
   cd cleitin-os-npu
   ```

2. Abra o arquivo `index.html` diretamente em um navegador web moderno (Google Chrome, Mozilla Firefox, Microsoft Edge ou Safari):
   ```bash
   # Exemplo via linha de comando Linux/macOS
   open index.html
   
   # Ou sirva via servidor local HTTP simples
   python -m http.server 8000
   ```

3. Acesse no navegador: `http://localhost:8000`.

---

## 🎮 Controles de Interatividade

### Painel Superior (Header)
* **⚡ Tudo Junto:** Exibe a tela dividida contendo o simulador e o blueprint esquemático.
* **🧠 Só Simulador:** Oculta o blueprint vetorial e expande os seletores da matriz neural.
* **📐 Só Blueprint:** Oculta os seletores para foco na análise esquemática.
* **⏸️ Pausar/Retomar Loop:** Interrompe a malha de tempo real do engine `requestAnimationFrame`.

### Painel da Matriz Neural
* **Clique Manual em Neurônio:** Força o estado do nó individual diretamente para o nível de *Spike* ($P = 1.00$).
* **⚡ Testar Surto / Freio GABA:** Injeta um estado de sobrecarga em $100\%$ dos neurônios excitatórios para homologação do freio inibitório.
* **🌙 Faxina do Sono:** Aciona o resfriamento forçado a $31^\circ\text{C}$ e esvazia a fila de eventos estocásticos pendentes.

### Navegação no Blueprint SVG
* **Zoom (+ / -):** Botões da interface ou rolagem do *scroll* do mouse sobre o blueprint.
* **Pan (Arrastar):** Clique com o botão esquerdo e arraste dentro da área azul da prancha eletrônica.
* **Hover de Trilhas:** Passe o mouse sobre qualquer trilha luminosa para visualizar a identificação da malha no rodapé técnico.
* **EXPORTAR SVG:** Gera o download imediato da prancha vetorial do circuito com o estado dos componentes no momento do clique.

---

## 📄 Licença

Este projeto está sob a licença [MIT](LICENSE). Sinta-se livre para modificar, distribuir e utilizar para fins acadêmicos, de pesquisa e projetos pessoais.
