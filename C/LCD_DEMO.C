/*
 * LCD_DEMO.C - I2C LCD demo program by Gary Hammond
 *
 * V1.0.0 01/06/2021
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
  printf("\nLCD Demonstration\n");
  printf("===================\n");

  LCD_Init();

  LCD_Cmd(0x01);
  LCD_Cmd(0x80);
  LCD_Print(0x31);
  LCD_Cmd(0xC0);
  LCD_Print(0x32);
  
  printf("===================\n");
}


