//
// Created by novas on 16/5/24.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H

#endif //UNTITLED_STACK_H
typedef struct m_stack{
    int top;
    int array[20];
}Stack;
void init(Stack* stack);
int pop(Stack* stack);
void push(Stack* stack,int element);
int length(Stack* stack);
int isFull(Stack* stack);
int isEmpty(Stack* stack);