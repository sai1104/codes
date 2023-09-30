#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define SERV_PORT 6000
int main(int argc, char **argv){
//declare variable here
int listenfd;
socklen_t clilen;
struct sockaddr_in servaddr,cliaddr;
char msg1[512];
listenfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listenfd, 5);
for(;;) {
 clilen = sizeof(cliaddr);
 int connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
 int childpid;
 if ((childpid = fork()) == 0) {
 printf("pid is %d .\n",getpid());
 close(listenfd);
 int n1 = read(connfd, msg1, 512);
 write(connfd, msg1, 50);
 printf("message from client is: ");
 printf(msg1);
 printf("\n");
 close(connfd);
 exit(0);
}
 close(connfd);
}
}
