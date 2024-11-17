#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY  0x1234

typedef struct msg {
    long id;
    int data1;
    int data2;
    int data3;
} msg_t;

int main() {
    int mqid, pid, s, ret;
    msg_t m1, m2;

    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    pid = fork();
    if (pid == 0) {
        printf("child: enter first no: ");
        scanf("%d", &m1.data1);
        printf("child: enter second no: ");
        scanf("%d", &m1.data2);

        m1.id = 101;
        ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
        if (ret < 0)
            perror("child: msgsnd() failed");
        else
            printf("child: message sent: %d %d\n", m1.data1, m1.data2);

        printf("child: waiting for parent's message...\n");
        ret = msgrcv(mqid, &m1, sizeof(msg_t) - sizeof(long), 202, 0);
        if (ret < 0)
            perror("msgrcv() failed");
        else
            printf("child: addition from parent is %d\n", m1.data3);
    } else {
        printf("parent: waiting for child message...\n");
        ret = msgrcv(mqid, &m2, sizeof(msg_t) - sizeof(long), 101, 0);
        if (ret < 0)
            perror("msgrcv() failed");
        else {
            printf("parent: received first no : %d\n", m2.data1);
            printf("parent: received second no : %d\n", m2.data2);

            m2.id = 202;
            m2.data3 = m2.data1 + m2.data2;
            printf("parent: The result of two integers is %d\n", m2.data3);

            ret = msgsnd(mqid, &m2, sizeof(msg_t) - sizeof(long), 0);
            if (ret < 0)
                perror("parent: msgsnd() failed");
            else
                printf("parent: message sent: %d\n", m2.data3);
        }

        waitpid(pid, &s, 0);
    }

    return 0;
}

