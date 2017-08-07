#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <netdb.h> 
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <time.h> 
#include <sys/types.h>
#include <pthread.h>
#include <net/if.h>
#include <errno.h>
#include <assert.h>
#define HELLO_WORLD_SERVER_PORT    6666 
#define LENGTH_OF_LISTEN_QUEUE 1
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
bool server_init[5]={false};
bool server_finish=false;
bool client_finish=false;
void *server(void *arg)
{
    struct sockaddr_in server_addr[5];
	int server_socket[5];
	int new_server_socket[5];
    int i=0;
    for(i=0;i<5;i++){
		printf("[Server]%d:socket\n",i);
        bzero(&(server_addr[i]),sizeof(server_addr[i]));
        server_addr[i].sin_family = AF_INET;
        server_addr[i].sin_addr.s_addr = htons(INADDR_ANY);
        server_addr[i].sin_port = htons(HELLO_WORLD_SERVER_PORT+i);

        struct	group_req group = {0};
        struct sockaddr_in *psin;

        psin = (struct sockaddr_in *)&group.gr_group;
        psin->sin_family = AF_INET;
        psin->sin_addr.s_addr = htonl(inet_addr("10.10.2.224"));

        server_socket[i] = socket(PF_INET,SOCK_STREAM,0);
        if( server_socket[i] < 0)
        {
            printf("[Server]Create Socket Failed!");
            exit(1);
        }

        { 
         int opt =1;
           //IPPROTO_IP
           setsockopt(server_socket[i], SOL_IP, MCAST_JOIN_GROUP, &group, sizeof (group));
        }

        if( bind(server_socket[i],(struct sockaddr*)&(server_addr[i]),sizeof(server_addr[i])))
        {
            printf("[Server]Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT+i); 
            exit(1);
        }


        if ( listen(server_socket[i], LENGTH_OF_LISTEN_QUEUE) )
       {
           printf("[Server]Server Listen Failed!"); 
           exit(1);
        }

        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        server_init[i]=true;
        printf ("[Server]accept..... \n"); 
        new_server_socket[5] = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            close(server_socket);
            printf("[Server]Server Accept Failed!\n");
            return NULL;
        }
    }
    sleep(3);
    for(i=0;i<5;i++){
		printf("%d:1st socket close\n");
		close(new_server_socket[i]);
	}
	for(i=0;i<5;i++){
    	printf("%d:2nd socket close\n");
		close(server_socket);
	}
	server_finish=true;
    return NULL;
}
void *client(void *arg){
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htons(INADDR_ANY);
	client_addr.sin_port=htons(0);
	int client_socket=socket(AF_INET,SOCK_STREAM,0);
	if(client_socket<0){
		printf("[Client]Create socket failed!\n");
		exit(1);
	}
	if(bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr))){
		printf("[Client] client bind port failed!\n");
		exit(1);
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	if(inet_aton("127.0.0.1",&server_addr.sin_addr)==0){
		printf("[Client]Server IP Address error\n");
		exit(0);
	}
	server_addr.sin_port=htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length=sizeof(server_addr);
	if(connect(client_socket,(struct sockaddr*)&server_addr,server_addr_length)<0){
		printf("[Client]cannot connect to 127.0.0.1!\n");
		exit(1);
	}
	printf("[Client]Close client socket\n");
	close(client_socket);
		client_finish=true;

	return NULL;

}
int main(int argc,char* argv[])
{	
	pthread_t id_server,id_client;
	pthread_create(&id_server,NULL,server,NULL);
	while(!server_init){
		sleep(1);
	}
	pthread_create(&id_client,NULL,client,NULL);
	while(!server_finish || !client_finish){
		sleep(1);
	}
    printf("exit...\n");
	return 0;
}
