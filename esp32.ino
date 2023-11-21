// Adicionamos as bibliotecas que serão utilizadas
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "DHTesp.h"

// Configuração do DHT22
const int DHT_PIN = 15;
DHTesp dhtSensor;

// Configuração do LC
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Configuração do MQTT
EspMQTTClient client{
  "Wokwi-GUEST",  //SSID do WiFi
  "",  // Senha do wifi
  "mqtt.tago.io",  // Endereço do servidor
  "Default",  // Usuario
  "70de94f2-1cfb-4f85-b94b-7dee0b6ef274",  // Token do device
  "esp",  // Nome do device
  1883  // Porta de comunicação
};

void setup() {
  // Inicialização do Display LCD  
  lcd.init();
  lcd.backlight();
  
  // Inicialização do sensor DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Comunicação serial
  Serial.begin(9600);
  Serial.println("Conectando WiFi");
  
  while (!client.isWifiConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
    }
    Serial.println("WiFi Conectado");
    Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
      Serial.print('.'); client.loop(); delay(1000);
    }
  Serial.println("MQTT Conectado");
}

  // Callback da EspMQTTClient
  void onConnectionEstablished()
  {}
  char bufferJson[100];

void loop() {
  // Leitura de temperatura e umidade do sensor DHT22
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  
  // Exibir no Serial Monitor
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");

  // Exibir no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(data.humidity, 1) + "%");

  // Aguardar por uma nova leitura do sensor (DHT22 tem uma taxa de amostragem de ~0.5Hz)
  delay(2000);

  // Enviar para o servidor MQTT
  StaticJsonDocument<300> documentoJson;
  documentoJson["temperature"] = data.temperature;
  documentoJson["humidity"] = data.humidity;
  char bufferJson[100];
  serializeJson(documentoJson, bufferJson);
  client.publish("topicoTDSPI", bufferJson);
  delay(2000);
  client.loop();
}