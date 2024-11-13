#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd, ret;
    int num2;
    fd = open("/tmp/myfifo", O_RDONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    printf("p2: waiting for message...\n");
    ret = read(fd, num2, sizeof(num2));
    printf("p2: message recvd: %d bytes = %d\n", ret, num2);
    close(fd);
    return 0;
}
