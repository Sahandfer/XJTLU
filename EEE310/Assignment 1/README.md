# Assignment 1
## Part A
Write a C Program to read an integer from the screen and decide if it is odd or even.

[Hint: An expression: a % b produces the remainder when a is divided by b; and zero when there is no remainder]

Note: The programme should start: 

#include <stdio.h>

int main() {

    int number;
    
    printf("\nEnter an integer: ");
    
    scanf("%d", &number);

The output should be like this (if 11 was the number input). 

11 is an odd integer.

or for an even number 

12 is an even integer.

## Part B

The standard form of a quadratic equation is:

 , where a, b and c are real numbers, and a ≠ 0.

The term b^2-4ac is known as the discriminant of a quadratic equation. It tells the nature of the roots.

	1) If the discriminant is greater than 0, the roots are real and different.
	
	2) If the discriminant is equal to 0, the roots are real and equal.
	
	3) If the discriminant is less than 0, the roots are complex and different.

Write a C program to find when the discriminant is greater than or equal to 0 and print the roots to 3 decimal places. Your program should output to the screen the largest root first if they are not equal. If the discriminant is less than zero print to screen “The roots are complex and different”.

## Part C

o do this problem, you should have the knowledge of the following C programming topics:

C switch Statement

C break and continue

Take an arithmetic operator +, -, *, / and two operands (integer numbers) from the user. Then, perform the calculation on the two operands depending upon the operator entered by the user. (For example the user chooses + and 2 and 3, so the output must be 5).

Please start the programme like this:

#include <stdio.h>

int main() {

    int operator;
    
    float first, second;
    
    printf("\nEnter an operator: \n 1 for+,\n 2 for -,\n 3 for *,\n 4 for /\n");
    
    scanf("%i", &operator);     
    
    printf("\nEnter two operands:\n");
    
    scanf("%f %f", &first, &second);

........



The output should be just the result of the arithmetic operation as a float with 4 decimal points. (i.e. if you add 2 and 3 the answer should be shown as : 5.0000). 

Do not put any text before the answer. Just print the answer to the screen as a float to 4 decimal places !

## Part D

Use the function below to  calculate the power of a number (base). 

int power(int base, int a) {

   if (a != 0)

        return (base * power(base, a - 1));
    
    else
    
        return 1;

}

The output should be formatted, for example for 2 raised to the power of 2, as shown here: 

2^2=4

