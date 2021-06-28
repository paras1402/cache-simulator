#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../lib/chatserver_header.h"
char name[100];
int flag=0;
int sock=0;



void smsghandler(){
	char mess[1000]={};
	char buff[1000]={};
	while(1){
		fflush(stdout);
		fgets(mess,1000,stdin);
               format(mess, 1000);
		if(strncmp(mess,"quit",4)==0){
			break;
		}
		else{
			sprintf(buff,"%s -> %s",name,mess);
			send(sock,buff, strlen(buff),0);
		
		}
		bzero(mess,1000);
		bzero(buff,1000);
	
	}
	flag=1;
}



void rmsghandler() {
     char message[1000] = {};
  while (1) {
   int receive = recv(sock, message, 1000, 0);
    if (receive > 0) {
      printf("%s\n", message);
    
       fflush(stdout);
    } else if (receive == 0) {
		break;
    } 
	memset(message, 0, sizeof(message));
  }
}


int main(){

	struct sockaddr_in server_addr;
	sock=socket(AF_INET, SOCK_STREAM, 0);
	 server_addr.sin_family = AF_INET;
 	 server_addr.sin_addr.s_addr = INADDR_ANY;
  	server_addr.sin_port = htons( 8888 );
	int con = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(con==-1)
	{
          printf("ERROR");
           return 1;
	}
	printf("chat client\n");
	printf("enter name\n");
	fgets(name,100,stdin);

	format(name,100);
	printf("*********Welcome %s***********\n",name);
	send(sock,name ,100,0);
	pthread_t smt;
	
	 if(pthread_create(&smt, NULL, (void *) smsghandler, NULL) != 0){
		printf("error\n");
   	 return 1;
	}
	
	pthread_t rmt;
  if(pthread_create(&rmt, NULL, (void *) rmsghandler, NULL) != 0){
		printf("error\n");
		return 1;
	}
	
	for(;;){
		if(flag==1)
		{
			printf("diconnected");
			break;
		}
	}
	close(sock);
	return 1;
	

	
}
