#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<arpa/inet.h>
#include <unistd.h>
void tostring(char str[], int num)
{
 int i, rem, len = 0, n;
 n = num;
 while (n != 0)
 {
  len++;
  n /= 10;
 }
 for (i = 0; i < len; i++)
 {
  rem = num % 10;
  num = num / 10;
  str[len - (i + 1)] = rem + '0';
 }
 str[len] = '\0';
}
int main()
{
 char str[100],msg[100],ch,*ip,ports[10];
 struct sockaddr_in x,c1;
 int fd,fd1,l,i,size,ret,maxfd,b,r,pid,port,prt,sen;
 size=sizeof(struct sockaddr);
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Socket Creation Error\n");
  exit(0);
 } 
 printf("Enter Port Number: ");
 scanf("%d",&port);
 x.sin_family=AF_INET;
 x.sin_port=htons(port);
 x.sin_addr.s_addr=inet_addr("127.0.0.1");
 b=bind(fd,(const struct sockaddr*)&x,size);
 if(b==-1)
 {
  printf("BIND FAILURE\n");
  exit(0);
 }
 l=listen(fd,5);
 if(l==-1)
 {
  printf("Listen Failure\n");
  close(fd);
  exit(0);
 }
 fd_set readfds,allset;
 FD_ZERO(&readfds);
 FD_ZERO(&allset);
 FD_SET(fd,&allset);
 FD_SET(STDIN_FILENO,&allset);
 maxfd=fd+1;
 struct timeval timeout;
 while(1)
 {
  timeout.tv_sec=10;
  timeout.tv_usec=0;
  readfds=allset;
  ret=select(maxfd,&readfds,NULL,NULL,&timeout);
  if(ret==-1)
  {
   printf("Error in Select API\n");
   exit(0);
  }
  else if(ret==0)
  printf("Timeout\n");
  else
  {
   if(FD_ISSET(fd,&readfds))
   {
    fd1=accept(fd,(struct sockaddr*)&c1,&size);
    if(fd1==-1)
    printf("Error in Accept API\n");
    else
    {
     ip=inet_ntoa(c1.sin_addr);
     prt=ntohs(c1.sin_port);
     printf("\nConnection Established\n");
     printf("IP Address: %s\n",ip); 
     printf("Port Number: %d\n\n",prt);
    }
    FD_SET(fd1,&allset);
    if(maxfd<=fd1)
    maxfd=fd1+1;
   }
   if(FD_ISSET(fd1,&readfds))
   {
    r=recv(fd1,str,sizeof(str),0);
    if(r==-1)
    {
     printf("Recieving Failure\n");
     close(fd);
     exit(0);
    }
    str[r]='\0';
    printf("\n\nMessage: %s\n",str);
    for(i=0;i<100;i++)
    str[i]=0;
   }
   if(FD_ISSET(STDIN_FILENO,&readfds))
   {
    read(STDIN_FILENO,msg,70);
    strcat(msg,"IP Address: ");
    strcat(msg,ip);
    tostring(ports,prt);
    strcat(msg,"\nPort Number: ");
    strcat(msg,ports);
    sen=send(fd1,msg,strlen(msg),0);
    if(sen==-1)
    {
     printf("Error in Sending Message\n");
     close(fd1);
     close(fd);
     exit(0);
    }
    for(i=0;i<sizeof(msg);i++)
    msg[i]=0;
   }
  }
 }
 close(fd1);
 close(fd);
 return 0;
}
