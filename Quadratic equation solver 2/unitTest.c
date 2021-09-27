#include <stdio.h>
#include <math.h>
#include <float.h>

const double EPSILON = 1e-50;

void testFunction(double a, double b, double c, int curRCount, double curX1, double curX2, int (*functionToTest)(double a, double b, double c, double *x1, double *x2))
{
    double x1, x2;
    x1 = x2 = 0;
    int rCount = 0;

    rCount = (*functionToTest)(a, b, c, &x1, &x2);

    if(rCount != curRCount ||
    (fabs((curX1 - x1) / curX1) > EPSILON && fabs((curX1 - x2) / curX1) > EPSILON) ||
    (fabs((curX2 - x2) / curX2) > EPSILON && fabs((curX2 - x1) / curX2) > EPSILON) )
    {
        printf("a = %e, b = %e, c = %e\n", a, b, c);
        printf("Current Root count = %d, x1 = %e, x2 = %e\n", curRCount, curX1, curX2);
        printf("Given Root count = %d, x1 = %e, x2 = %e\n\n", rCount, x1, x2);
    }
}

void unitTest(int (*functionToTest)(double a, double b, double c, double *x1, double *x2))
{
    //           a      b       c       n      x1      x2
    testFunction(1,     2,      1,      1,     -1,      0, functionToTest);
    testFunction(0,     0,      0,     -1,      0,      0, functionToTest);
    testFunction(0,     0,      1,      0,      0,      0, functionToTest);
    testFunction(0,     2,      1,      1,   -0.5,      0, functionToTest);
    testFunction(1,     0,      1,      0,      0,      0, functionToTest);
    testFunction(1,     0,      0,      1,      0,      0, functionToTest);
    testFunction(1,     3,      2,      2,     -2,     -1, functionToTest);
    testFunction(1*DBL_MIN,2*DBL_MIN,1*DBL_MIN,1,-1,0, functionToTest);
    testFunction(0.5*DBL_MAX,1*DBL_MAX,0.5*DBL_MAX,1,-1,0, functionToTest);
    testFunction(1*sqrt(DBL_MIN),2*sqrt(DBL_MIN),1*sqrt(DBL_MIN),1,-1,0, functionToTest);
    testFunction(1*sqrt(DBL_MAX),2*sqrt(DBL_MAX),1*sqrt(DBL_MAX),1,-1,0, functionToTest);
}
