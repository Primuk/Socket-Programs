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
 int t,fd,y,l,fd1,size,rec,sen;
 struct sockaddr_in x,z,new;
 char str[100],msg[100];
 FILE *fil;
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Error in Socket Creation\n\n");
  exit(0);
 }
 x.sin_family=AF_INET;
 x.sin_port=htons(7000);
 x.sin_addr.s_addr=inet_addr("127.0.0.19");
 size= sizeof(struct sockaddr);
 y=bind(fd,(const struct sockaddr*)&x,size);
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
 fd1=accept(fd,(struct sockaddr*)&z,&size);
 
 fil=fopen("abc.txt","r");
 while(!feof(fil))
 {
  fread(msg,1,10,fil);
  sen= send(fd1,msg,strlen(msg),0);
  if(sen==-1)
  {
   printf("\nSending Failure\n");
   exit(0);
  }
 }
 for(i=0;i<100;i++)
 msg[i]=0;
 strcpy(msg,"FILEEND");
 sen= send(fd1,msg,strlen(msg),0);
 if(sen==-1)
 {
  printf("\nSending Failure\n");
  exit(0);
 }
 t=fclose(fil);
 if(t!=0)
 printf("File closing Error\n\n");
 close(fd);
 return 0;
}
