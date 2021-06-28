#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>	
#include<unistd.h>

int main(){
	struct sockaddr_in s;
	char text[1000];
	char reply[1000];
	int sock=socket(AF_INET,SOCK_STREAM,0);
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_family=AF_INET;
	s.sin_port=htons( 8888 );
	connect(sock,(struct sockaddr*)&s,sizeof(s));
	puts("connected to server");
	while(1){
		printf("enter message\n");
		scanf("%s",text);
		send(sock,text,sizeof(text),0);
		recv(sock,reply,1000,0);
		puts(reply);
		memset(reply,0,sizeof(reply));
		memset(text,0,sizeof(reply));
	
	}
	

}
