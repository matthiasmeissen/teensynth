#include "Display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void initDisplay() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
}

void drawDisplay() {
    display.display();
}

void clearDisplay() {
    display.clearDisplay();
}

void compLabel(int posX, int posY, char* label) {
  display.drawRoundRect(posX, posY, 32, 32, 2, SSD1306_WHITE);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(posX + 8, posY + 14);
  display.println(label); 
}

void compKnob(int posX, int posY, float value, char* label) {
  display.drawCircle(posX + 15, posY + 11, 10, SSD1306_WHITE);
  display.drawPixel(posX + 15 + (cos(value * (2 * PI) + (0.5 * PI)) * 7), posY + 11 + (sin(value * (2 * PI) + (0.5 * PI)) * 7), SSD1306_WHITE);
  display.drawPixel(posX + 15 + (cos(value * (2 * PI) + (0.5 * PI)) * 8), posY + 11 + (sin(value * (2 * PI) + (0.5 * PI)) * 8), SSD1306_WHITE);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(posX + 8, posY + 23);
  display.println(label);
}

void compSlider(int posX, int posY, float value, char* label) {
  display.drawLine(posX + 12, posY + 1, posX + 18, posY + 1, SSD1306_WHITE);
  display.drawLine(posX + 12, posY + 21, posX + 18, posY + 21, SSD1306_WHITE);
  display.drawLine(posX + 11, posY + 2, posX + 11, posY + 20, SSD1306_WHITE);
  display.drawLine(posX + 19, posY + 2, posX + 19, posY + 20, SSD1306_WHITE);

  for (size_t i = 0; i < 10; i++) {
    display.drawPixel(posX + 13, (posY + 3) + i * 2, SSD1306_WHITE);
    display.drawPixel(posX + 17, (posY + 3) + i * 2, SSD1306_WHITE);
  }

  for (size_t i = 0; i < 17 * value; i++) {
    display.drawLine(posX + 13, (posY + 19) - i, posX + 17, (posY + 19) - i, SSD1306_WHITE);
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(posX + 8, posY + 23);
  display.println(label);
}
