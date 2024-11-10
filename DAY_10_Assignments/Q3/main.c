#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
int main() {
    int ret, cnt = 0,s;
    while(1) {
        ret = fork();
        if(ret == -1) { 
            printf("fork() failed.\n");
            _exit(0);
        }
        else if(ret == 0) {
            
            sleep(0.1);
            _exit(0);
        }
        else {
            
            cnt++;
            printf("child count: %d\n", cnt);
        }

		wait(&s);
    }
    
    return 0;
}
