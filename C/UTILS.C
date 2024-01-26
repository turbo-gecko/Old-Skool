/*
 * Miscellaneous utility functions by Gary Hammond
 *
 * V1.0.1 30/05/2021 - Added BDCto Decimal and Decimal_To_BCD functions
 * V1.0.0 29/05/2021
 */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE   76
#define MAX_KEY_SIZE    38
#define MAX_VALUE_SIZE  76

char BCD_To_Decimal (char bcd_byte)
{
   return((bcd_byte / 16 * 10) + (bcd_byte % 16));
}

char Decimal_To_BCD (char decimal_byte)
{
 return (((decimal_byte / 10) << 4) | (decimal_byte % 10));
}

/*
 * For RC2014 platform with a Z80 running at 7.3728MHz, the time delay can
 * be approximately calculated in micro seconds as
 * delay(uS) = (count * 29.2) + 67.2
 * 
 * This means the shortest delay with count = 1 is approx. 116uS
 * With count = 1000 this is approx. 29.2mS
 */
void Delay(unsigned int count)
{
  while(count > 0)
  {
    --count;
  }
}

/*
 * Displays a text file that is no longer than 80 characters per line
 */
void Display_File(char* filename)
{
  FILE *fp;
  
  char *result;
  char line[82];

  fp = fopen(filename, "r");

  if (fp == NULL)
  {
    perror("Error while opening %s\n", filename);
    exit(1);
  }

  result = fgets(line, 82, fp);
  while(result != NULL)
  {
    printf("%s", result);
    result = fgets(line, 82, fp);
  }
  fclose(fp);
}

/*
 * Converts a hex number in string format to an unsigned integer
 */
unsigned Hex_To_Int(char *hex)
{
  unsigned val = 0;

  while (*hex)
  {
    char byte = *hex++; 
        
    if (byte >= '0' && byte <= '9')
      {
          byte = byte - '0';
      }
      else if (byte >= 'a' && byte <='f')
      {
          byte = byte - 'a' + 10;
      }
      else if (byte >= 'A' && byte <='F')
      {
          byte = byte - 'A' + 10;
      }

      val = (val << 4) | (byte & 0xF);
    }
  return val;
}

void Pause(void)
{
  while(!kbhit())
  {
    /* do nothing */
  }
  getch();
}

/*
 * Reads a key/value pair from a text file in the format of
 * <key>=<value>
 * Function returns the string <value> if found or an empty string
 * if the <key> is not found in the file.
 * Lines beginning with # are ignored as comments.
 */
char * Read_Cfg_Item(char *filename, char *key)
{
  FILE *fp;
  
  char *result;
  int temp_int;

  static char line[MAX_LINE_SIZE];
  static char current_key[MAX_KEY_SIZE];

  fp = fopen(filename, "r");

  if (fp == NULL)
  {
    perror("Error while opening config file\n");
    exit(1);
  }

  result = fgets(line, MAX_LINE_SIZE, fp);
  while(result != NULL)
  {
    temp_int = strncmp(line, "#", 1);
    if ( temp_int != 0)
    {
      result = strchr(line, '=');
      if (result != NULL)
      {
        sscanf(line, "%s=", current_key);
        if (strcmp(current_key, key) == 0)
        {
          fclose(fp);
          strcpy(&line[0], result + 1);
          line[strlen(line) - 1] = 0;
          return line;
        }
      }
    }
    result = fgets(line, MAX_LINE_SIZE, fp);
  }
  fclose(fp);
  return "";
}

