#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<termios.h>
#include<stdbool.h>
#include<sys/ipc.h>
#include<sys/shm.h>

pthread_t tid[10];

char monster[100];
int hunger_status = 205;
int hygiene_status = 110;
int health_status = 295;
int my_food_stock = 100;
int *shop_food_stock;
int cooldown = 0;
int enemy_health_status;

bool standby = true;
int i, x;
char pilihan;

void stand_by_mode();
void battle_mode();
void shop_mode();

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

void stand_by_mode() {
	while(1) {
		if(hunger_status<=0) {
			printf("%s died starving!!!\n", monster);
			sleep(1);
			exit(-1);
		}

		if(hygiene_status<=0) {
			printf("%s died from illness!!!\n", monster);
			sleep(1);
			exit(-1);
		}

		printf("Standby Mode\n");
		printf("Health    : %d\n", health_status);
		printf("Hunger    : %d\n", hunger_status);
		printf("Hygiene   : %d\n", hygiene_status);
		printf("Food left : %d\n", my_food_stock);
		if(cooldown == 0 || i-cooldown > 20) printf("Bath is ready\n");
		else printf("Bath will be ready in %ds\n", cooldown+20-i);
		 
		printf("Choices\n");
		printf("1. Eat\n");
		printf("2. Bath\n");
		printf("3. Battle\n");
		printf("4. Shop\n");
		printf("5. Exit\n");
		pilihan = mygetch();
		if(pilihan=='1') {
			if(my_food_stock>0) {
				if(hunger_status >= 200) printf("Full\n");
				else if(my_food_stock-15<0) {
					hunger_status += my_food_stock;
					my_food_stock = 0;
				}
				else {
					my_food_stock -= 15;
					hunger_status += 15;
				}
				
				if(hunger_status>200) {
					my_food_stock += (hunger_status-200);
					hunger_status = 200;
				}
			}
			else {
				printf("Insufficient food\n");
			}
		}
		else if(pilihan=='2') {
			if(cooldown == 0 || i-cooldown > 20) {
				cooldown = i;
				printf("Bath is ready\n");
				hygiene_status += 30;
			}
			else printf("Bath will be ready in %ds\n", cooldown+20-i);
		}
		else if(pilihan=='3') {
			enemy_health_status = 100;
			system("clear");
			standby = false;
			battle_mode();
		}
		else if(pilihan=='4') {
			system("clear");
			standby = false;
			shop_mode();
		}	
		else if(pilihan=='5') {
			printf("Bye Bye\n");
			sleep(1);
			system("clear");
			exit(-1);
		}
		system("clear");
	}
}

void battle_mode() {
	while(1) {
		printf("Battle Mode\n");
		printf("Monster's Health : %d\n", health_status);
		printf("Enemy's Health   : %d\n", enemy_health_status);
		printf("Choices\n");
		printf("1. Attack\n");
		printf("2. Run\n");
		pilihan = mygetch();
		if(pilihan=='1') {
			enemy_health_status -= 20;
			health_status -= 20;
			if(health_status<=0) {
				printf("%s was defeated by the enemy and died!!!\n", monster);
				sleep(1);
				system("clear");
				exit(-1);
			}

			if(enemy_health_status <= 0) {
				printf("%s win!!!\n", monster);
				sleep(1);
				system("clear");
				standby = true;
				stand_by_mode();
			}
		}		
		else if(pilihan=='2') {
			printf("Run from battle mode\n");
			sleep(1);
			system("clear");
			stand_by_mode();
		}
		system("clear");
	}
}

void shop_mode() {
	while(1) {
		printf("Shop Mode\n");
		printf("Shop food stock : %d\n", *shop_food_stock);
		printf("Your food stock : %d\n", my_food_stock);
		printf("Choices\n");
		printf("1. Buy\n");
		printf("2. Back\n");
		pilihan = mygetch();
		if(pilihan=='1') {
			if(*shop_food_stock > 0) {
				printf("Transaksi berhasil\n");
				*shop_food_stock = *shop_food_stock - 1;
				my_food_stock++;
			}
			else printf("Transaksi gagal\n");
		}		
		else if(pilihan=='2') {
			printf("Back from shop mode\n");
			sleep(1);
			system("clear");
			standby = true;
			stand_by_mode();
		}
		system("clear");
	}
}

void* hitungwaktu(void *arg)
{
	i = 1;
	while(1) {
		i++;
		sleep(1);
	}
}

void* hunger(void *arg)
{
	while(1) {
		while(!standby) {

		}
		hunger_status -= 5;
		sleep(10);
	}
}

void* hygiene(void *arg)
{
	while(1) {
		while(!standby) {

		}
		hygiene_status -= 10;
		sleep(30);
	}
}

void *health(void *arg)
{
	while(1) {
		while(!standby) {

		}
		health_status += 5; 
		sleep(10);
	}
}

int main(void)
{   
    system("clear");
	  printf("Beri nama monster lucu kamu : ");
	  scanf("%s", monster);

    system("clear");

	key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	shop_food_stock = shmat(shmid, NULL, 0);

    pthread_create(&(tid[0]), NULL, &hitungwaktu, NULL);
    pthread_create(&(tid[1]), NULL, &hunger, NULL);
    pthread_create(&(tid[2]), NULL, &hygiene, NULL);
    pthread_create(&(tid[3]), NULL, &health, NULL);
    stand_by_mode();
    
    return 0;
}