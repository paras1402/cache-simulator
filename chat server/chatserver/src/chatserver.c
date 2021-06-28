
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
#define LENGTH 2048
#define MAX_CHATS 10

clients *root, *now;

static int ind=0;
char* database[1000];
static int client_count=0;
static int client_id=0;
FILE *fp;



void* handler(void * arg){
	int out=0;
	char buffer[1024];	
	char name[32];
	client_count++;
	
	clients * cl = (clients *) arg;
	
	recv(cl->sock,name,32,0);
	strcpy(cl->name,name);
	sprintf(buffer, "%s added", cl->name);
	printf("%s\n", buffer);
	clients* temp=root->next;
	while(temp){
		if(temp->client_id!=client_id){
		
		write(temp->sock,buffer,strlen(buffer));
		
	}
	temp=temp->next;
	}
	bzero(buffer,1024);
	while(1){
		if(out)
			{break;}
		
		int rec=recv(cl->sock , buffer, 1024, 0);		
		if(rec >0){
			if(strlen(buffer)>0){
			fprintf(fp,"%s",buffer);
			
			//strcpy(database[ind],buffer);
			//ind++;
			clients* temp=root->next;
			while(temp)
			{
			if(temp->client_id!=client_id){
			write(temp->sock,buffer,strlen(buffer));	
			}
			temp=temp->next;
			}
				format(buffer, strlen(buffer));
				printf("%s\n", buffer);
			}
			
		}
	
		else{
			printf("error");
			out=1;
		}
		bzero(buffer,1024);
	}
	close(cl->sock);
	
	if(cl==now){
		now=cl->prev;
		now->next=NULL;
	}
	else{
		cl->prev->next=cl->next;
		cl->next->prev=cl->prev;
	}
	free(cl);
	  
	  return NULL;
}


int main(){

fp=fopen("/home/paras/Desktop/database.txt","w");

 struct sockaddr_in s , c;
	printf("server\n");

  int sock;
	int size=sizeof(struct sockaddr_in);
	sock= socket(AF_INET,SOCK_STREAM,0);
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_port=htons(8888);
  pthread_t tid;
int x=bind(sock,(struct sockaddr*)&s , sizeof(s));
	if(x<0){
		printf("bind failed\n");
		return 1;
	}
	listen(sock,15);
	
	root=node(sock);
	now=root;
	printf("CHATSERVER\n");
			
	while(1){
	
		int acc=accept(sock,(struct sockaddr*)&c,(socklen_t*)&size);
		if(acc>0)
		{
		puts("new connection established");
		clients * cl = node(acc);
		cl->add=c;
		cl->client_id=client_id++;	
		
		cl->prev=now;
		now->next=cl;
		now=cl;
	
		pthread_create(&tid,NULL,&handler, (void*)cl);
		}
		if(acc<0){
			return 1;
		}
	}
	fclose(fp);
	return 1;
	
	
}





































