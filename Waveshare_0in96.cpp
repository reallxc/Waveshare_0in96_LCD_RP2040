#include <Arduino.h>
#include <SPI.h>

// Define SPI1 pins for RP2040
#define LCD_CS     9   // Chip Select
#define LCD_DC     8   // Data/Command
#define LCD_RST    12  // Reset
#define LCD_BL     25  // Backlight

#define LCD_WIDTH  160
#define LCD_HEIGHT 80

// Initialize SPI1
void LCD_InitSPI() {
    SPI1.setSCK(10);
    SPI1.setTX(11);
    SPI1.begin();
}

// Send command to LCD
void LCD_SendCommand(uint8_t cmd) {
    Serial.print("Sending CMD: 0x");
    Serial.println(cmd, HEX);
    
    digitalWrite(LCD_DC, LOW);
    digitalWrite(LCD_CS, LOW);
    SPI1.transfer(cmd);
    //digitalWrite(LCD_CS, HIGH);
}

// Send data to LCD
void LCD_SendData(uint8_t data) {
    digitalWrite(LCD_DC, HIGH);
    digitalWrite(LCD_CS, LOW);
    SPI1.transfer(data);
    digitalWrite(LCD_CS, HIGH);
}

// LCD Reset
void LCD_Reset() {
    digitalWrite(LCD_RST, HIGH);
    delay(200);
    digitalWrite(LCD_RST, LOW);
    delay(200);
    digitalWrite(LCD_RST, HIGH);
    delay(200);
}

// LCD Initialization sequence
void LCD_Init() {
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_DC, OUTPUT);
    pinMode(LCD_RST, OUTPUT);
    pinMode(LCD_BL, OUTPUT);
    
    digitalWrite(LCD_BL, HIGH); // Turn on backlight
    LCD_Reset();
    
    LCD_SendCommand(0x11); // Sleep out
    delay(120);
    
    LCD_SendCommand(0x21); // Display inversion on
    LCD_SendCommand(0x21);

    LCD_SendCommand(0xB1); // Frame rate control
    LCD_SendData(0x05);
    LCD_SendData(0x3A);
    LCD_SendData(0x3A);
    
    LCD_SendCommand(0xB2); // Frame rate control
    LCD_SendData(0x05);
    LCD_SendData(0x3A);
    LCD_SendData(0x3A);

    LCD_SendCommand(0xB3); // Frame rate control
    LCD_SendData(0x05);
    LCD_SendData(0x3A);
    LCD_SendData(0x3A);
    LCD_SendData(0x05);
    LCD_SendData(0x3A);
    LCD_SendData(0x3A);

    LCD_SendCommand(0xB4); // Frame rate control
    LCD_SendData(0x03);

    LCD_SendCommand(0xC0); // Power control
    LCD_SendData(0x62);
    LCD_SendData(0x02);
    LCD_SendData(0x04);
    
    LCD_SendCommand(0xC1);
    LCD_SendData(0xC0);
    
    LCD_SendCommand(0xC2);
    LCD_SendData(0x0D);
    LCD_SendData(0x00);
    
    LCD_SendCommand(0xC3);
    LCD_SendData(0x8D);
    LCD_SendData(0x6A);
    
    LCD_SendCommand(0xC4);
    LCD_SendData(0x8D);
    LCD_SendData(0xEE);
    
    LCD_SendCommand(0xC5); // Set pixel format to 16-bit color
    LCD_SendData(0x0E);

    LCD_SendCommand(0xE0);
	LCD_SendData(0x10);
	LCD_SendData(0x0E);
	LCD_SendData(0x02);
	LCD_SendData(0x03);
	LCD_SendData(0x0E);
	LCD_SendData(0x07);
	LCD_SendData(0x02);
	LCD_SendData(0x07);
	LCD_SendData(0x0A);
	LCD_SendData(0x12);
	LCD_SendData(0x27);
	LCD_SendData(0x37);
	LCD_SendData(0x00);
	LCD_SendData(0x0D);
	LCD_SendData(0x0E);
	LCD_SendData(0x10);

	LCD_SendCommand(0xE1);
	LCD_SendData(0x10);
	LCD_SendData(0x0E);
	LCD_SendData(0x03);
	LCD_SendData(0x03);
	LCD_SendData(0x0F);
	LCD_SendData(0x06);
	LCD_SendData(0x02);
	LCD_SendData(0x08);
	LCD_SendData(0x0A);
	LCD_SendData(0x13);
	LCD_SendData(0x26);
	LCD_SendData(0x36);
	LCD_SendData(0x00);
	LCD_SendData(0x0D);
	LCD_SendData(0x0E);
	LCD_SendData(0x10);

	LCD_SendCommand(0x3A); 
	LCD_SendData(0x05);

	LCD_SendCommand(0x36);
	LCD_SendData(0xA8);

    LCD_SendCommand(0x29); // Display on
}

// Fill screen with a color
void LCD_FillScreen(uint16_t color) {
    LCD_SendCommand(0x2A); // Column address set
    LCD_SendData(0x00);
    LCD_SendData(0x00);
    LCD_SendData(0x00);
    LCD_SendData(LCD_WIDTH - 1);
    
    LCD_SendCommand(0x2B); // Row address set
    LCD_SendData(0x00);
    LCD_SendData(0x00);
    LCD_SendData(0x00);
    LCD_SendData(LCD_HEIGHT - 1);
    
    LCD_SendCommand(0x2C); // Memory write
    
    digitalWrite(LCD_DC, HIGH);
    digitalWrite(LCD_CS, LOW);
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        SPI1.transfer(color >> 8);
        SPI1.transfer(color & 0xFF);
    }
    digitalWrite(LCD_CS, HIGH);
}
