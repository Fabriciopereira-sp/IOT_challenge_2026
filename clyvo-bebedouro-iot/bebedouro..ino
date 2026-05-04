#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

// ── Pinos ──────────────────────────────────────────
#define PIN_TRIG     25
#define PIN_ECHO     35
#define PIN_LED       2
#define PIN_DHT       4
#define SCREEN_W    128
#define SCREEN_H     64

// ── WiFi e MQTT ────────────────────────────────────
const char* WIFI_SSID     = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const char* MQTT_BROKER   = "broker.hivemq.com";
const int   MQTT_PORT     = 1883;

// ID ÚNICO para não desconectar o outro projeto
const char* MQTT_CLIENT   = "clyvo-bebedouro-pro-99"; 

// Tópicos Isolados
const char* TOPIC_NIVEL   = "clyvo/vet/bebedouro/nivel";
const char* TOPIC_TEMP    = "clyvo/vet/bebedouro/temp";
const char* TOPIC_UMID    = "clyvo/vet/bebedouro/umid";
const char* TOPIC_ALERTA  = "clyvo/vet/bebedouro/alerta";

// ── Objetos ────────────────────────────────────────
DHT dht(PIN_DHT, DHT22);
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

unsigned long ultimaLeitura = 0;
const long INTERVALO = 3000;

void conectarMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Bebedouro conectando MQTT...");
    if (mqtt.connect(MQTT_CLIENT)) {
      Serial.println(" OK!");
    } else {
      delay(2000);
    }
  }
}

int lerDistancia() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  long dur = pulseIn(PIN_ECHO, HIGH, 30000);
  if (dur == 0) return -1;
  return dur * 0.034 / 2;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED,  OUTPUT);
  dht.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) Serial.println("OLED Erro");
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  mqtt.setServer(MQTT_BROKER, MQTT_PORT);
}

void loop() {
  if (!mqtt.connected()) conectarMQTT();
  mqtt.loop();

  unsigned long agora = millis();
  if (agora - ultimaLeitura >= INTERVALO) {
    ultimaLeitura = agora;

    int dist   = lerDistancia();
    float temp = dht.readTemperature();
    float umid = dht.readHumidity();

    if (dist < 0 || isnan(temp)) return;

    bool alerta = (dist > 20); // Vazio se > 20cm
    digitalWrite(PIN_LED, alerta ? HIGH : LOW);

    // Envio para MQTT com chaves simplificadas
    StaticJsonDocument<100> doc;
    char buf[100];

    // Nível
    doc.clear();
    doc["valor"] = dist;
    doc["status"] = alerta ? "vazio" : "ok";
    serializeJson(doc, buf);
    mqtt.publish(TOPIC_NIVEL, buf);

    // Temperatura
    doc.clear();
    doc["valor"] = temp;
    serializeJson(doc, buf);
    mqtt.publish(TOPIC_TEMP, buf);

    // Umidade
    doc.clear();
    doc["valor"] = umid;
    serializeJson(doc, buf);
    mqtt.publish(TOPIC_UMID, buf);

    // Alerta dedicado
    if (alerta) mqtt.publish(TOPIC_ALERTA, "{\"msg\":\"vazio\"}");
    else mqtt.publish(TOPIC_ALERTA, "{\"msg\":\"ok\"}");

    // Display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0,0);
    display.println("CLYVO - BEBEDOURO");
    display.printf("\nNivel: %d cm", dist);
    display.printf("\nTemp: %.1f C", temp);
    display.display();
  }
}