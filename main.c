#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

#define MAXORDER 2

void getCoefficients(float k[], int l);
int getOrder(float k[], int l);
int getAnswer(float k[], float x[], int n);
void printAnswer(float x[], int l);

int main()
{
    float k[MAXORDER + 1], x[MAXORDER];
    int order, rootCount;
    order = rootCount = 0;

    printf("Give me coefficients of your equation:\n\n");

    getCoefficients(k, MAXORDER + 1);

    order = getOrder(k, MAXORDER + 1);

    rootCount = getAnswer(k, x, order);

    printAnswer(x, rootCount);

    return 0;
}

void getCoefficients(float k[], int l)
{
    for(int i = 0; i < l; i++)
    {
        printf("%c= ",'a' + i);
        scanf("%f", &k[l-i-1]);
    }
}

int getOrder(float k[], int l)
{
    int n = 0;

    for(int i = 0; i < l; i++)
        if(k[i] != 0)
            n = i;

    return n;
}

int getAnswer(float k[], float x[], int n)
{
    switch (n)
    {
    case 0 :
        if (k[0] == 0)
            return -1;
        else
            return 0;
    case 1 :
        x[0] = -k[1]/k[0];
        return 1;
    case 2 :
        float d = k[1]*k[1] - 4*k[0]*k[2];
        if (d > 0)
        {
            x[0] = (-k[1] - sqrtf(d))/(2*k[2]);
            x[1] = (-k[1] + sqrtf(d))/(2*k[2]);
            return 2;
        }
        else if (d == 0)
        {
            x[0] = -k[1]/(2*k[2]);
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

void printAnswer(float x[], int l)
{
    switch (l)
    {
    case -1 :
        printf("The equation has infinity roots.");
        break;
    case 0 :
        printf("The equation has no roots.");
        break;
    default :
        for(int i = 0; i < l; i++)
            printf("\nx%i = %.4f;",i + 1, x[i]);
        printf("\b.");
        break;
    }
    printf("\n");
}
