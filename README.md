# Sistema de Monitoramento e Controle de Gases com ESP32 e MQTT  

Este projeto apresenta um sistema baseado no protocolo MQTT para monitoramento e controle de gases em ambientes industriais, utilizando sensores de gás, exaustores automatizados e dispositivos wearables. O objetivo principal é aumentar a segurança no trabalho, permitindo respostas rápidas e automatizadas a situações de risco.

---

## 🚀 Funcionalidades  
1. **Monitoramento de Gases**  
   - Utilização de sensores da linha MQ para detecção de gases como monóxido de carbono (CO), metano (CH4) e dióxido de carbono (CO2).  

2. **Exaustores Automatizados**  
   - Exaustores acionados automaticamente via ESP32 quando detectadas concentrações perigosas de gases.  

3. **Dispositivos Wearables**  
   - Equipamentos vestíveis que alertam os trabalhadores por meio de sinais sonoros e visuais em caso de risco detectado.  

4. **Comunicação MQTT**  
   - Comunicação eficiente e em tempo real entre sensores, exaustores e wearables, garantindo coordenação e resposta imediata.  

---

## 🛠️ Tecnologias e Componentes  
### Hardware  
- **ESP32**: Microcontrolador responsável pelo processamento de dados e comunicação MQTT.  
- **Sensores de Gases (Linha MQ)**: Sensores como MQ-2, MQ-7 e MQ-135 para monitoramento de gases.  
- **Exaustores Automatizados**: Controlados pelo ESP32 para atuar automaticamente em situações de risco.  
- **Dispositivos Wearables**: Vestíveis para alerta direto aos trabalhadores.  

### Software  
- **Arduino IDE**: Para programação e configuração do ESP32.  
- **Protocolo MQTT**: Usado para comunicação eficiente entre dispositivos, com o broker Mosquitto.  

---

## 📋 Como Funciona  
### Etapas do Sistema  
1. **Coleta de Dados**  
   - Os sensores conectados ao ESP32 monitoram continuamente os níveis de gases no ambiente.  
   - Os dados são enviados ao broker MQTT, disponíveis para outros dispositivos no sistema.  

2. **Processamento e Decisão**  
   - O ESP32 avalia os dados recebidos para verificar se os níveis de gás ultrapassam limites seguros.  
   - Caso haja perigo, o ESP32 publica comandos para acionar os exaustores e alertar os wearables.  

3. **Ação Automatizada**  
   - **Exaustores**: Ativados automaticamente para mitigar a concentração de gases.  
   - **Wearables**: Alertam os trabalhadores sobre a situação de risco.  

---

## 📝 Pré-requisitos  
1. **Hardware**  
   - ESP32  
   - Sensores de gás (MQ-2, MQ-7, MQ-135, etc.)  
   - Exaustores ou ventiladores compatíveis com controle via ESP32  
   - Dispositivos wearables (opcional para testes)  

2. **Software**  
   - Arduino IDE  
   - Broker MQTT (sugestão: Mosquitto)  
   - Cliente MQTT para monitoramento (ex.: MQTT Explorer ou MQTT.fx)  

---

## 🛠️ Instalação e Configuração  
### 1. Instale o Broker MQTT  
- Instale o Mosquitto MQTT no servidor local ou em nuvem.  
  ```bash
  sudo apt update  
  sudo apt install mosquitto mosquitto-clients  
