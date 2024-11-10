#include<stdio.h>
#include<unistd.h>
int main()
{
int i = 1;
printf("%d\n",getpid());
    while(1) {
        printf("running: %d\n", i);
        i++;
sleep(1);
}
return 0;
}
