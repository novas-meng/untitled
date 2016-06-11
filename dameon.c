//
// Created by novas on 16/6/7.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdlib.h>
#include <signal.h>

enum State{
    New,Running,Done,Error
};

struct dowork
{
    //job完成情况
    enum State workState;
    //参数
    char buffer[1024];
    struct dowork *next;
};
typedef struct dowork* workList;
workList headList;
struct dowork* getFirst(workList list)
{
    return list->next;
}
struct dowork* outqueue(workList list)
{
    struct dowork *p=list->next;
    if(p==NULL)
    {
        return NULL;
    }
    list->next=p->next;
    return p;
}

void doRun(workList headList)
{
  //  printf("in dorun");
    int pid;
    struct dowork* work;
    Label: work=getFirst(headList);
    printf("work=%d\n",work);
    if(work==NULL)
    {
        printf("empty\n");
    }
    else
    {
        if(work->workState==New)
        {
            work->workState=Running;
            int parentid=getpid();
            printf("执行结束,执行下一个,state=%s\n",work->buffer);
            if(pid=fork())
            {
                // exit(0);
            }
            else if(pid==0)
            {
                system(work->buffer);
                kill(parentid,SIGUSR1);
                exit(1);
                printf("发送信号\n");
            }
        }
        else if(work->workState==Running)
        {

        }
        else if(work->workState==Done)
        {
            printf("出队\n");
            outqueue(headList);
            goto Label;
        }
    }
}
void handle(int signal)
{
    if(signal==SIGUSR1)
    {
        printf("接收到信号\n");
        struct dowork* work=getFirst(headList);
        if(work->workState==Running)
        {
            work->workState=Done;
        }
      //  outqueue(headList);
        doRun(headList);
    }
}
void init(workList *list)
{
    *list=(struct dowork *)malloc(sizeof(struct dowork));
    printf("%d\n",list);
    (*list)->next=NULL;
}

void enqueue(workList list,struct dowork* work)
{
   // printf("===\n");

    struct dowork *p=list;

    //printf("===\n");
    while (p->next!=NULL)
    {
        p=p->next;
    }
  //  printf("===\n");

    p->next=work;
   // printf("===\n");

    work->next=NULL;
   // printf("===\n");

}

int main()
{
    init(&headList);
    signal(SIGUSR1,handle);
    int fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    if(fd==-1)
    {
        printf("create roor");
    }
    memset(&serverAddr,0, sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddr.sin_port=htons(8097);
    if(bind(fd,(struct sockaddr*)&serverAddr, sizeof(serverAddr))==-1)
    {
        printf("bind error\n");
    }
    if(listen(fd,10)==-1)
    {
        printf("listen error\n");
    }
    while (1)
    {
        int clinetfd=accept(fd,(struct sockaddr*)NULL,NULL);
        if(clinetfd==-1)
        {
            printf("connect error");
        }
        char buffer[1024];
        read(clinetfd,buffer, sizeof(buffer));
        printf("recvmsg=%s\n",buffer);
      //  printf("demo\n");
        struct dowork *dowork1;
        dowork1=(struct dowork*)malloc(sizeof(struct dowork));
        dowork1->next=NULL;
        dowork1->workState=New;
        strcpy(dowork1->buffer,buffer);
        printf("dowork1=%d\n",dowork1);
        enqueue(headList,dowork1);
        printf("%d",headList->next);
        doRun(headList);
    }
}
