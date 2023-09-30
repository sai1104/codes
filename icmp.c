#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main() {
  int sockfd;
  char buffer[4096];
  sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
  while(1){
  int f=recv(sockfd,buffer,sizeof(buffer),0);
  if(f<0){
    break;
  }
  struct iphdr *ip_header=(struct iphdr*)buffer;
  printf("IP header is: %d bytes \n",ip_header->check);
  }
  close(sockfd);
}
