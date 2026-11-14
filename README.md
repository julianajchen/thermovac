# ThermoVac

**Sistema de Monitoramento de Temperatura e Umidade para Transporte de Vacinas**

## Descrição do Projeto

O ThermoVac é um protótipo de sistema de monitoramento de temperatura e umidade desenvolvido para a disciplina de Objetos Inteligentes Conectados.

O projeto utiliza um ESP32 e um sensor DHT22 para acompanhar as condições ambientais durante o transporte de vacinas. A temperatura é classificada de acordo com faixas previamente estabelecidas, permitindo a identificação de condições normais, de atenção e de alerta.

A sinalização ocorre por meio de LEDs e um buzzer, enquanto as informações são exibidas em um display LCD e transmitidas pela rede Wi-Fi utilizando o protocolo MQTT, possibilitando o acompanhamento remoto dos dados.

O projeto foi desenvolvido e testado por meio de simulação na plataforma Wokwi.

## Pré-requisitos
- Arduino IDE (ou ambiente compatível com ESP32).
- Bibliotecas: WiFi, PubSubClient, DHT, Wire e LiquidCrystal_I2C.
- Plataforma Wokwi
- Broker MQTT (HiveMQ WebSocket Client)

## Estrutura do Repositório

A documentação do projeto está organizada nas seguintes pastas:

- `src/`: código-fonte do sistema.
- `hardware/`: descrição dos componentes e circuito utilizado.
- `protocols/`: documentação da comunicação MQTT.
- `results/`: registros da simulação e resultados dos testes.

## Instalação e Uso

1. Clone este repositório:

```bash
$ git clone https://github.com/julianajchen/thermovac.git
$ cd thermovac
```

2. Abra o arquivo `src/sketch.ino` na Arduino IDE.
3. Instale as bibliotecas necessárias, listadas em `src/libraries.txt`.
4. Utilize o arquivo `hardware/diagram.json` para reproduzir a montagem do circuito na plataforma Wokwi.
5. Execute a simulação. A conexão Wi-Fi será realizada pela rede `Wokwi-GUEST`.
6. Acesse o HiveMQ WebSocket Client e conecte-se ao broker `mqtt-dashboard.com`, na porta `1883`.
7. Inscreva-se no tópico `vacinas/dados` para visualizar as mensagens enviadas pelo ThermoVac.

As mensagens recebidas apresentam os valores de temperatura, umidade e o estado de classificação do sistema.

## Comunicação MQTT

O sistema utiliza o protocolo MQTT para transmitir os dados de temperatura, umidade e classificação da condição térmica para um broker.

- Broker: `mqtt-dashboard.com`
- Porta: `1883`
- Tópico: `vacinas/dados`
- Formato das mensagens: JSON

## Resultados

Os registros da simulação e os resultados dos testes de tempo de resposta estão disponíveis na pasta `results/`.

## Documentação

- [Hardware](hardware/hardware.md)
- [Comunicação MQTT](protocols/mqtt.md)
- [Diagrama](hardware/diagrama.json)
- [Resultados](results/data/tempos-resposta.md)

## Licença

Consulte o arquivo LICENSE para informações sobre a licença do projeto.
