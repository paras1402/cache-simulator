#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/socket.h>	
#include<unistd.h>
#include<pthread.h>


static int count =0;
#define MAX_CON 5

void *handler(void *arg)
{
	
	count++;

	printf("thread created\n");
	int socket=*(int* )arg;
	char reply[10000];
	recv(socket,reply,10000,0);
	
	printf("%s",reply);
	char *table[3];
	

		
	table[0]=strtok(reply," \t\n");
	table[1]=strtok(NULL, " \t");
	for(int i=1;i<11;i++)
	{	
		table[1][i-1]=table[1][i];
	}
	table[1][10]='\0';
	table[2]=strtok(NULL, " \t\n");
	
	if (count > MAX_CON)
	{
	 char *message = "HTTP/1.0 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<!doctype html><html><body>System is busy right now.</body></html>";
	 write(socket,message,strlen(message));
	
	while(count>MAX_CON){};
	
	 
	 if(strcmp(table[1],"index.html")==0)
        {
        	
        
			char * path="/home/paras/Desktop/";
			char *fullpath = (char*)malloc((strlen(path)+strlen(table[1]))*sizeof(char));
			char content[10000];
			strcpy(fullpath,path);
			strcat(fullpath,table[1]);
			
			
			
			FILE * fp;
			
			fp=fopen(fullpath,"r");
			char c;
			c = fgetc(fp);
			int i=0; 
   			 while (c != EOF) 
			    { 
       	 		content[i++]=c;
        		 
        			c = fgetc(fp); 
    			}
			
			 if(strncmp(table[2],"HTTP/1.0",8)==0)
                		{
                			send(socket,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n", 44, 0);
					write(socket,content,strlen(content));
                		}
			
      			  else if (strncmp(table[2], "HTTP/1.1",8) == 0)
                		{
                				send(socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 44, 0);
						write(socket,content,strlen(content));
						while(1){
							char text[10000];
							int rec=recv(socket,text,10000,0);
							write(socket,text,strlen(text));
							puts(text);
							memset(text,0,10000);
							if(rec==0)
								{
								printf("left");
								fflush(stdout);
								break;
								}
						    }
       				}
        
        
        }
        
        else{				// favicon
        	free(arg);
        	shutdown(socket,SHUT_RDWR);
        	close(socket);
        	socket=-1;
        	count--;
        	pthread_exit(NULL);
        }
	
	
	count--;
	free(arg);
	shutdown(socket,SHUT_RDWR);
         close(socket);
        socket = -1;
        pthread_exit(NULL);
		
	
	}
	
        if(strcmp(table[1],"index.html")==0)
        {
        	
        
			char * path="/home/paras/Desktop/";
			char *fullpath = (char*)malloc((strlen(path)+strlen(table[1]))*sizeof(char));
			char content[10000];
			strcpy(fullpath,path);
			strcat(fullpath,table[1]);
			
			
			
			FILE * fp;
			
			fp=fopen(fullpath,"r");
			char c;
			c = fgetc(fp);
			int i=0; 
   			 while (c != EOF) 
			    { 
       	 		content[i++]=c;
        		 
        			c = fgetc(fp); 
    			}
			
			 if(strncmp(table[2],"HTTP/1.0",8)==0)
                		{
                			send(socket,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n", 44, 0);
					write(socket,content,strlen(content));
                		}
			
      			  else if (strncmp(table[2], "HTTP/1.1",8) == 0)
                		{
                				send(socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 44, 0);
						write(socket,content,strlen(content));
						while(1){
							char text[10000];
							int rec=recv(socket,text,10000,0);
							write(socket,text,strlen(text));
							puts(text);
							memset(text,0,10000);
							if(rec==0)
								{
								printf("left");
								fflush(stdout);
								break;
								}
						    }
       				}
        
        
        }
        
        else{				// favicon
        	free(arg);
        	shutdown(socket,SHUT_RDWR);
        	close(socket);
        	socket=-1;
        	count--;
        	pthread_exit(NULL);
        }
		
	free(arg);
	shutdown(socket,SHUT_RDWR);
	close(socket);
	socket=-1;
	count--;
	pthread_exit(NULL);

	return 0;
}

int main(int argc , char *argv[])
{
	struct sockaddr_in s , c;
	printf("server thread\n");
	int sock;
	int *nsock;
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
	puts("wait for the connection");
	
	
		

	while(1){
	
		int client=accept(sock,(struct sockaddr*)&c,(socklen_t*)&size);
		if(client>0)
		{
		puts("new connection established");
		pthread_t th;
		nsock=malloc(1);
		*nsock=client;
		pthread_create(&th,NULL,handler,(void*)nsock);
		}
		if(client<0){
			return 1;
		}
	}
 return 0;
}

