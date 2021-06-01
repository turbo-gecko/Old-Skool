/*
 * I2C.C - I2C LCD driver by Gary Hammond
 *
 * V1.0.0 01/06/2021
 */

#include <I2C.H>
#include <UTILS.H>

static int lcd_rd;
static int lcd_wr;

void LCD_Init(void)
{
  char *config_string;

  config_string = ReadCfgItem("I2C.CFG", "LCD_RD");
  lcd_rd = Hex2Int(config_string);

  config_string = ReadCfgItem("I2C.CFG", "LCD_WR");
  lcd_wr = Hex2Int(config_string);

  LCD_Cmd(0x00);
  LCD_Cmd(0x03);
  LCD_Cmd(0x03);
  LCD_Cmd(0x03);
  LCD_Cmd(0x02);
  LCD_Cmd(0x02);
  LCD_Cmd(0x08);
  LCD_Cmd(0x00);
  LCD_Cmd(0x0C);
  LCD_Cmd(0x00);
}

void LCD_Busy_Wait()
{
  static unsigned char byte_read;
  static unsigned char busy_flag;

  byte_read = 0;
  busy_flag = 1;

  while(busy_flag > 0)
  {
    I2C_Start();
    I2C_Write(lcd_wr);
    /* Toggle E*/
    I2C_Write(0x0A);
    I2C_Write(0x0C);
    I2C_Stop();

    /* Read the first nibble */
    I2C_Start();
    I2C_Write(lcd_rd);
    byte_read = I2C_Read(ACK);
    I2C_Stop();
    
    busy_flag = byte_read & 0x80;

    I2C_Start();
    I2C_Write(lcd_wr);
    /* Toggle E */
    I2C_Write(0x0A);
    I2C_Write(0x0C);
    I2C_Stop();

    /* Read the second nibble */
    I2C_Start();
    I2C_Write(lcd_rd);
    I2C_Write(lcd_rd);
    byte_read = I2C_Read(NACK);
    I2C_Stop();
  }
}

void LCD_Cmd(int byte)
{
  I2C_Start();
  I2C_Write(lcd_wr);
  /* Write MSN */
  I2C_Write((byte & 0xf0) | 0x0C);
  I2C_Write((byte & 0xf0) | 0x08);
  /* Write LSN */
  I2C_Write((byte << 4) | 0x0C);
  I2C_Write((byte << 4) | 0x08);
  I2C_Stop();

  LCD_Busy_Wait();
}

void LCD_Print(int byte)
{
  I2C_Start();
  I2C_Write(lcd_wr);
  I2C_Write((byte & 0xf0) | 0x0D);
  I2C_Write((byte & 0xf0) | 0x09);
  I2C_Write((byte << 4) | 0x0D);
  I2C_Write((byte << 4) | 0x09);
  I2C_Stop();

  LCD_Busy_Wait();
}

