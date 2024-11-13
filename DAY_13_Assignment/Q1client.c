#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd, ret;
    int num1;
    fd = open("/tmp/myfifo", O_WRONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    printf("p1: enter a message: ");
    scanf("%d", num1);
    ret = write(fd, num1, strlen(num1)+1);
    printf("p1: message sent: %d bytes\n", ret);
    close(fd);
    return 0;
}
