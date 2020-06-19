#include <stdio.h>

int main()
{

    int number;

    printf("\nEnter an integer: \n");

    scanf("%d", &number);

    if (number % 2 == 0)
    {
        printf("%d is an even integer.\n", number);
    }
    else
    {
        printf("%d is an odd integer.\n", number);
    }
}