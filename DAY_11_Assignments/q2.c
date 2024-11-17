#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char cmd[512], *ptr, *args[32];
    int i, ret, err, s;
    int is_background;

    while(1) 
	{
       
        printf("cmd> ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;  

        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;  
        i++;

        is_background = 0;  
        while(ptr != NULL) {
            ptr = strtok(NULL, " ");
            args[i] = ptr;  
            i++;
        }
        
       
        if(i > 1 && strcmp(args[i-2], "&") == 0) {
            is_background = 1;
            args[i-2] = NULL;  
        }

        
        if(strcmp(args[0], "exit") == 0) {
            _exit(0);
        } else if(strcmp(args[0], "cd") == 0) {
            if(args[1] != NULL) {
                chdir(args[1]);
            } else {
                fprintf(stderr, "cd: missing argument\n");
            }
        } else
		{
            
            ret = fork();
            if(ret == 0) {
                err = execvp(args[0], args);
                if(err < 0) {
                    perror("exec() failed");
                    _exit(1);
                }
            } else
			{
                
                if(!is_background) {
                    waitpid(ret, &s, 0);
                }
            }
        }
    }
    return 0;
}

