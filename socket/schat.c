#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <poll.h>
#define SA struct sockaddr

// char src_str[100] = "+CIFSR,STAIP:\"122.51.89.94\"\r\n"; 
// int  seg1,seg2,seg3,seg4;

int main(int argc , char *argv[]){
  int PORT=51041;
  char SERVER_IP[17];
  char PORT_BUFFER[10];
  char content[4096];
  content[0] = '\0';   
  int sockfd = socket(AF_INET, SOCK_STREAM, 0); //listener
  struct sockaddr_in address;
  //Create Socket  (Remember to check the return value to see if an error occured) 
  //Read IP Address
  printf ("Enter IP Address: ");
  scanf("%14s", SERVER_IP);

  //Read Port
  printf ("Enter Port: ");
  scanf("%9s", PORT_BUFFER);;
  PORT = atoi(PORT_BUFFER);

  printf("1. Creating Socket...\n");
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(SERVER_IP);
  address.sin_port = htons(PORT);

  int len = sizeof(address);
  struct sockaddr_in clt;


  //Connect to Remote server 
  printf("2. Connecting To Server...\n");
  int result = connect(sockfd, (struct sockaddr *) &address, sizeof address);
  if(result == -1){
      perror("connection failed!!!");
        exit(1);
      }

  printf("Server Connected.\n");


  struct pollfd p[2];
      p[0].fd = sockfd;
      p[0].events = POLLIN | POLLHUP;
      p[1].fd = 0;
      p[1].events = POLLIN;

  printf("Socket Created.\n");

  while(1){
      char buf[1024] = {0};
      poll(p,2,-1);
      if(p[1].revents & POLLIN){
          int ret = read(0,buf,sizeof(buf));
          write(sockfd,buf,ret);
      }

      if(p[0].revents & POLLHUP){
          return -1;
      }
      else if(p[0].revents & POLLIN){
        memset(buf,0,sizeof(buf));
        read(sockfd,buf,sizeof(buf));
        printf("%s\n",buf);
      }
  }

  close(sockfd);
  return 0;
}
