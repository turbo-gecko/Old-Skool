/*
 * I2C.H - I2C bus master support by Gary Hammond
 *
 * This code is derived from the I2C demo Z80 assembler code for the SC126 
 * and the SC137 by Stephen J Cousins.
 *
 * V1.0.1 18/05/2021 - Added SC144 support
 * V1.0.0 16/05/2021 - Initial version
 */

#define I2C_DC_LL   0x00
#define I2C_DC_LH   0x01
#define I2C_DC_HL   0x80
#define I2C_DC_HH   0x81

#define ACK         1
#define NACK        0

#define ERR_NONE    0
#define ERR_JAM     1
#define ERR_NOACK   2
#define ERR_TOUT    3

void I2C_Init(void);
unsigned char I2C_Read(char ack_flag);
void I2C_Start();
void I2C_Stop();
char I2C_Write(unsigned char data);

