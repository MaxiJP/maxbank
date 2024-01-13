#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

Adafruit_SSD1306 maxOLED(128, 64);

void setup() {
  maxOLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  maxOLED.clearDisplay();
  maxOLED.setTextSize(2);
  maxOLED.setTextColor(SSD1306_WHITE);
  maxOLED.setCursor(0,0);
  maxOLED.print("-MAX BANK-");
  maxOLED.setTextSize(1);
  maxOLED.setCursor(40,40);
  maxOLED.print(millis());
  maxOLED.display();
} 
