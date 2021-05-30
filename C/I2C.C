/*
 * I2C.C - I2C bus master support by Gary Hammond
 *
 * This code is derived from the I2C demo Z80 assembler code for the SC126 
 * and the SC137 by Stephen J Cousins.
 *
 * V1.0.0 16/05/2021
 */

#include <sys.h> 

#include <I2C.H>
#include <UTILS.H>

static int i2c_port;
static int i2c_sda_rd;
static int i2c_quies;

void I2C_Init(void)
{
  char *config_string;

  printf("Initialising I2C\n");

  config_string = ReadCfgItem("I2C.CFG", "PORT");
  i2c_port = Hex2Int(config_string);

  config_string = ReadCfgItem("I2C.CFG", "SDA_RD");
  i2c_sda_rd = Hex2Int(config_string);

  config_string = ReadCfgItem("I2C.CFG", "QUIES");
  i2c_quies = Hex2Int(config_string);

  config_string = ReadCfgItem("I2C.CFG", "TYPE");

  printf("Using %s on port %x\n", config_string, i2c_port);
}

unsigned char I2C_Read(char ack_flag)
{
  unsigned char byte_read = 0;
  char count = 0;
  unsigned char temp_data = 0;

  /* Set SDA high */ 
  outp(i2c_port, I2C_DC_HL);

  /* Get 8 bits for data */
  for (count = 7; count >= 0; count--)
  {
    /* Set SCL high */
    outp(i2c_port, I2C_DC_HH);

    temp_data = inp(i2c_port) & i2c_sda_rd;
    if(temp_data > 0)
    {
        byte_read += (1 << count);
    }

    /* Set SCL low */
    outp(i2c_port, I2C_DC_HL);
  }

  /* Set SDA low */ 
  outp(i2c_port, I2C_DC_LL);

  /* check ack flag */
  if (ack_flag == 0)
  {
    /* Set SDA high */
    outp(i2c_port, I2C_DC_HL);

    /* Set SCL high */
    outp(i2c_port, I2C_DC_HH);

    /* Set SCL low */
    outp(i2c_port, I2C_DC_HL);
  }
  else
  {
    /* Set SCL high */
    outp(i2c_port, I2C_DC_LH);

    /* Set SCL low */
    outp(i2c_port, I2C_DC_LL);
  }

  return byte_read;
}

void I2C_Start()
{
  /* Initialise I2C control port */
  outp(i2c_port, i2c_quies);

  /* Set SDA low */
  outp(i2c_port, I2C_DC_LH);

  /* Set SCL low */
  outp(i2c_port, I2C_DC_LL);
}

void I2C_Stop()
{
  /* Set SCL high */
  outp(i2c_port, I2C_DC_LH);

  /* Set SDA high */
  outp(i2c_port, I2C_DC_HH);
}

char I2C_Write(unsigned char data)
{
  char count = 0;
  unsigned char temp_data = 0;

  /* Get 8 bits for data */
  for (count = 7; count >= 0; count--)
  {
    /* Is the current bit set to high */
    if ((data & (1 << count)) > 0)
    {
      /* Set SDA high */
      outp(i2c_port, I2C_DC_HL);

      /* Set SCL high */
      outp(i2c_port, I2C_DC_HH);

      /* Set SCL low */
      outp(i2c_port, I2C_DC_HL);
    }
    else
    {
      /* Set SDA low */
      outp(i2c_port, I2C_DC_LL);

      /* Set SCL high */
      outp(i2c_port, I2C_DC_LH);

      /* Set SCL low */
      outp(i2c_port, I2C_DC_LL);
    }
  }

  /* Check for acknowledgement */
  /* Set SDA high */
  outp(i2c_port, I2C_DC_HL);

  /* Set SCL high */
  outp(i2c_port, I2C_DC_HH);

  temp_data = inp(i2c_port) & i2c_sda_rd;

  /* Set SCL low */
  outp(i2c_port, I2C_DC_HL);

  if (temp_data == 1)
  {
    return ERR_NOACK;    
  }
  else
  {
    return ERR_NONE;
  }
}
