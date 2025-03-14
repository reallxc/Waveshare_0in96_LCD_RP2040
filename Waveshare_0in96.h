#ifndef LCD_0IN96_DRIVER_H
#define LCD_0IN96_DRIVER_H

#include <Arduino.h>
#include <SPI.h>

#define LCD_CS     9   // Chip Select
#define LCD_DC     8   // Data/Command
#define LCD_RST    12  // Reset
#define LCD_BL     25  // Backlight

#define LCD_WIDTH  160
#define LCD_HEIGHT 80

#define HORIZONTAL 0
#define VERTICAL   1

void LCD_InitSPI();
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Reset();
void LCD_Init();
void LCD_FillScreen(uint16_t color);

#endif