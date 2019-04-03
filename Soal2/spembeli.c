#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#define PORT 8008

int *value;
pthread_t tid;

void* tulis(void* sock){
        int new_socket = *(int*)sock;
	char buffer[1024] = {0};
	int valread;
        char msg[30];
	while((valread = read( new_socket , buffer, 1024))>0){
	    	if(strcmp(buffer,"beli")==0){
			if(*value<=0) {
		    		strcpy(msg,"transaksi gagal");
		    		send(new_socket , msg , strlen(msg) , 0 );
				
			} else
			{	
		    		*value -=1;
		    		strcpy(msg,"transaksi berhasil");
		    		send(new_socket , msg , strlen(msg) , 0 );
				
			}
	    	}
	   memset(msg,0,30);
	   memset(buffer,0,1024);

   	}
}


int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char msg[30];
    
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) {
	if(new_socket<0){
		return 0;
	}else{
		pthread_create(&tid, NULL, &tulis, (void*)&new_socket);

	}
    }
    return 0;
}
