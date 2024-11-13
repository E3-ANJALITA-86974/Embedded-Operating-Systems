#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG_KEY 1234


struct message {
    long msg_type;
    int number1;
    int number2;
    int result;
};

int main() {
    int msgid;
    pid_t pid;
    struct message msg;

   
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    
   pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        
      msg.msg_type = 1; 
       msg.number1 = 5;  
        msg.number2 = 10; 

        
       if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        printf("Child: The sum is %d\n", msg.result);
        exit(0);
    } else {
        

        
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        
        msg.result = msg.number1 + msg.number2;
        msg.msg_type = 2; 

        
        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        
       wait(NULL);

        
        msgctl(msgid, IPC_RMID, NULL);
        printf("Parent: Message queue removed and exiting.\n");
    }

    return 0;
}

