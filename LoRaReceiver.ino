#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=/ 16, / clock=/ 15, / data=*/ 4);
void setup() {
  Serial.begin(9600);
  while (!Serial);
  u8g2.begin();
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      const char* string = (const char*)LoRa.read();
      Serial.print(string);
      u8g2.clearBuffer();

      // Set the font and print the text
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 20, string);

      u8g2.sendBuffer();

      delay(1000);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
