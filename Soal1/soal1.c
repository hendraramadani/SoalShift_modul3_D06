#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int arr[10000];
pthread_t tid[50];


struct Factorial{
	int val;
};

void* tulis(void* args){
    unsigned long long fctr=1;
    struct Factorial*extract =(struct Factorial*)args;
	for(int i=1; i<=extract->val; ++i)
        {
            fctr = i*fctr;          
        }
    printf("[ Thread %d sukses dibuat | %d! Factorial = %llu ]\n",extract->val,extract->val,fctr);

   printf("\n");
}



int main(){
  int i=0, j=0,order,x;
  char temp;
  do {
      scanf("%d%c", &arr[i], &temp);
      i++;
  } while(temp != '\n');
 

 for (i = 0; arr[i]!='\0'; ++i) 
        {
            for (j = i + 1; arr[j]!='\0'; ++j)
            {
                if (arr[i] > arr[j]) 
                {
                    x =  arr[i];
                    arr[i] = arr[j];
                    arr[j] = x;
                }
            }     
        }

   i=0;
  struct Factorial factorial;
  while(arr[i]!='\0') {
	factorial.val = arr[i];
	order=arr[i];
	pthread_create(&tid[order], NULL, &tulis,(void *)&factorial);
        pthread_join(tid[order],NULL);
    	i++;
  }
    
    return 0;
}



