/*
 * TESTER.C - TESTER program by Gary Hammond
 *
 * Program for testing the Z80
 *
 * V1.0.0 12 Aug 2021
 */

#include <conio.h>
#include <string.h>

#include <I2C.H>
#include <LCD.H>
#include <UTILS.H>

void LED_7Seg(int number);

main()
{
  int count = 0;
  char str_count[21];

  printf("Program for testing the RC80\n");
  printf("Press <ENTER> to exit\n");

  I2C_Init();
  LCD_Init();
  LCD_Clear();
  LCD_Display(LCD_ON);

  LCD_Cursor(1, 1);
  LCD_Print("RC80 Tester");

  LED_7Seg(-1);

  for (count = 0; count < 10000; count++)
  {
    LED_7Seg(count);
    LCD_Cursor(2, 1);
    LCD_Print("Count = ");
    sprintf(str_count, "%d", count);
    LCD_Cursor(2, 9);
    LCD_Print(str_count);
    if(kbhit())
    {
      getch();
      break;
    }
  }

  LCD_Clear();
}

void LED_7Seg(int number)
{
  int digit = 0;
  int port_num = 0;

  if (number < 0 || number > 9999)
  {
    for (port_num = 56; port_num <= 59; port_num++)
    {
      out(port_num, 10);
      out(port_num + 4, 0);
    }
  }
  else 
  {
    digit = number / 1000;
    number = number % 1000;
    out(59, digit);
    digit = number / 100;
    number = number % 100;
    out(58, digit);
    digit = number / 10;
    number = number % 10;
    out(57, digit);
    digit = number;
    out(56, digit);
  }
}

