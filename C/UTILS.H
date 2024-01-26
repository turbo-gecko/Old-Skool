/*
 * Miscellaneous utility functions
 */

char BCD_To_Decimal (char bcd_byte);

char Decimal_To_BCD (char decimal_byte);

/*
 * For RC2014 platform with a Z80 running at 7.3728MHz, the time delay can
 * be approximately calculated in micro seconds as
 * delay(uS) = (count * 29.2) + 67.2
 * 
 * This means the shortest delay with count = 1 is approx. 116uS
 * With count = 1000 this is approx. 29.2mS
 */
void Delay(unsigned int count);

/*
 * Displays a text file that is no longer than 80 characters per line
 */
void Display_File(char* filename);

/*
 * Converts a hex number in string format to an unsigned integer
 */
unsigned Hex_To_Int(char *hex);

void Pause(void);

/*
 * Reads a key/value pair from a text file in the format of
 * <key>=<value>
 * Function returns the string <value> if found or an empty string
 * if the <key> is not found in the file.
 * Lines beginning with # are ignored as comments.
 */
char * Read_Cfg_Item(char *filename, char *key);
