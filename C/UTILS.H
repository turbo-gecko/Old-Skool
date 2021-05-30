/*
 * Miscellaneous utility functions
 */

char BCDToDecimal (char bcdByte);
char DecimalToBCD (char decimalByte);
void Delay(unsigned int count);
unsigned Hex2Int(char *hex);
char * ReadCfgItem(char *filename, char *key);
