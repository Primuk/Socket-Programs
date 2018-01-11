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
 int z,fd,sen,size,rec,t,con;
 struct sockaddr_in x,new,y;
 char msg[100],str[100];
 FILE *fil;
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd==-1)
 {
  printf("Error in Socket Creation\n\n");
  exit(0);
 }
 size= sizeof(struct sockaddr);
 y.sin_family=AF_INET;
 y.sin_port=htons(7000);
 y.sin_addr.s_addr=inet_addr("127.0.0.19");
 con=connect(fd,(const struct sockaddr*)&y,size);
 if(con==-1)
 {
  printf("\nERROR: Connection unable to establish\n");
  exit(0);
 };
 fil=fopen("xyz.txt","w");
 while(1)
 {
  rec= recv(fd,str,sizeof(str),0);
  if(rec==-1)
  {
   printf("\nRecieving Failure\n\n");
   exit(0);
  }
  printf("%s",str);
  if(strcmp(str,"FILEEND")==0)
  break; 
  fwrite(str,1,11,fil);
 }
 printf("\n\n");
 t=fclose(fil);
 if(t!=0)
 printf("\nFile Closing Error\n\n");
 close(fd);
 return 0;
}
