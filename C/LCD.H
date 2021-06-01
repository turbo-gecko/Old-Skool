/*
 * LCD.H - I2C LCD driver by Gary Hammond
 *
 * V1.0.0 01/06/2021 - Initial version
 */

void LCD_Init(void);
void LCD_Busy_Wait();
void LCD_Cmd(int);
void LCD_Print(int);
