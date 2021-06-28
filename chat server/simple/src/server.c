#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>	
#include<unistd.h>
#include <time.h>

int  main(){



	struct sockaddr_in s , c;
	printf("server\n");

	int sock;
	int size=sizeof(struct sockaddr_in);
	sock= socket(AF_INET,SOCK_STREAM,0);
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_port=htons(8888);
	int x=bind(sock,(struct sockaddr*)&s , sizeof(s));
	if(x<0){
		printf("bind failed\n");
		return 1;
	}
	listen(sock,15);
	puts("wait for the connection\n");
		int client=accept(sock,(struct sockaddr*)&c,(socklen_t*)&size);
	while(1)
	
	{
		
		
		if(client>0)
		{
		puts("new connection established\n");
		}
		char text[1000000];
		while(1){
		
		int rec=recv(client,text,1000000,0);
		if(strcmp(text,"quit")==0){
		printf("left\n");
		fflush(stdout);
		break;
		
		}
		write(client,text,strlen(text));
		puts(text);
		memset(text,0,1000000);
		if(rec==0)
		{
		printf("left\n");
		fflush(stdout);
		break;
		}
		
		}
	
	}
	return 0;
}
