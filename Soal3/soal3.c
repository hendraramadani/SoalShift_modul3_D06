#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int wakeup_status=0,spirit_status=100;
char msg[30];
char dsblfitur[50];
int agflag=0,irflag=0,sleepcount=0,wakecount=0;
pthread_t tid;

void* t_Agmal(void* args){
	while(1){
		if(strcmp(dsblfitur,"Agmal Ayo Bangun disabled 10 s")==0 && sleepcount==3){
			printf("Disable : Agmal Ayo Bangun (10 Sec)\n");
			sleep(10);
			agflag=0;
			sleepcount=0;
			printf("Enable : Agmal Ayo Bangun\n");
		}else{
			if(agflag==1){
				wakecount++;
				wakeup_status+=15;

				if(wakecount>3){
					wakecount=1;
				}

				if(wakecount==3){
					memset(dsblfitur,0,30);
					strcpy(dsblfitur,"Fitur Iraj Ayo Tidur disabled 10 s");
				}
			agflag=0;
			}
		}	
	}
}

void* t_Iraj(void* args){
	while(1){
		if(strcmp(dsblfitur,"Fitur Iraj Ayo Tidur disabled 10 s")==0 && wakecount==3){
			printf("Disable : Iraj Ayo Tidur (10 Sec)\n");
			sleep(10);
			irflag=0;
			wakecount=0;
			printf("Enable : Iraj Ayo Tidur\n");
		}else{
			if(irflag==1){
				sleepcount++;
				spirit_status-=20;

				if(sleepcount>3){	
					sleepcount=1;
				}
				if(sleepcount==3){
					memset(dsblfitur,0,30);
					strcpy(dsblfitur,"Agmal Ayo Bangun disabled 10 s");
				}
			irflag=0;
			}
		}	
	}
}

int main(){
	pthread_create(&tid, NULL, &t_Agmal,NULL);
	pthread_create(&tid, NULL, &t_Iraj,NULL);

	while(wakeup_status<100 && spirit_status>0 && wakeup_status!=100 && spirit_status!=0){
		memset(msg,0,30);
		gets(msg);
		if(strcmp(msg,"All Status")==0){
			printf("Agmal->WakeUp_Status = %d\nIraj->Spirit_Status = %d\n",wakeup_status,spirit_status);
		}else
		if(strcmp(msg,"Agmal Ayo Bangun")==0){
			agflag=1;
		}else
		if(strcmp(msg,"Iraj Ayo Tidur")==0){
			irflag=1;
		}

		if(wakeup_status>=100){
        	printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
			return 0;
    	}else
		if(spirit_status<=0){
        	printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
			return 0;
   		}
	}  
}



