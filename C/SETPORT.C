/* setport.c
   Simple program to send a byte to a port.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <UTILS.H>

void GetValues(short int *port, short int *value)
{
    printf("Port number > ");
    scanf("%d", port);

    printf("Enter value to output to the port > ");
    scanf("%d", value);
}

main(argc, argv)
int argc;
char *argv[];
{
    short int out_port;
    short int out_value;
    
    if (argc == 3)
    {
        if (strcmp("CYLON", argv[2]) == 0)
        {
            short int x;
            
            printf("There be cylons!\n");
            
            out_port = atoi(argv[1]);

            while (!kbhit())
            {
                for (x = 1; x <= 64; x = x << 1 )
                {
                    outp(out_port, x);
                    Delay(5000);
                }
            
                for (x = 128; x >= 2; x = x >> 1)
                {
                    outp(out_port, x);
                    Delay(5000);
                }
            }
            outp(out_port, 0);
            getch();
        }
        else
        {
            out_port = atoi(argv[1]);
            out_value = atoi(argv[2]);
            
            outp(out_port, out_value);
        }
    }
    else
    {
        GetValues(&out_port, &out_value);

        outp(out_port, out_value);
    }
}
