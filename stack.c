//
// Created by novas on 16/5/24.
//
#include "stack.h"
void init(Stack* stack)
{
    stack=(Stack*)malloc(sizeof(Stack));
    stack->top=0;
}
int pop(Stack* stack)
{
    int res=stack->array[stack->top];
    stack->top--;
    return res;
}
void push(Stack* stack,int element)
{
    stack->top++;
    stack->array[stack->top]=element;
}

