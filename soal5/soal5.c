#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <termios.h>

char nama_monster[30];
int hunger_status=200, health_status=300, hygiene_status=100, my_food_stock=100, cooldown=20, scene=0, enemy_health_status=100;
char pilih, sampah;

// key press
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

// fungsi nampil
void tampil(){
    while(1){
        if (scene == 0) {
            printf("Standby Mode\n");
            printf("Health: %d \n", health_status);
            printf("Hunger: %d \n", hunger_status);
            printf("Hygiene: %d \n", hygiene_status);
            printf("Health: %d \n", health_status);
            printf("Food left : %d\n", my_food_stock);
            printf("Bath will be ready in %ds \n", cooldown);
            printf("Choiches\n");
            printf("1. Eat\n");
            printf("2. Bath\n");
            printf("3. Battle\n");
            printf("4. Shop\n");
            printf("5. Exit\n");
            scene = mygetch();
        }

        if (scene == 1){
            printf("Battle Mode\n");
            printf("Monster's Health: %d \n", health_status);
            printf("Monster's Health %d \n", hunger_status);
            printf("Choiches\n");
            printf("1. Attack\n");
            printf("2. Run\n");
        }

        if (scene == 2){
            printf("Shop Mode\n");
            printf("Shop Food Stock: %d \n", health_status);
            printf("Your Food Stock: %d \n", hunger_status);
            printf("Choiches\n");
            printf("1. Buy\n");
            printf("2. Back\n");
        }
        
        sleep(1);
        //system("cls");
    }
    
}

void action(char pilih){
    if(pilih == '1'){
        printf("fungsi %c\n", pilih);
    }

    if(pilih == '2'){
        printf("fungsi %c\n", pilih);
    }

    if(pilih == '3'){
        printf("fungsi %c\n", pilih);
    }

    if(pilih == '4'){
        printf("fungsi %c\n", pilih);
    }

    if(pilih == '5'){
        printf("fungsi %c\n", pilih);
    }
}

void hunger_kurang(){
    while(1){
        if(1){
            hunger_status = hunger_status - 5;
            printf("hunger_status = %d\n", hunger_status);
            sleep(2);
        }
    }
}

int main(){
    printf("Masukkan nama monster kamu: ");scanf("%s", nama_monster);
    printf("%s\n", nama_monster);
    tampil();
    scanf("%c",&sampah);
    //scanf("%c",&pilih);
    action(scene);
    hunger_kurang();
}