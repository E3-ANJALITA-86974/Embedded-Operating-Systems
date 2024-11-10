#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
int  signal,pid;
printf("Enter signal number : ");
scanf("%d",&signal);
printf("Enter pid of the process :");
scanf("%d",&pid);

int ret = kill(pid,signal);
if(ret == -1)
{
printf("Signal sent successfully!");
}
else
{
printf("Signal sending unsuccessful!\n");
}
return 0;
}
