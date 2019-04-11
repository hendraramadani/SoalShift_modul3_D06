#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <termios.h>

int *shop_food_stock;
pthread_t tid;


int mygetch(void)
{
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

void* printku(void *arg){
	while(1) {
        printf("Shop\n");
        printf("Food stock : %d\n", *shop_food_stock);
        printf("Choices\n");
        printf("1. Restock\n");
        printf("2. Exit\n");
        sleep(1);
        system("clear");
    }
}

int main(void) {
    key_t key = 1234;
    char pilihan;
    //*shop_food_stock = 50;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    shop_food_stock = shmat(shmid, NULL, 0);
    system("clear");

    pthread_create(&tid, NULL, &printku, NULL);

    while(1){
        pilihan = mygetch();
        if(pilihan=='1') *shop_food_stock = *shop_food_stock + 1;
        else if(pilihan=='2') {
            printf("Exit\n");
            sleep(1);
            exit(-1);
            system("clear");
        }
    }
    system("clear");
}
