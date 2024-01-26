/*
 * LCD_DEMO.C - I2C LCD demo program by Gary Hammond
 *
 * This is designed to work on a 2 line by 16 character LCD display
 *
 * V1.0.0 05/06/2021
 */

#include <conio.h>
#include <string.h>

#include <I2C.H>
#include <LCD.H>
#include <UTILS.H>

void LCD_Demo();

main()
{
  printf("Demonstration program for I2C LCD\n");
  I2C_Init();
  LCD_Demo();
}

void LCD_Demo()
{
  LCD_Init();
  LCD_Clear();

  printf("\nLCD Demonstration\n");
  printf("===================\n");
  printf("Writing to line 1\n");
  LCD_Display(LCD_ON);
  LCD_Cursor(1, 1);
  LCD_Print("I2C LCD Demo");
  Pause();

  printf("Writing to line 2 with blinking cursor\n");
  LCD_Clear();
  LCD_Display(LCD_ON | LCD_CURSOR | LCD_BLINK);
  LCD_Cursor(2, 1);
  LCD_Print("Blinking cursor");
  Pause();
  
  printf("Writing to line 3 with steady cursor\n");
  LCD_Clear();
  LCD_Display(LCD_ON | LCD_CURSOR);
  LCD_Cursor(3, 1);
  LCD_Print("Steady cursor");
  Pause();

  printf("Writing to line 4 with blinking block\n");
  LCD_Clear();
  LCD_Display(LCD_ON | LCD_BLINK);
  LCD_Cursor(4, 1);
  LCD_Print("Blinking block");
  Pause();
  
  printf("Writing to line 1 with no cursor\n");
  LCD_Clear();
  LCD_Display(LCD_ON);
  LCD_Cursor(1, 1);
  LCD_Print("No cursor");
  Pause();

  printf("All done!\n");
  LCD_Clear();
  LCD_Display(LCD_ON);
  LCD_Cursor(1, 5);
  LCD_Print("I2C LCD");
  LCD_Cursor(2, 2);
  LCD_Print("Demonstration");
  printf("===================\n");
}


