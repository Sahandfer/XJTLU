#include <stdio.h>
int main()
{
    int operator;
    float first, second;
    printf("\nEnter an operator: \n 1 for+,\n 2 for -,\n 3 for *,\n 4 for /\n");
    scanf("%i", &operator);
    printf("\nEnter two operands:\n");
    scanf("%f %f", &first, &second);
    switch (operator)
    {
    case 1:
        printf("%.4f", first + second);
        break;
    case 2:
        printf("%.4f", first - second);
        break;
    case 3:
        printf("%.4f", first * second);
        break;
    case 4:
        printf("%.4f", first / second);
        break;
    }
}