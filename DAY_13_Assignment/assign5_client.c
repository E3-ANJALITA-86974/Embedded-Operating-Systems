#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define SERV_ADDR   "192.168.1.13"
#define SERV_PORT   2809

int main() {
    int ret, cli_fd;
    struct sockaddr_in serv_addr;
    char msg[512];
    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(cli_fd<0)
    {
    	perror("SOCKET() FAILED");
    	_exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret<0)
    {
    	perror("connect() failed");
    	_exit(1);
    }
    do {
        printf("client: ");
        gets(msg);
        ret = write(cli_fd, msg, strlen(msg)+1);
        if(ret<0)
        {
        	perror("write() failed");
        	_exit(1);
        }
        ret = read(cli_fd, msg, sizeof(msg));
        if(ret<0)
        {
        	perror("read() failed");
        	_exit(1);
        }
        printf("server: %s\n", msg);
    }while(strcmp(msg, "bye")!=0);
    close(cli_fd);
    return 0;
}

