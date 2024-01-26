/*#include <conio.h>*/
/*#include <I2C.H>*/
#include <stdio.h>
#include <stdlib.h>

#include <UTILS.H>

main()
{
  char *config_string;
  int config_int;

  printf("Temp program for testing stuff\n");

  config_string = ReadCfgItem("I2C.CFG", "PORT");
  config_int = Hex2Int(config_string);

  printf("ReadCfgItem = %s\n", config_string);
  printf("Integer = %d\n", config_int);
}

