#include "Stack.h"

StackError StackCtor__ (Stack * stack, const size_t capacity, const int itemSize)
{
    assert (stack);

    if (!(stack -> Data = (char*) calloc (capacity, itemSize)))
        return MEMORY_ALLOCATION_ERROR;

    memset(stack -> Data, 0, capacity*itemSize);

    stack -> Size = 0;
    stack -> Capacity = capacity;
    stack -> ItemSize = itemSize;

    StackDump (stack);

    return SUCCESS;
}

StackError StackDtor (Stack * stack)
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


StackError stackRealocate (Stack * stack, size_t capacity);

StackError StackPush (Stack * stack, const void* value)
{
    assert(stack);

    StackError error = SUCCESS;
    if(stack -> Size >= stack -> Capacity)
    {
        if((error = stackRealocate(stack, stack -> Size + 1)) != SUCCESS)
            return error;
    }

    memcpy(stack -> Data + (stack -> Size ++) * stack -> ItemSize,
           value,
           stack -> ItemSize);

    StackDump(stack);

    return SUCCESS;
}

StackError StackPop (Stack * stack, void * value)
{
    assert(stack);

    if(stack -> Size <= 0)
        return NO_ITEMS_ERROR;
    else
    {
        //printf("%d ", stack -> Capacity);

        memcpy(value,
               stack -> Data + (-- stack -> Size) * stack -> ItemSize,
               stack -> ItemSize);
        stackRealocate(stack, stack -> Size);

        //printf("%d ", stack -> Capacity);

        return SUCCESS;
    }

}


StackError stackRealocate (Stack * stack, size_t capacity)
{
    if(capacity > STACK_MAX_SIZE)
        return OUT_OF_BOUNDS_ERROR;


    size_t calcCapacity = capacity;

    if(stack -> Capacity < capacity)
    {
        if(stack -> Capacity * STACK_STEP_INCREASE < STACK_MAX_STEP)
            calcCapacity = stack -> Capacity *(1 + STACK_STEP_INCREASE);
        else
            calcCapacity = stack -> Capacity + STACK_MAX_STEP;
    }

    if(stack -> Capacity > capacity)
    {
        if(stack -> Capacity * STACK_STEP_INCREASE / (1 + STACK_STEP_INCREASE) <= STACK_MAX_STEP)
        {
            if(stack -> Capacity / ((1 + STACK_STEP_INCREASE)*(1 + STACK_STEP_INCREASE)) < capacity)
                return SUCCESS;
            else
                calcCapacity = stack -> Capacity / (1 + STACK_STEP_INCREASE);
        }
        else
        {
            if(stack -> Capacity - 2 * STACK_MAX_STEP < capacity)
                return SUCCESS;
            else
                calcCapacity = stack -> Capacity - STACK_MAX_STEP;
        }
    }


    if(calcCapacity <= STACK_MIN_SIZE)
        return SUCCESS;
    if(calcCapacity > STACK_MAX_SIZE)
        calcCapacity = STACK_MAX_SIZE;


    if(char * buff = (char*)realloc(stack -> Data, calcCapacity * stack -> ItemSize))
    {
        stack -> Data = buff;
        stack -> Capacity = calcCapacity;
        memset (stack -> Data + stack -> ItemSize * stack -> Size,
                0,
                (stack -> Capacity - stack -> Size) * stack -> ItemSize);
        return SUCCESS;
    }
    else
        return MEMORY_ALLOCATION_ERROR;
}

void StackDump (const Stack * stack)
{
    extern FILE * Logs;
    fprintf (Logs, "stack<%s>[0x%X]", stack -> dtype, stack);
    if (stack)
    {
        fprintf (Logs, "\"%s\" at %s() at %s (%d)\n", stack -> dname, stack -> dfunction, stack -> dfile, stack -> dline);
        fprintf (Logs, "{\n");
        fprintf (Logs, "\tsize = %d\n", stack -> Size);
        fprintf (Logs, "\tcapacity = %d\n", stack -> Capacity);
        fprintf (Logs, "\tdata[0x%X]\n", stack -> Data);
        if (stack -> Data != nullptr)
            for (int i = 0; i < stack -> Capacity; i++)
            {
                fprintf (Logs, "\t\t[%d] = ", i);
                (*stack -> dprintItem) (Logs, (void*) (stack -> Data + i * stack -> ItemSize));
                fprintf (Logs, "\n");
            }
        fprintf (Logs, "}\n\n");
    }
}
