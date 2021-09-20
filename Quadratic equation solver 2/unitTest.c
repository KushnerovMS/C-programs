#include <stdio.h>
#include <math.h>
#include <float.h>

const double EPSILON = 1e-100;

void testFunction(double a, double b, double c, int curRCount, double curX1, double curX2, int (*functionToTest)(double a, double b, double c, double *x1, double *x2))
{
    double x1, x2;
    x1 = x2 = 0;
    int rCount = 0;

    rCount = (*functionToTest)(a, b, c, &x1, &x2);

    if(rCount != curRCount || fabs((curX1 - x1) / curX1) > EPSILON || fabs((curX2 - x2) / curX2) > EPSILON)
    {
        printf("a = %e, b = %e, c = %e\n", a, b, c);
        printf("Current Root count = %d, x1 = %e, x2 = %e\n", curRCount, curX1, curX2);
        printf("Given Root count = %d, x1 = %e, x2 = %e\n\n", rCount, x1, x2);
    }
}

void unitTest(int (*functionToTest)(double a, double b, double c, double *x1, double *x2))
{
    testFunction(/*a*/1,/*b*/2,/*c*/1,/*n*/1,/*x1*/-1,/*x2*/0, functionToTest);
    testFunction(/*a*/1*DBL_MIN,/*b*/2*DBL_MIN,/*c*/1*DBL_MIN,/*n*/1,/*x1*/-1,/*x2*/0, functionToTest);
    testFunction(/*a*/0.5*DBL_MAX,/*b*/1*DBL_MAX,/*c*/0.5*DBL_MAX,/*n*/1,/*x1*/-1,/*x2*/0, functionToTest);
    testFunction(/*a*/1*sqrt(DBL_MIN),/*b*/2*sqrt(DBL_MIN),/*c*/1*sqrt(DBL_MIN),/*n*/1,/*x1*/-1,/*x2*/0, functionToTest);
    testFunction(/*a*/1*sqrt(DBL_MAX),/*b*/2*sqrt(DBL_MAX),/*c*/1*sqrt(DBL_MAX),/*n*/1,/*x1*/-1,/*x2*/0, functionToTest);
    testFunction(/*a*/0,/*b*/0,/*c*/0,/*n*/-1,/*x1*/0,/*x2*/0, functionToTest);
    testFunction(/*a*/0,/*b*/0,/*c*/1,/*n*/0,/*x1*/0,/*x2*/0, functionToTest);
    testFunction(/*a*/0,/*b*/2,/*c*/1,/*n*/1,/*x1*/-0.5,/*x2*/0, functionToTest);
    testFunction(/*a*/1,/*b*/0,/*c*/1,/*n*/0,/*x1*/0,/*x2*/0, functionToTest);
    testFunction(/*a*/1,/*b*/0,/*c*/0,/*n*/1,/*x1*/0,/*x2*/0, functionToTest);
    testFunction(/*a*/1,/*b*/3,/*c*/2,/*n*/2,/*x1*/-2,/*x2*/-1, functionToTest);
}
