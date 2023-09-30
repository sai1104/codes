#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
//declare variables here
struct sockaddr_in servaddr;
socklen_t len;
char sendline[4096];
char recvline[4096];
if (argc != 2) printf("usage tcpcli <ipaddress>\n");
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(6000);
servaddr.sin_addr.s_addr = inet_addr(argv[1]);
connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
printf("Type something\n");
fgets(sendline, 512, stdin);
int n = strlen(sendline);
write(sockfd, sendline, n);
n = read(sockfd, recvline, 512);
if (n < 0) printf("error reading\n");
recvline[n] = 0;
fputs(recvline, stdout);
exit(0);
}
