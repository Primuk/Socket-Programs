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
 int i,z,fd,sen,size,rec,con;
 struct sockaddr_in x,new,y;
 char msg[100],str[100];
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Error in Socket Creation\n\n");
  exit(0);
 }
 size= sizeof(struct sockaddr);
 y.sin_family=AF_INET;
 y.sin_port=htons(7000);
 y.sin_addr.s_addr=inet_addr("127.0.0.35");
 con=connect(fd,(const struct sockaddr*)&y,size);
 if(con==-1)
 {
  printf("\nERROR: Connection unable to establish\n");
  exit(0);
 };
 while(1)
 {
  for(i=0;i<100;i++)
  msg[i]=0;
  printf("\nEnter your message: ");
  scanf("%s",msg);
  sen=send(fd,msg,strlen(msg),0);
  if(sen==-1)
  {
   printf("\nSending Failure\n");
   exit(0);
  }
  if(strcmp(msg,"BYE")==0)
  break;
  for(i=0;i<100;i++)
  str[i]=0;
  rec= recv(fd,str,sizeof(str),0);
  if(rec==-1)
  {
   printf("\nRecieving Failure\n\n");
   exit(0);
  }
  printf("\nMessage:- %s\n\n",str);
  if(strcmp(str,"BYE")==0)
  break;
 }
 return 0;
}
