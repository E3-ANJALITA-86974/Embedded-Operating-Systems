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
    int ret, serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    char msg[512];
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_fd<0)
    {
    	perror("socket() failed");
    	_exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret<0)
    {
    	perror("bind() failed");
    	_exit(1);
    }
    ret = listen(serv_fd, 5);
    if(ret<0)
    {
    	perror("listen() failed");
    	_exit(1);
    }
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    if(cli_fd<0)
    {
    	perror("accept() failed");
    	_exit(1);
    }
    do {
        //8. read data from client
        ret = read(cli_fd, msg, sizeof(msg));
        if(ret<0)
        {
        	perror("read() failed");
        	_exit(1);
        }
        printf("client: %s\n", msg);
        //9. send data to client
        printf("server: ");
        gets(msg);
        ret = write(cli_fd, msg, strlen(msg)+1);
        if(ret<0)
        {
        	perror("write() failed");
        	_exit(1);
        }
    }while(strcmp(msg, "bye")!=0);
    //12. close client socket
    close(cli_fd);
    //13. shutdown server socket
    shutdown(serv_fd, SHUT_RDWR);
    return 0;
}

