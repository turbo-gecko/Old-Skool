/*
 * LCD.H - I2C LCD driver by Gary Hammond
 *
 * V1.0.0 01/06/2021 - Initial version
 */

#define LCD_BLINK  0x01
#define LCD_CURSOR 0x02
#define LCD_ON     0x04

void LCD_Init(void);
void LCD_Busy_Wait(void);
void LCD_Clear(void);
void LCD_Cmd(int);
void LCD_Cursor(int, int);
void LCD_Display(int);
void LCD_Print(char *);
void LCD_Print_Char(int);

