# CLYVO VET - Monitor Inteligente de Bebedouro 🐾
### **Sprint 1 - Disruptive Architectures: IOT, IOB & Generative IA**

---

## 📖 Sobre o Projeto
Este projeto faz parte do Challenge com a **CLYVO VET**, focado em transformar a saúde pet através da tecnologia. O sistema consiste em um bebedouro inteligente monitorado via IoT, que permite acompanhar em tempo real o nível de água disponível e as condições ambientais (temperatura e umidade) onde o pet se encontra.

O objetivo principal é auxiliar na **prevenção de doenças renais** e garantir a **continuidade terapêutica**, enviando alertas imediatos aos tutores caso o nível de água esteja crítico.

---

## 🚀 Funcionalidades
*   **Monitoramento de Nível:** Medição em tempo real da quantidade de água via sensor ultrassônico.
*   **Controle Ambiental:** Leitura de temperatura e umidade para garantir o bem-estar térmico do animal.
*   **Alertas Visuais:** LED físico e alertas no Dashboard indicam quando o bebedouro precisa ser abastecido.
*   **Interface Local:** Display OLED exibe os dados diretamente no dispositivo.
*   **Dashboard Web:** Interface responsiva que recebe dados via protocolo MQTT.

---

## 🛠️ Hardware Utilizado
Para a construção do protótipo (simulado via Wokwi), utilizamos os seguintes componentes:
1.  **ESP32 DevKit V4:** Microcontrolador com WiFi nativo.
2.  **Sensor Ultrassônico HC-SR04:** Medição de distância (nível de água).
3.  **Sensor DHT22:** Monitoramento de temperatura e umidade ambiente.
4.  **Display OLED SSD1306 (I2C):** Interface visual local.
5.  **LED Vermelho:** Atuador para alertas críticos.

---

## 🏗️ Arquitetura e Tecnologias
O projeto utiliza uma arquitetura baseada em microsserviços de dados:
*   **Linguagem C++ (Arduino IDE):** Programação do firmware do ESP32.
*   **Protocolo MQTT:** Comunicação assíncrona entre o dispositivo e o dashboard.
*   **JSON:** Formatação estruturada de dados para envio de mensagens.
*   **HiveMQ (Broker):** Intermediário público para tráfego das mensagens.
*   **HTML5/CSS3/JavaScript:** Front-end para visualização dos dados em tempo real.

---

## 📋 Pré-requisitos e Instalação

### No ESP32 (Firmware):
É necessário instalar as seguintes bibliotecas na Arduino IDE:
*   `PubSubClient` 
*   `DHT sensor library` 
*   `Adafruit SSD1306` e `Adafruit GFX`
*   `ArduinoJson` 

### No Dashboard (Front-end):
Basta abrir o arquivo `index.html` em qualquer navegador moderno. A conexão com o broker MQTT é feita via WebSockets.

---

## 🔗 Links do Projeto
*   **Simulação Wokwi:** [https://wokwi.com/projects/462585423032013825]
*   **Vídeo de Demonstração:** [https://youtu.be/RmeN-215nk4]
*   **Github:** [https://youtu.be/RmeN-215nk4]


---

## 👥 Integrantes
*   **FABRÍCIO HENRIQUE PEREIRA** - RM563237
*   **PEDRO HENRIQUE DE OLIVEIRA** - RM562312
*   **LEONARDO JOSÉ PEREIRA** - RM563065
*   **MIGUEL HENRIQUE OLIVEIRA DIAS** - RM565492