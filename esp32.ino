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

  // Exibir no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");

  lcd.setCursor(0, 1);
  lcd.print("Oxygen: " + String(data.humidity, 1) + "%");


// Enviar para o servidor MQTT
StaticJsonDocument<300> documentTemperature;
documentTemperature["variable"] = "temperature";
documentTemperature["value"] = data.temperature;

StaticJsonDocument<300> documentOxygen;
documentOxygen["variable"] = "oxygen";
documentOxygen["value"] = data.humidity;

// Serializar e enviar a leitura de temperatura
char bufferTemperature[100];
serializeJson(documentTemperature, bufferTemperature);
Serial.println(bufferTemperature);
client.publish("leituras/temperatura", bufferTemperature);
delay(2000);
client.loop();

// Serializar e enviar a leitura de oxigenação
char bufferOxygen[100];
serializeJson(documentOxygen, bufferOxygen);
Serial.println(bufferOxygen);
client.publish("leituras/oxigenacao", bufferOxygen);
delay(2000);
client.loop();

}