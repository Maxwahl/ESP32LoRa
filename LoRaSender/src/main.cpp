#include <SPI.h>
#include <LoRa.h>
#include <Arduino.h>
#include "SSD1306.h"

SSD1306  display(0x3c, 4, 15);

#define SS 18
#define RST 14
#define DI0 26
#define BAND 433E6 
int counter = 0;
void setup() {
    pinMode(25, OUTPUT);
    pinMode(16, OUTPUT);
    digitalWrite(16, LOW); // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(16, HIGH);
    Serial.begin(115200);
    while (!Serial); 
    display.init();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    SPI.begin(5, 19, 27, 18);
    LoRa.setPins(SS, RST, DI0);

    Serial.println("LoRa Sender");
    display.drawString(0, 0, "LoRa Sender ");
    display.display();
    delay(2000);
    display.clear();
    if (!LoRa.begin(BAND)) {
        Serial.println("Starting LoRa failed!");
        display.drawString(5, 5, "Starting LoRa failed!");
        while (1);
    }
    display.display();
    delay(2000);
    display.clear();
    Serial.println("LoRa Initial OK!");
    display.drawString(0, 0, "LoRa Initial OK!");
    display.display();
    delay(2000);
}

void loop() {
    display.clear();
    Serial.print("Sending packet: ");
    Serial.println(counter);
    display.drawString(0,0,"Sending packet:  "+String(counter));
    display.display();
    // send packet
    LoRa.beginPacket() ;
    LoRa.print("Hello ") ;
    LoRa.print(counter) ;
    LoRa.endPacket();
    counter++;
    delay(10000);
}