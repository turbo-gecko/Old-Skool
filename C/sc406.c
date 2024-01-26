/*
 * SC406.C - I2C demo program by Kurt Pieper
 * originated from the source program SC407.C from Gary Hammond
 * Thanks Gary
 *
 * This code is derived from the I2C demo Z80 assembler code for the rc2014 
 * and the SC137+SC406 by Stephen J Cousins with some extra button check code.
 *
 * Learning phase HI-TECH C (z80)
 * V1.0.1 from 18/05/2021
 */

#include <conio.h>
#include <sys.h> 

#define SC137

#ifdef SC137
#define MESSAGE "Using I2C (24a karlab and SC137+SC406 S.Cousins) \n"
#define I2C_PORT    0x0C  /* 0x20 is the standard port for the SC137 */
#define I2C_SDA_RD  0x80
#define I2C_QUIES   0x81

#define I2C_DC_LL   0x00
#define I2C_DC_LH   0x01
#define I2C_DC_HL   0x80
#define I2C_DC_HH   0x81
#endif

#define TC74_ADDR (0x4D << 1) 

/* Other boards */
/* TC74 */

/* #define PCF_IN     0x4D*/   /* 0x7F */
/* #define PCF_OUT    0x4E*/   /* 0x7E */

#define ACK         1
#define NACK        0

#define ERR_NONE    0
#define ERR_JAM     1
#define ERR_NOACK   2
#define ERR_TOUT    3

unsigned char I2C_Read(char ack_flag);
void I2C_Start();
void I2C_Stop();
char I2C_Write(unsigned char data);

char BCDToDecimal (char bcdByte);
char DecimalToBCD (char decimalByte);

int main(int c, char**av) {

    printf(MESSAGE);

    TC74_Demo();
    exit(0);
}

int TC74_Demo() {

    /* char ret_code = 0; */
    unsigned char byte_read = 0;
    unsigned char last_byte_read = 0;
    unsigned char bcd;
    unsigned char temperatur;
    int count;

    /* read tc74  */
    I2C_Start();
    I2C_Write(0x00);
    I2C_Write(TC74_ADDR);

    /* I2C_Stop();
     * I2C_Start();
     * I2C_Write(TC74_ADDR+1);
    */

    while(!kbhit())
    {
    /* Read the pushbuttons. Press a key to quit */
       I2C_Stop();
       I2C_Start();
       I2C_Write(TC74_ADDR+1);

       byte_read  = I2C_Read(ACK);
       bcd        = DecimalToBCD(byte_read);
       temperatur = BCDToDecimal(bcd);
       I2C_Stop();

       if(byte_read != last_byte_read)
       {
              printf("byte_read     = %x\n", byte_read);
              printf("Temperatur    = %02D C \n",temperatur);
       }

        last_byte_read = byte_read;

    /* Wait */
     for (count = 20000; count > 0; count--)
     {
     }

    }
    getch();
    return 0;
}

unsigned char I2C_Read(char ack_flag)
{
    unsigned char byte_read = 0;
    char count = 0;
    unsigned char temp_data = 0;

    /* Set SDA high */ 
    outp(I2C_PORT, I2C_DC_HL);

    /* Get 8 bits for data */
    for (count = 7; count >= 0; count--)
    {
        /* Set SCL high */ 
        outp(I2C_PORT, I2C_DC_HH);

        temp_data = inp(I2C_PORT) & I2C_SDA_RD;
        if(temp_data > 0)
        {
            byte_read += (1 << count);
        }

        /* Set SCL low */ 
        outp(I2C_PORT, I2C_DC_HL);
    }

    /* Set SDA low */ 
    outp(I2C_PORT, I2C_DC_LL);
    
    /* check ack flag */
    if (ack_flag == 0)
    {
        /* Set SDA high */ 
        outp(I2C_PORT, I2C_DC_HL);

        /* Set SCL high */ 
        outp(I2C_PORT, I2C_DC_HH);

        /* Set SCL low */ 
        outp(I2C_PORT, I2C_DC_HL);
    }
    else
    {
        /* Set SCL high */ 
        outp(I2C_PORT, I2C_DC_LH);

        /* Set SCL low */ 
        outp(I2C_PORT, I2C_DC_LL);
    }

    return byte_read;    
}

void I2C_Start()
{
    /* Initialise I2C control port */
    outp(I2C_PORT, I2C_QUIES);
    
    /* Set SDA low */ 
    outp(I2C_PORT, I2C_DC_LH);

    /* Set SCL low */ 
    outp(I2C_PORT, I2C_DC_LL);
}

void I2C_Stop()
{
    /* Set SCL high */ 
    outp(I2C_PORT, I2C_DC_LH);

    /* Set SDA high */ 
    outp(I2C_PORT, I2C_DC_HH);
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
            outp(I2C_PORT, I2C_DC_HL);

            /* Set SCL high */ 
            outp(I2C_PORT, I2C_DC_HH);

            /* Set SCL low */ 
            outp(I2C_PORT, I2C_DC_HL);
        }
        else
        {
            /* Set SDA low */ 
            outp(I2C_PORT, I2C_DC_LL);

            /* Set SCL high */ 
            outp(I2C_PORT, I2C_DC_LH);

            /* Set SCL low */ 
            outp(I2C_PORT, I2C_DC_LL);
        }
    }

    /* Check for acknowledgement */
    /* Set SDA high */ 
    outp(I2C_PORT, I2C_DC_HL);

    /* Set SCL high */ 
    outp(I2C_PORT, I2C_DC_HH);

    temp_data = inp(I2C_PORT) & I2C_SDA_RD;

    /* Set SCL low */ 
    outp(I2C_PORT, I2C_DC_HL);

    if (temp_data == 1)
    {
        return ERR_NOACK;    
    }
    else
    {
        return ERR_NONE;
    }
}

char BCDToDecimal (char bcdByte)
{
   return((bcdByte / 16 * 10) + (bcdByte % 16));
}

char DecimalToBCD (char decimalByte)
{
 return (((decimalByte / 10) << 4) | (decimalByte % 10));
}


