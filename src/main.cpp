#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"
#include <LiquidCrystal.h>

const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 14, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");

  Serial.println(WiFi.localIP());
  lcd.begin(16, 2);

}


void loop() {
  HTTPClient http;

  http.begin(endpoint.c_str());

  http.addHeader("api-key", api_key);

  int httpResponseCode = http.GET();

  if(httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String responseBody = http.getString();
    Serial.println(responseBody);

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, responseBody);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    String line_1 = doc["line_1"]; // nullptr
    String line_2 = doc["line_2"]; // nullptr

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line_1);
    lcd.setCursor(0,1);
    lcd.print(line_2);
    

    }
    else{
      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }
  
    http.end();

}
