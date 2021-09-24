#include <stdio.h>
#include <stdlib.h>
#include "stack.cpp"


int main()
{
    Stack stack = {};

    StackCtor(&stack, 10, sizeof(int));


    for(int i = 0; i < 1000 && StackPush(&stack, &i)== SUCCESS; i++)
        putchar('\n');
    printf("\n\n");

    int a = 0;
    for(int i = 0; StackPop(&stack, &a) == SUCCESS; i++)
        printf("%d\n", a);

    StackDtor(&stack);

    return 0;
}
