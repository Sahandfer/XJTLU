#include<reg51.h>
sbit r1=P0^3; // keyboard's top row
sbit c1=P0^6; // keyboard's first column (right to left)
sbit c2=P0^5; // keyboard's second column (right to left)

void main()
{
//The segment codes for three possible conditions
// 0xF0 - 00001111 -> Turn LEDs 0-3 on
// 0x0F - 11110000 -> Turn LEDs 4-7 on
// 0x00 - 11110000 -> Turn all LEDs on
// 0xFF - 11111111 -> Turn all LEDs off
char seg_code[]={0xF0, 0x0F, 0x00, 0xFF};
// Start infinite loop
while(1)
{
r1=0;
c1=1;
c2=1;
if (r1==0 && c1== 0 && c2 == 1) // Key 1 is pressed
{
P1 = seg_code[0]; 
}
else if (r1==0 && c1== 1 && c2 == 0) // Key 2 is pressed
{
P1 = seg_code[1]; 
}
else if (r1==0 && c1== 0 && c2 == 0) // Both of the keys are pressed
{
P1 = seg_code[2]; 
}
else { // None of the keys are pressed
P1 = seg_code[3]; 
}
}
}