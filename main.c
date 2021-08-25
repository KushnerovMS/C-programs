#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a,b,c,d;

    printf("Введите коофициенты квадратного уравнения:\nа=");
    scanf("%d", &a);

    printf("b=");
    scanf("%d", &b);

    printf("c=");
    scanf("%d", &c);

    if((d = (b*b - 4*a*c)) > 0)
        printf("\nx1 = %.4f;\nx2 = %.4f.\n",(-b + sqrt(d))/(2.0*a),(-b - sqrt(d))/(2.0*a));
    else if(d == 0)
        printf("\nx = %.4f;\n",-(double)b/(2.0d*a));
    else printf("Нет корней\n");

    return 0;
}
