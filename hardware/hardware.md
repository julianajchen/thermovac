# Descrição de Hardware

## Componentes Principais

- **ESP32 DevKitC V4**
  - Microcontrolador baseado no módulo ESP32-WROOM-32D, com Wi-Fi e Bluetooth integrados.
- **Sensor DHT22**
  - Sensor digital utilizado para medir a temperatura e umidade relativa do ar.
  - Faixa de medição de temperatura: -40 °C a +80 °C.
  - Faixa de medição de umidade: 0% a 100% UR.
  - Precisão típica de temperatura: ±0,5 °C.
- **Display LCD 16x2 com I2C**
  - Exibe os valores de temperatura, umidade e a classificação do sistema.
  - Interface I2C permite comunicação com ESP32 utilizando as linhas SDA e SCL.
- **LEDs indicadores**
  - LED verde: indica condição normal.
  - LED amarelo: indica condição de atenção.
  - LED vermelho: indica condição de alerta.
- **Buzzer passivo**
  - Emite um sinal sonoro quando a temperatura atinge uma condição de alerta.
- **Resistores de 220 Ω**
  - Limitam a corrente elétrica dos LEDs.

## Diagrama de Montagem

- Veja `diagram.json` para o esquema do circuito desenvolvido na plataforma Wokwi.

## Referências de Datasheets

1. Espressif Systems. *ESP32 Series Datasheet*.
2. Aosong Electronics. *AM2302 (DHT22) Digital Temperature and Humidity Sensor Datasheet*.
