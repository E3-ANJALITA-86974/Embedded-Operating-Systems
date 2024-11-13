#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/sem.h>
#include <signal.h>

#define SEM_KEY 0x123

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
    int pid, semid, ret;
    union semun su;
    struct sembuf op[1];

    semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
    if (semid < 0) {
        perror("semget() failed!\n");
        return 1;
    }

    su.val = 0;
    ret = semctl(semid, 0, SETVAL, su);
    if (ret < 0) {
        perror("semctl() failed!\n");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("START!\n");
    pid = fork();

    if (pid == 0) {
        while (1) {
            op[0].sem_num = 0;
            op[0].sem_op = -1;
            op[0].sem_flg = 0;
            semop(semid, op, 1);

            char *str = "INFOTECH\n";
            for (int i = 0; str[i] != '\0'; i++) {
                write(1, &str[i], 1);
                usleep(500000);
            }

            op[0].sem_num = 0;
            op[0].sem_op = 1;
            op[0].sem_flg = 0;
            semop(semid, op, 1);
        }
    } else {
        while (1) {
            char *str = "SUNBEAM\n";
            for (int i = 0; str[i] != '\0'; i++) {
                write(1, &str[i], 1);
                usleep(500000);
            }

            op[0].sem_num = 0;
            op[0].sem_op = 1;
            op[0].sem_flg = 0;
            semop(semid, op, 1);

            op[0].sem_num = 0;
            op[0].sem_op = -1;
            op[0].sem_flg = 0;
            semop(semid, op, 1);
        }

        wait(NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}

