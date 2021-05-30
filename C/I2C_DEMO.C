/*
 * I2C_DEMO.C - I2C demo program by Gary Hammond
 *
 * This code is derived from the I2C demo Z80 assembler code for the SC126 
 * and the SC137 by Stephen J Cousins with some extra button check code.
 *
 * SC406 example is from code by Kurt Pieper. Thanks!
 *
 * V1.0.0 30/05/2021
 */

#include <conio.h>
#include <string.h>

#include <I2C.H>
#include <UTILS.H>

void Flash_LEDs(int);
void Read_Buttons(int);
void SC406_Demo();
void SC407_Demo();

main()
{
  printf("Demonstration program I2C modules\n");
  I2C_Init();
  SC406_Demo();
  SC407_Demo();
}

void Flash_LEDs(int pcf_out)
{
  /* Demo using the SC407 to flash alternate LED's
     Note: The SC407 LED's are active low so the values
     sent to light the LED's are inverted */
  char ret_code = 0;

  while(!kbhit())
  {
    /* Output alternate bit pattern 1 */
    I2C_Start();
    ret_code = I2C_Write(pcf_out);
    ret_code = I2C_Write(0xAA);
    I2C_Stop();

    /* Wait long enought to see it */
    Delay(20000);

    /* Output alternate bit pattern 2 */
    I2C_Start();
    ret_code = I2C_Write(pcf_out);
    ret_code = I2C_Write(0x55);
    I2C_Stop();

    /* Wait long enought to see it */
    Delay(20000);
  }
  getch();

  /* Turn off the LED's */
  I2C_Start();
  ret_code = I2C_Write(pcf_out);
  ret_code = I2C_Write(0xFF);
  I2C_Stop();
}

void Read_Buttons(int pcf_in)
{
  char ret_code = 0;
  int count = 0;
  unsigned char byte_read = 0;
  unsigned char last_byte_read = 0;

  /* Read the pushbuttons. Press a key to quit */
  I2C_Start();
  ret_code = I2C_Write(pcf_in);
  while(!kbhit())
  {
    byte_read = I2C_Read(ACK);

    if(byte_read != last_byte_read)
    {
      printf("Buttons = ");
      for (count = 7; count >= 0; count--)
      {
        if ((byte_read & (1 << count)) == 0)
        {
          printf("O");
        }
        else
        {
          printf("-");
        }
      }
      printf("\n");
    }
    last_byte_read = byte_read;
  }
  byte_read = I2C_Read(NACK);
  I2C_Stop();
  getch();
}

void Read_Temp(int tc74_addr)
{
  unsigned char bcd;
  unsigned char byte_read = 0;
  unsigned char last_byte_read = 0;
  unsigned char temperature;

  /* Read TC74. Press a key to quit */
  I2C_Start();
  I2C_Write(0x00);
  I2C_Write(tc74_addr);
  while(!kbhit())
  {
    I2C_Stop();
    I2C_Start();
    I2C_Write(tc74_addr + 1);

    byte_read   = I2C_Read(ACK);
    bcd         = DecimalToBCD(byte_read);
    temperature = BCDToDecimal(bcd);
    I2C_Stop();

    if(byte_read != last_byte_read)
    {
      printf("byte_read     = %x\n", byte_read);
      printf("Temperature   = %d C \n",temperature);
    }
    last_byte_read = byte_read;
    /* Pause between reads */
    Delay(80000);
  }
  I2C_Stop();
  getch();
}

void SC406_Demo()
{
  int i2c_tc74_addr;
  char *config_string;

  config_string = ReadCfgItem("I2C.CFG", "TC74_ADDR");
  if (strcmp(config_string, "") == 0)
  {
    printf("SC406 not found\n");
  }
  else
  {
    i2c_tc74_addr = (Hex2Int(config_string) << 1);

    printf("\nSC406 Demonstration\n");
    printf("===================\n");
    printf("Reading and displaying temperature\n");
    printf("<Press any key to quit>\n\n");
    Read_Temp(i2c_tc74_addr);
    printf("===================\n");
  }
}

void SC407_Demo()
{
  int i2c_pcf_in;
  int i2c_pcf_out;

  char *config_string;

  config_string = ReadCfgItem("I2C.CFG", "PCF_IN");
  if (strcmp(config_string, "") == 0)
  {
    printf("SC407 not found\n");
  }
  else
  {
    i2c_pcf_in = Hex2Int(config_string);

    config_string = ReadCfgItem("I2C.CFG", "PCF_OUT");
    i2c_pcf_out = Hex2Int(config_string);

    printf("\nSC407 Demonstration\n");
    printf("===================\n");
    printf("Flashing alternate LEDs\n");
    printf("<Press any key to continue>\n\n");
    Flash_LEDs(i2c_pcf_out);

    printf("Reading and display button values\n");
    printf("<Press any key to quit>\n\n");
    Read_Buttons(i2c_pcf_in);
    printf("===================\n");
  }
}
