# Avaliação dos Tempos de Resposta

## Metodologia

Foram realizadas quatro medições para avaliar os tempos de resposta dos componentes e das operações do ThermoVac. Foram considerados o intervalo entre a leitura do sensor DHT22 e o recebimento dos dados pelo broker MQTT e o intervalo de tempo entre a execução do comando e o acionamento dos LEDs, do buzzer e atualização do display LCD.

## Resultados

| Operação | Medição 1 | Medição 2 | Medição 3 | Medição 4 | Média |
|---|---:|---:|---:|---:|---:|
| DHT22 -> MQTT (ms) | 684 | 698 | 647 | 639 | 667 |
| Comando -> LED verde (µs) | 37 | 38 | 39 | 37 | 37,75 |
| Comando -> LED amarelo (µs) | 46 | 46 | 47 | 47 | 46,50 |
| Comando -> LED vermelho (µs) | 55 | 55 | 57 | 56 | 55,75 |
| Comando -> Buzzer (µs) | 983 | 982 | 984 | 966 | 978,75 |
| Comando -> Display LCD (ms) | 72 | 68 | 70 | 69 | 69,75 |

De modo geral, os resultados indicam que o ESP32 executou corretamente os comandos de acionamento dos LEDs e do buzzer, atualizou os dados no display e publicou as informações por meio do protocolo MQTT. Dessa forma, o protótipo apresentou agilidade na sinalização local e na transmissão dos dados para o monitoramento remoto, atendendo às funcionalidades propostas para o sistema.
