#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a,b,c,d;

    printf("������� ����������� ����������� ���������:\n�=");
    scanf("%d", &a);

    printf("b=");
    scanf("%d", &b);

    printf("c=");
    scanf("%d", &c);

    if((d = (b*b - 4*a*c))>=0)
        printf("\nx1 = %.4f;\nx2 = %.4f.",(-b + sqrtf(d))/(2.0f*a),(-b - sqrtf(d))/(2.0f*a));
    else printf("��� ������");

    return 0;
}
