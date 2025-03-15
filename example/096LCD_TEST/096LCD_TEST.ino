#include "Waveshare_0in96.h"
#include <Adafruit_GFX.h>

// Custom class for LCD using Adafruit GFX
class LCD_0IN96_GFX : public Adafruit_GFX {
public:
    LCD_0IN96_GFX() : Adafruit_GFX(LCD_0IN96_WIDTH, LCD_0IN96_HEIGHT) {}

    void drawPixel(int16_t x, int16_t y, uint16_t color) override {
        LCD_0IN96_DisplayPoint(x, y, color); // Call your existing function
    }
};

// Create an instance of the class
LCD_0IN96_GFX display;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Initializing LCD...");

  LCD_0IN96_Init();
  LCD_0IN96_Clear(0x0000);
}

void loop() {
  Serial.println("Running LCD...");

  display.setTextSize(1);       // Set text size (1 = default, 2 = double, etc.)
  display.setTextColor(0xFFFF); // Set text color (white)
  display.setCursor(5, 5);    // Position text at (10,10)
  display.print("Hello, World!"); // Print text

  delay(1000);
  LCD_0IN96_Clear(0x0000);
}
