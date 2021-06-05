/*
 * LCD.H - I2C LCD driver by Gary Hammond
 *
 * Tested with 2x16 and 4x20 LCD modules using I2C interface in 4 bit mode
 *
 * V1.0.0 05/06/2021 - Initial version
 */

#define LCD_BLINK  0x01 /* Blink at current cursor position */
#define LCD_CURSOR 0x02 /* Turn on the cursor underscore */
#define LCD_ON     0x04 /* Turn on the LCD display backlighting */

/*
 * Reads the read and write addresses from I2C.CFG file
 * Initialises the LCD to 4 bit mode, 2 lines and 5x8 character font
 * This function must be called first before using any other LCD function
 */
void LCD_Init(void);

/*
 * Reads the status of the busy flag from the LCD and will not return
 * until the busy flag has been cleared.
 * This is to allow the LCD to process the previous command/write.
 */
void LCD_Busy_Wait(void);

/*
 * Sends the command to clear the LCD display.
 */
void LCD_Clear(void);

/*
 * Writes a command byte to the LCD.
 */
void LCD_Cmd(int);

/*
 * Sets the cursor to the LCD row number 1 to 4 and the
 * LCD column number 1 to 20
 */
void LCD_Cursor(int, int);

/*
 * Sends the command to set the LCD disply settings for 
 * - display on/off (LCD_ON)
 * - cursor on/off (LCD_CURSOR)
 * - blink on/off (LCD_BLINK)
 * Do a logical or of the above 3 constants for passing into the function
 * i.e., LCD_Display(LCD_ON | LCD_CURSOR | LCD_BLINK); Using a constant
 * indicates that that setting should be 'on'.
 */
void LCD_Display(int);

/*
 * Prints a string of characters to the LCD display at the current cursor
 * position
 */
void LCD_Print(char *);

/*
 * Prints a single character to the LCD display at the current cursor
 * position
 */
void LCD_Print_Char(int);

