# Comunicação MQTT

## Protocolo MQTT

O MQTT (Message Queuing Telemetry Transport) é um protocolo de comunicação leve, baseado no modelo publish/subscribe, utilizado para a transmissão de mensagens entre dispositivos por meio de um broker.

No ThermoVac, o ESP32 atua como publicador (*publisher*), enviando os dados coletados pelo sensor DHT22 ao broker MQTT por meio da conexão Wi-Fi.

## Configuração da Comunicação

- **Broker:** `mqtt-dashboard.com`
- **Porta:** `1883`
- **Protocolo de transporte:** TCP/IP
- **Tópico:** `vacinas/dados`
- **Formato dos dados:** JSON

## Configurações de QoS

- QoS = 0 para todas as publicações.
- Retain = false.

## Reconexão e Tratamento de Falhas

1. O sistema verifica se o ESP32 está conectado ao broker MQTT.
2. Caso a conexão seja perdida, a função `conectarMQTT()` tenta restabelecê-la.
3. Em caso de falha, uma nova tentativa é realizada após um intervalo de 5 segundos.
4. O resultado da publicação é verificado e informado no Monitor Serial.

## Estrutura das Mensagens

As mensagens publicadas pelo ThermoVac são enviadas no formato JSON, contendo as seguintes informações:

| Campo | Tipo | Descrição |
|---|---|---|
| `temperatura` | float | Valor de temperatura medido pelo DHT22, em °C |
| `umidade` | float | Valor de umidade relativa do ar, em % |
| `status` | string | Classificação da condição de temperatura |

Exemplo de mensagem:

```json
{
  "temperatura": 5.5,
  "umidade": 60.0,
  "status": "NORMAL"
}
```

## Visualização dos Dados

As mensagens podem ser acompanhadas por meio de um cliente MQTT, realizando a conexão com o broker e a inscrição (*subscribe*) no tópico `vacinas/dados`.
