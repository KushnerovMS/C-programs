#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum
{
    SUCCESS = 1,
    MEMORY_ALLOCATION_ERROR,
    OUT_OF_BOUNDS_ERROR,
    DESTRUCTED_STACK,
    EXPANSION_DENIED,
    NO_ITEMS_ERROR
};


const int DATA_POISON = 0xF0;
void *const POINTER_POISON = (void*)13;

const int MAX_SIZE = 256;
const int MIN_SIZE = MAX_SIZE/64;
const int MAX_STEP = MAX_SIZE / 8;
const float STEP_INCREASE = 1;


struct Stack
{
    void *Data;
    size_t Capacity;
    size_t Size;
    int ItemSize;
};


int StackCtor (Stack * stack, const size_t capacity, const int itemSize)
{
    assert(stack);

    if (!(stack -> Data = calloc(capacity, itemSize)))
        return MEMORY_ALLOCATION_ERROR;

    memset(stack -> Data, 0, capacity*itemSize);

    stack -> Size = 0;
    stack -> Capacity = capacity;
    stack -> ItemSize = itemSize;

    return SUCCESS;
}

int StackDtor(Stack * stack)
{
    assert(stack);

    memset(stack -> Data, DATA_POISON, stack -> Capacity);

    free(stack -> Data);

    stack -> Data = POINTER_POISON;
    stack -> Size = -1;
    stack -> Capacity = -1;
    stack -> ItemSize = -1;

    return SUCCESS;
}


int stackRealocate(Stack * stack, size_t capacity);

int StackPush(Stack * stack, const void* value)
{
    assert(stack);

    printf("%d ", stack -> Capacity);

    int error = SUCCESS;
    if(stack -> Size >= stack -> Capacity)
    {
        if((error = stackRealocate(stack, stack -> Size + 1)) != SUCCESS)
            return error;
    }

    printf("%d ", stack -> Capacity);

    memcpy(stack -> Data + (stack -> Size ++) * stack -> ItemSize,
           value,
           stack -> ItemSize);

    return SUCCESS;
}

int StackPop(Stack * stack, void * value)
{
    assert(stack);

    if(stack -> Size <= 0)
        return NO_ITEMS_ERROR;
    else
    {
        printf("%d ", stack -> Capacity);

        memcpy(value,
               stack -> Data + (-- stack -> Size) * stack -> ItemSize,
               stack -> ItemSize);
        stackRealocate(stack, stack -> Size);

        printf("%d ", stack -> Capacity);

        return SUCCESS;
    }

}


int stackRealocate(Stack * stack, size_t capacity)
{
    if(capacity > MAX_SIZE)
        return OUT_OF_BOUNDS_ERROR;


    size_t calcCapacity = capacity;

    if(stack -> Capacity < capacity)
    {
        if(stack -> Capacity * STEP_INCREASE < MAX_STEP)
            calcCapacity = stack -> Capacity *(1 + STEP_INCREASE);
        else
            calcCapacity = stack -> Capacity + MAX_STEP;
    }

    if(stack -> Capacity > capacity)
    {
        if(stack -> Capacity * STEP_INCREASE / (1 + STEP_INCREASE) <= MAX_STEP)
        {
            if(stack -> Capacity / ((1 + STEP_INCREASE)*(1 + STEP_INCREASE)) < capacity)
                return SUCCESS;
            else
                calcCapacity = stack -> Capacity / (1 + STEP_INCREASE);
        }
        else
            if(stack -> Capacity - 2 * MAX_STEP < capacity)
                return SUCCESS;
            else
                calcCapacity = stack -> Capacity - MAX_STEP;
    }


    if(calcCapacity <= MIN_SIZE)
        return SUCCESS;
    if(calcCapacity > MAX_SIZE)
        calcCapacity = MAX_SIZE;


    if(char * buff = (char*)realloc(stack -> Data, calcCapacity * stack -> ItemSize))
    {
        stack -> Data = buff;
        stack -> Capacity = calcCapacity;
        return SUCCESS;
    }
    else
        return MEMORY_ALLOCATION_ERROR;
}