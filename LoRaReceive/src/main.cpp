#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h"

SSD1306  display(0x3c, 4, 15);
#define SS      18
#define RST     14
#define DI0     26

void setup() {
  pinMode(25, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);
  
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");
  display.drawString(5,5,"LoRa Receiver");
  display.display();
  delay(2000);
  display.clear();  

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  display.display();
  delay(2000);
  display.clear();
  Serial.println("LoRa Initial OK!");
  display.drawString(5, 5, "LoRa Initial OK!");
  display.display();
  delay(2000);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    display.clear();
    Serial.print("Received packet '");
    String msg = "";
    while (LoRa.available()) {
      msg = msg + ((char)LoRa.read());
    }
    Serial.print(msg);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    display.drawString(5,5,msg + " with RSSI "+String(LoRa.packetRssi()));
    display.display();
  }
}