#include "Stack.h"
#include "Logs.h"

#include <stdio.h>
#include <stdlib.h>

void print(FILE * output, void * item);

int main()
{
    OpenLogs();


    Stack stk = {};

    StackCtor(&stk, 10, int, print);


    for(int i = 0; i < 1000 && StackPush(&stk, &i) == SUCCESS; i++)
        ;
 //   printf("\n\n");

    int a = 0;
    for(int i = 0; StackPop(&stk, &a) == SUCCESS; i++)
        printf("%d\n", a);

    StackDtor(&stk);


    CloseLogs();

    return 0;
}

void print(FILE * output, void * item)
{
    fprintf(output, "%d", *((int*) item));
}

