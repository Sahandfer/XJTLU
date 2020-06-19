#include <reg51.h>
//The following variable would allow access to LED 3 in the simulator
sbit portBit = P1 ^ 3; //The sbit data type is used to access the bit addressable memory for Port 1_3.
void main()
{
    //main function starts
    unsigned int i;
    //Initializing Port1 pin3
    portBit = 0; //Make LED3 o/p
    while (1)
    {
        //Infinite loop
        for (i = 0; i < 10; i++)
            ; //delay loop (10 increments)
        portBit = ~portBit;
        //complement Port1.3
        //this makes LED connected on Port1.3 (LED 3) flash
    }
}