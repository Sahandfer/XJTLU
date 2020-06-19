#include <stdio.h>
int power(int base, int a)
{
    if (a != 0)
        return (base * power(base, a - 1));
    else
        return 1;
}
int main()
{
    int base, a, result;
    scanf("%i %i", &base, &a);
    result = power(base, a);
    printf("%i^%i=%i\n", base, a, result);
}