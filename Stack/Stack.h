#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "MacrosOverloaded.h"

enum StackError
{
    SUCCESS                 = 0,
    MEMORY_ALLOCATION_ERROR = 1,
    OUT_OF_BOUNDS_ERROR     = 2,
    DESTRUCTED_STACK        = 3,
    EXPANSION_DENIED        = 4,
    NO_ITEMS_ERROR          = 5
};

const int DATA_POISON = 666;
char *const POINTER_POISON = (char*)13;

typedef struct
{
    char * Data;
    size_t Capacity;
    size_t Size;
    int ItemSize;

    const char * dname;
    const char * dtype;
    const char * dfunction;
    const char * dfile;
    void (*dprintItem)(FILE * output, void *);
    int dline;
}Stack;

const int STACK_MAX_SIZE = 256;
const int STACK_MIN_SIZE = STACK_MAX_SIZE/64;
const int STACK_MAX_STEP = STACK_MAX_SIZE / 8;
const float STACK_STEP_INCREASE = 1;

StackError StackCtor__ (Stack * stack, const size_t capacity, const int itemSize);

#define StackCtor(stack, ...)                                   \
{                                                               \
    (stack) -> dprintItem = nullptr;                            \
                                                                \
    SELECT_OVERLOADED_MACROS(StackCtor_, stack, __VA_ARGS__);   \
}

#define StackCtor_3(stack, capacity, itemType)                  \
{                                                               \
    const char * name__  = #stack;                              \
    if(*name__ == '&') name__ ++;                               \
    (stack) -> dname = name__;                                  \
                                                                \
    const char * file__ = __FILE__;                             \
    const char * f__ = file__;                                  \
    while (*f__ != '\0')                                        \
    {                                                           \
        while (*f__ != '\0' && *(f__ ++) != '\\')               \
            ;                                                   \
        if(*(f__ - 1) == '\\')                                  \
            file__ = f__;                                       \
    }                                                           \
    (stack) -> dfile = file__;                                  \
                                                                \
    (stack) -> dline = __LINE__;                                \
                                                                \
    (stack) -> dfunction = __FUNCTION__;                        \
                                                                \
    (stack) -> dtype = #itemType;                               \
                                                                \
    StackCtor__(stack, capacity, sizeof(itemType));             \
}

#define StackCtor_4(stack, capacity, itemType, printItem)       \
{                                                               \
    (stack) -> dprintItem = printItem;                          \
    StackCtor_3(stack, capacity, itemType);                     \
}

StackError StackDtor (Stack * stack);
StackError StackPush (Stack * stack, const void* value);
StackError StackPop (Stack * stack, void * value);

void StackDump(const Stack * stack);

#endif
