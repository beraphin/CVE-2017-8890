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
#include <linux/if_ether.h>
#include <linux/filter.h>
#include <assert.h>

#define HELLO_WORLD_SERVER_PORT    6666 
#define LENGTH_OF_LISTEN_QUEUE 1
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
bool server_init=false;
bool server_bpf_init=false;
bool server_finish=false;
bool client_finish=false;
bool server_bpf_finish=false;
bool client_bpf_finish=false;
bool server_bpf_setsock_start=false;
bool server_bpf_setsock_finish=false;
void *server_bpf(void *arg)
{
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(5555);
   
    struct sock_filter code[] = {
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0,  8, 0x000086dd },
	{ 0x30,  0,  0, 0x00000014 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0, 17, 0x00000011 },
	{ 0x28,  0,  0, 0x00000036 },
	{ 0x15, 14,  0, 0x00000016 },
	{ 0x28,  0,  0, 0x00000038 },
	{ 0x15, 12, 13, 0x00000016 },
	{ 0x15,  0, 12, 0x00000800 },
	{ 0x30,  0,  0, 0x00000017 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0,  8, 0x00000011 },
	{ 0x28,  0,  0, 0x00000014 },
	{ 0x45,  6,  0, 0x00001fff },
	{ 0xb1,  0,  0, 0x0000000e },
	{ 0x48,  0,  0, 0x0000000e },
	{ 0x15,  2,  0, 0x00000016 },
	{ 0x48,  0,  0, 0x00000010 },
	{ 0x15,  0,  1, 0x00000016 },
	{ 0x06,  0,  0, 0x0000ffff },
	{ 0x06,  0,  0, 0x00000000 },
    };
    struct sock_fprog bpf = {
	.len =24,
	.filter = code,
    };

    
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if( server_socket < 0)
    {
        perror("[Server_bpf] Create Socket Failed!");
        exit(1);
    }

    int ret=setsockopt(server_socket, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
    if(ret<0){
        perror("[Server_bpf] setsock failed!");
    }
	server_bpf_setsock_finish=true;
	/*
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("[Server_bpf]Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }

        
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
   {
       printf("[Server_bpf]Server Listen Failed!"); 
       exit(1);
    }
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
 
    server_prog_init=true;
    printf ("[Server_bpf]accept..... \n"); 
    int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
    if ( new_server_socket < 0)
    {
        close(server_socket);
        printf("[Server_bpf]Server Accept Failed!\n");
        return NULL;
    }
        
        
    printf ("[Server_bpf]close new_server_socket \n");
    close(new_server_socket);*/
    printf ("[Server_bpf]close socket fd \n");
    close(server_socket);
    server_bpf_finish=true;
    return NULL;
}
void *client_bpf(void *arg){
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htons(INADDR_ANY);
	client_addr.sin_port=htons(0);
	int client_socket=socket(AF_INET,SOCK_STREAM,0);
	if(client_socket<0){
		printf("[Client_bpf]Create socket failed!\n");
		exit(1);
	}
	if(bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr))){
		printf("[Client_bpf] client bind port failed!\n");
		exit(1);
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	if(inet_aton("127.0.0.1",&server_addr.sin_addr)==0){
		printf("[Client_bpf]Server IP Address error\n");
		exit(0);
	}
	server_addr.sin_port=htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length=sizeof(server_addr);
	if(connect(client_socket,(struct sockaddr*)&server_addr,server_addr_length)<0){
		printf("[Client_bpf]cannot connect to 127.0.0.1!\n");
		exit(1);
	}
	printf("[Client_bpf]Close client socket\n");
	close(client_socket);
	client_bpf_finish=true;

	return NULL;

}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void *server(void *arg)
{
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

    struct group_req group = {0};
    struct sockaddr_in *psin;

	psin = (struct sockaddr_in *)&group.gr_group;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = htonl(inet_addr("10.10.2.224"));

    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("[Server]Create Socket Failed!");
        exit(1);
    }

    { 
	   int opt =1;
       //IPPROTO_IP
	printf("[Server] calling setsockopt...\n");
       setsockopt(server_socket, SOL_IP, MCAST_JOIN_GROUP, &group, sizeof (group));
    }

    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("[Server]Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }

        
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
   {
       printf("[Server]Server Listen Failed!"); 
       exit(1);
    }
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
 
 	server_init=true;
    printf ("[Server]accept..... \n"); 
    int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
    if ( new_server_socket < 0)
    {
        close(server_socket);
        printf("[Server]Server Accept Failed!\n");
        return NULL;
    }
        
        
    printf ("[Server]close new_server_socket \n");
    close(new_server_socket);
    //there must be a period between 2 close()???? 
    sleep(3);
	server_bpf_setsock_start=true;
	while(!server_bpf_setsock_finish)
		sleep(1);
	
    //
    printf ("[Server]close socket fd \n");
    close(server_socket);
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
	pthread_t id_server_bpf,id_client_bpf;
	pthread_create(&id_server,NULL,server,NULL);
	while(!server_init){
		sleep(1);
	}
	pthread_create(&id_client,NULL,client,NULL);
	while(!server_bpf_setsock_start)
		sleep(1);
	pthread_create(&id_server_bpf,NULL,server_bpf,NULL);
/*	while(!server_bpf_init)
		sleep(1);
	pthread_create(&id_client_bpf,NULL,client_bpf,NULL);*/
	while(!server_finish || !client_finish||!server_bpf_finish){
		sleep(1);
	}
    printf("exit...\n");
	return 0;
}
