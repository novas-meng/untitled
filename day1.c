//
// Created by novas on 16/5/16.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node * next;
};
typedef struct node * Stack;
void init(Stack stack)
{
    stack=(Stack)malloc(sizeof(struct node));
    stack->data=0;
    stack->next=NULL;
}
void push(Stack stack,int d)
{
    struct node * element=(struct node*)malloc(sizeof(struct node));
    element->data=d;
    element->next=stack->next;
    stack->next=element;
}
int pop(Stack stack)
{
    if(stack->next==NULL)
    {
        return 0;
    }
    struct node* p=stack->next;
    stack->next=p->next;
    free(p);
    return p->data;
}
int main()
{
    char  c='r';
    char   b='r';
    Stack stack;
    init(stack);
    push(stack,9);
    push(stack,90);
    push(stack,930);
    printf("%d\n",pop(stack));
    printf("%d\n",pop(stack));
    int pid=fork();
    if(pid==0)
    {
        printf("child %d\n",getpid());
        system("java -jar /Users/novas/Desktop/fcm.jar abcd defg");
    }
    else
    {
        printf("father %d\n",pid);
    }
}
