# Gary's C utilities for CP/M

## I2C utilities
I2CDEMO.C is a demonstration program for using the I2C capabilities of the Stephen C Cousins designed SC126, SC137 and SC144. See https://smallcomputercentral.wordpress.com/projects/ for further details on the I2C masters.
Currently supported slaves include:
* SC406 temperature sensor module (TC74)
* SC407 switched and lights module (PCF8574)

I2C.C is the I2C bit bashing code.

SC407.C is the standalone demo program for the SC407 module. This has been incorporated into I2CDEMO.C

UTILS.C contains various utilities that are used by my other programs. It is a general bucket of useful stuff.
Functions include:
* char BCDToDecimal (char bcdByte);
* char DecimalToBCD (char decimalByte);
* void Delay(unsigned int count);
* unsigned Hex2Int(char *hex);
* char * ReadCfgItem(char *filename, char *key);

I2C.CFG is a text file used to contain key=value pairs that can be read using the ReadCfgItem function from UTILS.C. This allows changes to master and slave settings without having to recompile the code. There is a line limit of 76 characters including the end of line characters with a 36 character limit for the key and the value. Any line beginning with a '#' will be ignored as well as any line without an '=' in it. If a key is not found, an empty string is returned for the value.

To build I2C_DEMO.C using HiTech C compiler, type the following on the command line

```
c -v i2c_demo.c i2c.c utils.c
```

To run type
```
i2c_demo
```

## SETPORT
Setport is a command line utility for setting the output of an I/O port

Usage is
```
setport <port> <value>
```
Note: if the word CYLON is used as the value, the output port will cycle through the bits like a Cylon scanner ;)
