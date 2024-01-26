/*
 * LCD_CLI.C - I2C LCD command line interface by Gary Hammond
 *
 * This is designed to work on a generic I2C LCD display
 *
 * V1.0.1 06/02/2022 - Added ability to display test at a specified line
 *                   - Added BLINK, CURSOR and OFF commands
 *                   - Added help text
 *                   - Added use of language files for messages and usage
 * V1.0.0 05/08/2021 - Initial version
 */

#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LCD_OFF    0x00 /* Turn off the LCD display */
#define LCD_BLINK  0x01 /* Blink at current cursor position */
#define LCD_CURSOR 0x02 /* Turn on the cursor underscore */
#define LCD_ON     0x04 /* Turn on the LCD display backlighting */

#define LC_LANG_FILE "LC-LANG.CFG"

unsigned char LCD_Init(void);
void Process_Command(char * command);
char * Read_Cfg_Item(char *filename, char *key);

static char message_file[13];

main(argc, argv)
int argc;
char *argv[];
{
  unsigned char result;

  if (argc == 1)
  {
    Display_File(Read_Cfg_Item(LC_LANG_FILE, "USAGE"));
    exit(0);
  }

  strcpy(message_file, Read_Cfg_Item(LC_LANG_FILE, "MESSAGES"));

  I2C_Init();
  result = LCD_Init();
  
  if (result > 0)
  {
    printf("%s\n", Read_Cfg_Item(message_file, "M3"));
    exit(1);
  }

  if (argc == 2)
  {
    Process_Command(argv[1]);
  }

  if (argc == 3)
  {
    printf("%s\n", Read_Cfg_Item(message_file, "M5"));
    exit(1);
  }

  if (argc >= 4)
  {
    int i;
    int column, row;

    column = atoi(argv[2]);
    row = atoi(argv[1]);
    
    if (column < 1)
    {
      printf("%s\n", Read_Cfg_Item(message_file, "M1"));
      exit(1);
    }

    if (row < 1)
    {
      printf("%s\n", Read_Cfg_Item(message_file, "M4"));
      exit(1);
    }

    LCD_Cursor(row, column);
    for (i = 3; i < argc; i++)
    {
      LCD_Print(argv[i]);
      if (i < (argc - 1))
      {
        LCD_Print(" ");
      }
    }
  }
  exit(0);
}

void Process_Command(char * command)
{
  if (strcmp("HELP", command) == 0)
  {
    Display_File(Read_Cfg_Item(LC_LANG_FILE, "USAGE"));
  }
  else if (strcmp("BLINK", command) == 0)
  {
    LCD_Display(LCD_ON|LCD_BLINK);
  }
  else if (strcmp("CLEAR", command) == 0)
  {
    LCD_Clear();
  }
  else if (strcmp("CURSOR", command) == 0)
  {
    LCD_Display(LCD_ON|LCD_CURSOR);
  }
  else if (strcmp("OFF", command) == 0)
  {
    LCD_Display(LCD_OFF);
  }
  else if (strcmp("ON", command) == 0)
  {
    LCD_Display(LCD_ON);
  }
  else 
  {
    printf("%s\n", Read_Cfg_Item(message_file, "M2"));
    Display_File(Read_Cfg_Item(LC_LANG_FILE, "USAGE"));
    exit(1);
  }
  exit(0);
}

