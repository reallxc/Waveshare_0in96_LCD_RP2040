#include "Waveshare_0in96.h"

LCD_0IN96_ATTRIBUTES LCD_0IN96;

// LCD Reset
static void LCD_0IN96_Reset(void) {
    digitalWrite(LCD_RST, HIGH);
    delay(200);
    digitalWrite(LCD_RST, LOW);
    delay(200);
    digitalWrite(LCD_RST, HIGH);
    delay(200);
}

// Send command to LCD
static void LCD_0IN96_SendCommand(uint8_t cmd) {
    digitalWrite(LCD_DC, LOW);
    digitalWrite(LCD_CS, LOW);
    SPI1.transfer(cmd);
    digitalWrite(LCD_CS, HIGH);
}

// Send data to LCD
static void LCD_0IN96_SendData_8Bit(uint8_t data) {
    digitalWrite(LCD_DC, HIGH);
    digitalWrite(LCD_CS, LOW);
    SPI1.transfer(data);
    digitalWrite(LCD_CS, HIGH);
}

static void LCD_0IN96_InitReg(void)
{
    LCD_0IN96_SendCommand(0x11); // Sleep out
    delay(120);
    
    LCD_0IN96_SendCommand(0x21); // Display inversion on
    LCD_0IN96_SendCommand(0x21);

    LCD_0IN96_SendCommand(0xB1); // Frame rate control
    LCD_0IN96_SendData_8Bit(0x05);
    LCD_0IN96_SendData_8Bit(0x3A);
    LCD_0IN96_SendData_8Bit(0x3A);
    
    LCD_0IN96_SendCommand(0xB2); // Frame rate control
    LCD_0IN96_SendData_8Bit(0x05);
    LCD_0IN96_SendData_8Bit(0x3A);
    LCD_0IN96_SendData_8Bit(0x3A);

    LCD_0IN96_SendCommand(0xB3); // Frame rate control
    LCD_0IN96_SendData_8Bit(0x05);
    LCD_0IN96_SendData_8Bit(0x3A);
    LCD_0IN96_SendData_8Bit(0x3A);
    LCD_0IN96_SendData_8Bit(0x05);
    LCD_0IN96_SendData_8Bit(0x3A);
    LCD_0IN96_SendData_8Bit(0x3A);

    LCD_0IN96_SendCommand(0xB4); // Frame rate control
    LCD_0IN96_SendData_8Bit(0x03);

    LCD_0IN96_SendCommand(0xC0); // Power control
    LCD_0IN96_SendData_8Bit(0x62);
    LCD_0IN96_SendData_8Bit(0x02);
    LCD_0IN96_SendData_8Bit(0x04);
    
    LCD_0IN96_SendCommand(0xC1);
    LCD_0IN96_SendData_8Bit(0xC0);
    
    LCD_0IN96_SendCommand(0xC2);
    LCD_0IN96_SendData_8Bit(0x0D);
    LCD_0IN96_SendData_8Bit(0x00);
    
    LCD_0IN96_SendCommand(0xC3);
    LCD_0IN96_SendData_8Bit(0x8D);
    LCD_0IN96_SendData_8Bit(0x6A);
    
    LCD_0IN96_SendCommand(0xC4);
    LCD_0IN96_SendData_8Bit(0x8D);
    LCD_0IN96_SendData_8Bit(0xEE);
    
    LCD_0IN96_SendCommand(0xC5); // Set pixel format to 16-bit color
    LCD_0IN96_SendData_8Bit(0x0E);

    LCD_0IN96_SendCommand(0xE0);
	LCD_0IN96_SendData_8Bit(0x10);
	LCD_0IN96_SendData_8Bit(0x0E);
	LCD_0IN96_SendData_8Bit(0x02);
	LCD_0IN96_SendData_8Bit(0x03);
	LCD_0IN96_SendData_8Bit(0x0E);
	LCD_0IN96_SendData_8Bit(0x07);
	LCD_0IN96_SendData_8Bit(0x02);
	LCD_0IN96_SendData_8Bit(0x07);
	LCD_0IN96_SendData_8Bit(0x0A);
	LCD_0IN96_SendData_8Bit(0x12);
	LCD_0IN96_SendData_8Bit(0x27);
	LCD_0IN96_SendData_8Bit(0x37);
	LCD_0IN96_SendData_8Bit(0x00);
	LCD_0IN96_SendData_8Bit(0x0D);
	LCD_0IN96_SendData_8Bit(0x0E);
	LCD_0IN96_SendData_8Bit(0x10);

	LCD_0IN96_SendCommand(0xE1);
	LCD_0IN96_SendData_8Bit(0x10);
	LCD_0IN96_SendData_8Bit(0x0E);
	LCD_0IN96_SendData_8Bit(0x03);
	LCD_0IN96_SendData_8Bit(0x03);
	LCD_0IN96_SendData_8Bit(0x0F);
	LCD_0IN96_SendData_8Bit(0x06);
	LCD_0IN96_SendData_8Bit(0x02);
	LCD_0IN96_SendData_8Bit(0x08);
	LCD_0IN96_SendData_8Bit(0x0A);
	LCD_0IN96_SendData_8Bit(0x13);
	LCD_0IN96_SendData_8Bit(0x26);
	LCD_0IN96_SendData_8Bit(0x36);
	LCD_0IN96_SendData_8Bit(0x00);
	LCD_0IN96_SendData_8Bit(0x0D);
	LCD_0IN96_SendData_8Bit(0x0E);
	LCD_0IN96_SendData_8Bit(0x10);

	LCD_0IN96_SendCommand(0x3A); 
	LCD_0IN96_SendData_8Bit(0x05);

	LCD_0IN96_SendCommand(0x36);
	LCD_0IN96_SendData_8Bit(0xA8);

    LCD_0IN96_SendCommand(0x29); // Display on
}

