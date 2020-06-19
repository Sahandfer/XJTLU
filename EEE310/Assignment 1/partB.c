#include <math.h>
#include <stdio.h>
int main()
{

    float a, b, c;
    float discriminant;
    float x1, x2;

    scanf("%f %f %f", &a, &b, &c);

    discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
    {
        printf("The roots are complex and different");
    }
    else
    {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        if (x1 == x2)
        {
            printf("%.3f\n", x1);
        }
        else
        {
            if (x1 > x2)
            {
                printf("%.3f\n", x1);
                printf("%.3f\n", x2);
            }
            else
            {
                printf("%.3f\n", x2);
                printf("%.3f\n", x1);
            }
        }
    }
}