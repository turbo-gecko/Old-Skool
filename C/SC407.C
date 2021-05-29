/*
 * SC407.C - I2C demo program by Gary Hammond
 *
 * This code is derived from the I2C demo Z80 assembler code for the SC126 
 * and the SC137 by Stephen J Cousins with some extra button check code.
 *
 * V1.1.0 16/05/2021
 */

#include <conio.h>
#include <I2C.H>
#include <UTILS.H>

/* Other boards */
/* PCF8574 */
#define PCF_IN      0x7F
#define PCF_OUT     0x7E

void Flash_LEDs();
void Read_Buttons();

main()
{
    printf("Demonstration program for the SC407 I2C I/O board\n");
    
    printf("Flashing alternate LEDs\n");
    printf("<Press any key to continue>\n\n");
    Flash_LEDs();
    
    printf("Reading and display button values\n");
    printf("<Press any key to quit>\n\n");
    Read_Buttons();
}

void Flash_LEDs()
{
    /* Demo using the SC407 to flash alternate LED's
       Note: The SC407 LED's are active low so the values
       sent to light the LED's are inverted */
    char ret_code = 0;

    while(!kbhit())
    {
        /* Output alternate bit pattern 1 */
        I2C_Start();
        ret_code = I2C_Write(PCF_OUT);
        ret_code = I2C_Write(0xAA);
        I2C_Stop();

        /* Wait long enought to see it */
        Delay(20000);

        /* Output alternate bit pattern 2 */
        I2C_Start();
        ret_code = I2C_Write(PCF_OUT);
        ret_code = I2C_Write(0x55);
        I2C_Stop();

        /* Wait long enought to see it */
        Delay(20000);
    }
    getch();

    /* Turn off the LED's */
    I2C_Start();
    ret_code = I2C_Write(PCF_OUT);
    ret_code = I2C_Write(0xFF);
    I2C_Stop();
}

void Read_Buttons()
{
    char ret_code = 0;
    int count = 0;
    unsigned char byte_read = 0;
    unsigned char last_byte_read = 0;

    /* Read the pushbuttons. Press a key to quit */
    I2C_Start();
    ret_code = I2C_Write(PCF_IN);
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