void LCD_0IN96_Init()
{
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_DC, OUTPUT);
    pinMode(LCD_RST, OUTPUT);
    pinMode(LCD_BL, OUTPUT);

    SPI1.setSCK(LCD_CLK);
    SPI1.setTX(LCD_DIN);
    SPI1.begin();
    SPI1.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

    digitalWrite(LCD_BL, HIGH);
    LCD_0IN96_Reset();

    LCD_0IN96.HEIGHT	= LCD_0IN96_HEIGHT;       
    LCD_0IN96.WIDTH   = LCD_0IN96_WIDTH;

    LCD_0IN96_InitReg();
}

void LCD_0IN96_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
	Xstart = Xstart + 1;
	Xend = Xend + 1;
	Ystart = Ystart + 26;
	Yend = Yend+26;
	
	LCD_0IN96_SendCommand(0x2a);
	LCD_0IN96_SendData_8Bit(Xstart >> 8);
	LCD_0IN96_SendData_8Bit(Xstart);
	LCD_0IN96_SendData_8Bit(Xend >> 8);
	LCD_0IN96_SendData_8Bit(Xend );

	LCD_0IN96_SendCommand(0x2b);
	LCD_0IN96_SendData_8Bit(Ystart >> 8);
	LCD_0IN96_SendData_8Bit(Ystart);
	LCD_0IN96_SendData_8Bit(Yend >> 8);
	LCD_0IN96_SendData_8Bit(Yend);

	LCD_0IN96_SendCommand(0x2C);
}

// Fill screen with a color
void LCD_0IN96_Clear(uint16_t color) {
    uint16_t j,i;
    uint16_t Image[LCD_0IN96.WIDTH*LCD_0IN96.HEIGHT];
    
    color = ((color<<8)&0xff00)|(color>>8);
   
    for (j = 0; j < LCD_0IN96.HEIGHT*LCD_0IN96.WIDTH; j++) {
        Image[j] = color;
    }
    
    LCD_0IN96_SetWindows(0, 0, LCD_0IN96.WIDTH-1, LCD_0IN96.HEIGHT-1);
    digitalWrite(LCD_DC, HIGH);
    digitalWrite(LCD_CS, LOW);
	
    for (uint32_t i = 0; i < LCD_0IN96.WIDTH * LCD_0IN96.HEIGHT; i++) {
        SPI1.transfer(color >> 8);
        SPI1.transfer(color & 0xFF);
    }
    digitalWrite(LCD_CS, HIGH);
}