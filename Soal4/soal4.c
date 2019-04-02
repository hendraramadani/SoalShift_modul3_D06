#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

int arr[10000];
pthread_t tid[50];


struct Order{
	int proc;
	int low;
	int high;
};

void* tulis(void* args){
    char command[100];
    struct Order*extract =(struct Order*)args;
    
    //CREATE FOLDER
    sprintf(command,"mkdir ~/Documents/FolderProses%d",extract->proc);
    system(command);

    //CREATE SimpanProses*.txt
    strcpy(command,"");
    sprintf(command,"ps aux --no-heading | head -%d  | tail -%d > ~/Documents/FolderProses%d/SimpanProses%d.txt",extract->high,extract->low,extract->proc,extract->proc);
    //printf("%s",command);
    system(command);

    //CREATE KompresProses*.zip
    strcpy(command,"");
    sprintf(command,"zip -qmj ~/Documents/FolderProses%d/KompresProses%d ~/Documents/FolderProses%d/SimpanProses%d.txt",extract->proc,extract->proc,extract->proc,extract->proc);
    //printf("%s",command);
    system(command);	
}

void* unzip(void* args){
    char command[100];
    struct Order*extract =(struct Order*)args;
    strcpy(command,"");
    sprintf(command,"unzip -qd ~/Documents/FolderProses%d ~/Documents/FolderProses%d/KompresProses%d.zip",extract->proc,extract->proc,extract->proc);
    //printf("%s",command);
    system(command);
}  



int main(){
  int n=2;
  struct Order order;
  order.proc=0;
  order.low=10;
  order.high=10;
  
  for(int i=1; i<=n;i++){
	order.proc=i;
	pthread_create(&tid[i], NULL, &tulis,(void *)&order);
        pthread_join(tid[i],NULL);
	order.high=order.high+10;
  }

  printf("Tunggu 15 Detik Untuk Unzip\n");
  for(int i=1; i<=15;i++){
	printf("%d\n",i);
	sleep(1);
  }

  for(int i=1; i<=n;i++){
	order.proc=i;
	pthread_create(&tid[i], NULL, &unzip,(void *)&order);
        pthread_join(tid[i],NULL);
  }
    
    return 0;
}



