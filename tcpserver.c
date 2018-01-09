#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<arpa/inet.h>
#include <unistd.h>
int main()
{
 int i,fd,y,l,fd1,size,rec,sen;
 struct sockaddr_in x,z,new;
 char str[100],msg[100];
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Error in Socket Creation\n\n");
  exit(0);
 }
 x.sin_family=AF_INET;
 x.sin_port=htons(7000);
 x.sin_addr.s_addr=inet_addr("127.0.0.35");
 y=bind(fd,(const struct sockaddr*)&x,sizeof(struct sockaddr));
 if(y==-1)
 {
  printf("\nBind Failure\n");
  exit(0);
 }
 l=listen(fd,5);
 if(l==-1)
 {
  printf("\nListen Failure\n");
  exit(0);
 }
 size= sizeof(struct sockaddr);
 fd1=accept(fd,(struct sockaddr*)&z,&size);
while(1)
{
 for(i=0;i<100;i++)
 str[i]=0;
 rec=recv(fd1,str,sizeof(str),0);
 if(rec==-1)
 {
  printf("\nRecieving Failure\n\n");
  exit(0);
 }
 printf("\nMessage:- %s\n\n",str);
 if(strcmp(str,"BYE")==0)
 break;
 for(i=0;i<100;i++)
 msg[i]=0;
 printf("\nEnter your message: ");
 scanf("%s",msg);
 sen= send(fd1,msg,strlen(msg),0);
 if(sen==-1)
 {
  printf("\nSending Failure\n");
  exit(0);
 }
 if(strcmp(msg,"BYE")==0)
 break;
 }
 return 0;
}
