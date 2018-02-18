/*
** lcd.h
**
** LCD 3310 driver
** Target: ATMEGA :: AVR-GCC
**
*/
#ifndef __LCD_H_
#define __LCD_H_

/* Lcd screen size */
#define LCD_X_RES 84
#define LCD_Y_RES 48
#define LCD_CACHE_SIZE ((LCD_X_RES * LCD_Y_RES) / 8)


/* Pinout for LCD */
#define LCD_CLK_PIN 	(1<<PC4)
#define LCD_DATA_PIN 	(1<<PC3)
#define LCD_DC_PIN 		(1<<PC2)
#define LCD_CE_PIN 		(1<<PC1)
#define LCD_RST_PIN		(1<<PC0)
#define LCD_PORT		PORTC
#define LCD_DDR			DDRC


/* Special Chars */
#define ARROW_RIGHT	ICON(0)
#define ARROW_LEFT 	ICON(1)
#define ARROW_UP 	ICON(2)
#define ARROW_DOWN 	ICON(3)
#define STOP 		ICON(4)
#define PLAY	 	ICON(5)

/* Function for my special int8_tacters */
#define	ICON(x)		'z'+1+x

void lcd_init(void);
void lcd_contrast(uint8_t contrast);
void lcd_clear(void);
void lcd_clear_area(uint8_t line, uint8_t startX, uint8_t endX);
void lcd_clear_line(uint8_t line);
void lcd_goto_xy(uint8_t x, uint8_t y);
void lcd_goto_xy_exact(uint8_t x, uint8_t y);
void lcd_chr(int8_t chr);
int16_t lcd_chr_printf(int8_t chr, FILE *stream);
void lcd_int(uint16_t chr);
void lcd_str(int8_t* str);
void lcd_invert(void);
void lcd_normal(void);
extern uint8_t invert;

#endif



