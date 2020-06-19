#include <reg51.h>
void DELAY_ms(unsigned int ms_Count)
{
	unsigned int i, j;
	for (i = 0; i < ms_Count; i++) // Loop based on required MS
	{
		for (j = 0; j < 100; j++)
			; // One milisecond delay
	}
}

sbit Q0 = P3 ^ 3; // Bit 0 of output decoder
sbit Q1 = P3 ^ 4; // Bit 1 of output decoder

int main()
{
	// Segment code for each digit's required LEDs
	char seg_code[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	char cnt = 0;		// The count variable
	char increment = 1; // 1 for counting upwards, -1 for downwards
	// Set decoder output to 10 (decimal 2) -> emulator uses Display 2
	Q0 = 0;
	Q1 = 1;
	// Start infinite loop
	while (1)
	{
		for (cnt = 0; cnt <= 9; cnt = cnt + increment) // loop to display 0-9
		{
			P1 = seg_code[cnt]; // Send the segment_code of number to be displayed */
			DELAY_ms(1);		// 1 milisecond delay
			if (cnt == 9)
			{					// if the upper limit is reached (=9)
				increment = -1; // Start counting downwards
			}
			else if (cnt == 0)
			{				   // if the lower limit is reached (=0)
				increment = 1; // Start counting upwards
			}
		}
	}
}