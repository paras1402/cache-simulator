
typedef struct client{
	struct sockaddr_in add;
	int sock;
	int client_id;
	struct client* prev;
	struct client* next;
	char name[100];
} clients;


void format(char* arr, int x) {
  int i;
  for (i=0;i<x; i++){
    if(arr[i]=='\n') {
      arr[i] = '\0';
      break;
    }
  }
}

clients * node(int sock){
	clients *np = (clients *)malloc( sizeof(clients) );
	np->prev=NULL;
	np->next=NULL;
	np->sock=sock;
	return np;
	
}
