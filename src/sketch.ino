#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Definição dos pinos
#define DHT_PIN 15
#define DHT_TYPE DHT22
#define LED_GREEN 2
#define LED_YELLOW 4
#define LED_RED 5
#define BUZZER 18

// Configuração da rede Wi-Fi
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

// Configuração do MQTT
const char* MQTT_BROKER = "mqtt-dashboard.com";
const int MQTT_PORT = 1883;

// Tópico MQTT
const char* TOPICO_DADOS = "vacinas/dados";

DHT dht(DHT_PIN, DHT_TYPE);

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// LCD 16x2 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);


// Conectar ao Wifi
void conectarWiFi() {

  Serial.print("Conectando ao Wi-Fi");

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// Conectar ao MQTT
void conectarMQTT() {

  while (!mqttClient.connected()) {

    Serial.println("Conectando ao broker MQTT...");

    String clientId = "ESP32-Vacinas-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {

      Serial.println("MQTT conectado!");

    } else {

      Serial.print("Falha na conexão MQTT. Codigo: ");
      Serial.println(mqttClient.state());

      Serial.println("Tentando novamente em 5 segundos...");

      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  // Configuração dos pinos
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Monitor Vacinas");

  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  delay(2000);

  conectarWiFi();

  // Configuração do MQTT
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);

  Serial.println();
  Serial.println("================================");
  Serial.println("Sistema iniciado!");
  Serial.println("================================");
}

void loop() {

  if (!mqttClient.connected()) {
    conectarMQTT();
  }

  mqttClient.loop();

  // Leitura do sensor DHT22
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {

    Serial.println("Erro ao ler o DHT22!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no DHT22");

    delay(2000);

    return;
  }

  // Determinar status
  String statusAtual;
  String ledAcionado;
  String estadoBuzzer;

  // Faixa NORMAL
  if (temperatura >= 2.5 && temperatura <= 7.5) {

    // VERDE
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

    noTone(BUZZER);

    statusAtual = "NORMAL";
    ledAcionado = "LED VERDE";
    estadoBuzzer = "DESLIGADO";
  }

  // Faixa ATENCAO
  else if (
    (temperatura >= 2.0 && temperatura < 2.5) ||
    (temperatura > 7.5 && temperatura <= 8.0)
  ) {

    // AMARELO
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);

    noTone(BUZZER);

    statusAtual = "ATENCAO";
    ledAcionado = "LED AMARELO";
    estadoBuzzer = "DESLIGADO";
  }

  // Faixa ALERTA

  else {

    // VERMELHO

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);

    statusAtual = "ALERTA";

    ledAcionado = "LED VERMELHO";
    estadoBuzzer = "LIGADO";

    tone(BUZZER, 1000);

    delay(1000);

    noTone(BUZZER);

    estadoBuzzer = "DESLIGADO";
  }

  // Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" C | Umidade: ");
  Serial.print(umidade, 1);
  Serial.print(" % | Status: ");
  Serial.print(statusAtual);
  Serial.print(" | ");
  Serial.print(ledAcionado);
  Serial.print(": LIGADO | BUZZER: ");
  Serial.println(estadoBuzzer);

  // LCD
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(statusAtual);

  // Mensagem JSON
  String mensagem = "{";
  mensagem += "\"temperatura\":" + String(temperatura, 1) + ",";
  mensagem += "\"umidade\":" + String(umidade, 1) + ",";
  mensagem += "\"status\":\"" + statusAtual + "\"";
  mensagem += "}";

  // Publicacao dos dados no tópico
  bool publicado = mqttClient.publish(
    TOPICO_DADOS,
    mensagem.c_str()
  );

  // Verificar publicação
  if (publicado) {
    Serial.println("Dados enviados ao MQTT:");
    Serial.println(mensagem);
  } else {
    Serial.println("Falha ao publicar dados no MQTT!");
  }

  delay(2000);
}
