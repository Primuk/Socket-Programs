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
 char msg[100],chh,strn[100],str[100];
 struct sockaddr_in x;
 fd_set readfds;
 int rec,fd,b,i,size,c,s,port;
 size=sizeof(struct sockaddr);
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Error in Socket Creation\n");
  exit(0);
 }
 printf("Enter Port Number: ");
 scanf("%d",&port);
 x.sin_family=AF_INET;
 x.sin_port=htons(port);
 x.sin_addr.s_addr=inet_addr("127.0.0.1");
 c=connect(fd,(const struct sockaddr*)&x,size);
 if(c==-1)
 {
  printf("Connect Error\n");
  close(fd);
  exit(0);  
 }
 FD_ZERO(&readfds);
 FD_SET(STDIN_FILENO,&readfds);
 while(1)
 {
  if(FD_ISSET(STDIN_FILENO,&readfds))
  {
   read(STDIN_FILENO,msg,70);
   s=send(fd,msg,strlen(msg),0);
	  if(s==-1)
	  {
	   printf("Sending Failure\n");
	   close(fd);
	   exit(0);
	 	}
	  printf("\n");
	  for(i=0;i<100;i++)
	  msg[i]=0;
  }
  rec=recv(fd,str,sizeof(str),0);
	 if(rec==-1)
	 {
	  printf("Error in Recieving\n");
	  close(fd);
	  exit(0);
	 }
	 if(rec>0)
	 {
			str[rec]='\0';
		 printf("\n\nMessage: %s\n",str);
		 for(i=0;i<100;i++)
		 str[i]=0;
	 }
 }
 close(fd);
 return 0;
}
