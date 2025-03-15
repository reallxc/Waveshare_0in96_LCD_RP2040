#ifndef LCD_0IN96_DRIVER_H
#define LCD_0IN96_DRIVER_H

#include <Arduino.h>
#include <SPI.h>

#define BLACK       0x0000  // 黑色
#define WHITE       0xFFFF  // 白色
#define RED         0xF800  // 红色
#define GREEN       0x07E0  // 绿色
#define BLUE        0x001F  // 蓝色
#define CYAN        0x07FF  // 青色
#define MAGENTA     0xF81F  // 洋红色
#define YELLOW      0xFFE0  // 黄色
#define ORANGE      0xFC00  // 橙色
#define PURPLE      0x780F  // 紫色
#define GRAY        0x8410  // 灰色

#define LCD_CS     9   // Chip Select
#define LCD_DC     8   // Data/Command
#define LCD_RST    12  // Reset
#define LCD_BL     25  // Backlight
#define LCD_CLK    10
#define LCD_DIN    11

#define LCD_0IN96_WIDTH  160
#define LCD_0IN96_HEIGHT 80

#define HORIZONTAL 0
#define VERTICAL   1

typedef struct{
    uint16_t WIDTH;
    uint16_t HEIGHT;
    uint8_t SCAN_DIR;
}LCD_0IN96_ATTRIBUTES;
extern LCD_0IN96_ATTRIBUTES LCD_0IN96;

void LCD_0IN96_Init();
void LCD_0IN96_Clear(uint16_t Color);
void LCD_0IN96_Display(uint16_t *Image);
void LCD_0IN96_DisplayWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t *Image);
void LCD_0IN96_DisplayPoint(uint16_t X, uint16_t Y, uint16_t Color);

#endif