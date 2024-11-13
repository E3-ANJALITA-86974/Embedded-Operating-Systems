#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        close(pipe1[0]);
        close(pipe2[1]);

        int num1 = 5, num2 = 10;
        write(pipe1[1], &num1, sizeof(num1));
        write(pipe1[1], &num2, sizeof(num2));
        close(pipe1[1]);

        int result;
        read(pipe2[0], &result, sizeof(result));
        close(pipe2[0]);

        printf("Child: The sum is %d\n", result);
        exit(0);
    } else {
        close(pipe1[1]);
        close(pipe2[0]);

        int num1, num2;
        read(pipe1[0], &num1, sizeof(num1));
        read(pipe1[0], &num2, sizeof(num2));
        close(pipe1[0]);

        int sum = num1 + num2;
        write(pipe2[1], &sum, sizeof(sum));
        close(pipe2[1]);

        wait(NULL);
        printf("Parent: Child process completed. Exiting.\n");
    }

    return 0;
}

