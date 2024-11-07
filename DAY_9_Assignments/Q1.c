#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
int i,s,cnt=0,ret;
for(i=1;i<=5;i++)
{
 ret;
ret = fork();
cnt++;
if(ret == 0)
{
printf("Child returned %d\n",ret);
printf("pid of child is %d\n",getpid());
printf("Pid of parent is %d\n",getppid());
sleep(5);
_exit(0);
}
else
{
printf("Child returned %d\n",ret);
sleep(1);
waitpid(ret,&s,0);
printf("Count = %d\n",cnt);
}
}
return 0;
}
