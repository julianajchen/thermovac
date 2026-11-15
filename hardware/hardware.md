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

## Interfaces e Conexões

Os componentes do ThermoVac são conectados ao ESP32 por meio de interfaces digitais e do barramento I2C, conforme a distribuição dos pinos apresentada a seguir.

| Componente | Interface | Pino ESP32 |
|---|---|---|
| Sensor DHT22 | Comunicação digital | GPIO 15 |
| Display LCD 16x2 | I2C – SDA | GPIO 21 |
| Display LCD 16x2 | I2C – SCL | GPIO 22 |
| LED verde | GPIO digital | GPIO 2 |
| LED amarelo | GPIO digital | GPIO 4 |
| LED vermelho | GPIO digital | GPIO 5 |
| Buzzer passivo | GPIO digital | GPIO 18 |

Os LEDs são conectados em série com resistores de 220 Ω para limitar a corrente elétrica.

## Diagrama de Montagem

- Veja `diagram.json` para o esquema do circuito desenvolvido na plataforma Wokwi.

## Referências de Datasheets

1. Espressif Systems. *ESP32 Series Datasheet*.
2. Aosong Electronics. *AM2302 (DHT22) Digital Temperature and Humidity Sensor Datasheet*.
