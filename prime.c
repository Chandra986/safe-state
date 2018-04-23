#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define MIN_USER_INPUT 2
#define MAX_USER_INPUT 1000

void *getUserInput(){
    int *number_from_user=(int *)malloc(sizeof(int));

    puts("Enter a number to print all prime numbers in range [0 - number]");

    while(1){
        printf("Input : ");
        scanf("%d",number_from_user);

        if(*number_from_user<MIN_USER_INPUT  ||*number_from_user>MAX_USER_INPUT){
            printf("Please Enter a positive number from %d to %d\n",MIN_USER_INPUT,MAX_USER_INPUT);
            
            rewind(stdin);
        }else break;
    }
    puts("Input thread received user input.");
    
    pthread_exit(number_from_user);
}
int checkPrime(int number){
    if(number==1) return 0; 
    int i;
     
    for(i=2; i<=(int)(number/2); i++)
        if(!(number%i)) return 0; 
    return 1;
}
void *printPrimeUntil(void *argument){
    int number = *((int *)argument),i,count=0;

    printf("Thread two received : %d\n",number);

    for(i=2; i<=number; i++){
        if(checkPrime(i)){
            printf("%5d",i);
            if(!(++count%5))       
                printf("\n");
        }
    }
    pthread_exit(NULL);
}
int main(){
    pthread_t input_thread, output_thread;
    void *ret_number;

    
    if(pthread_create(&input_thread,NULL,getUserInput,NULL))
        return -1*printf("Error in thread creation!!!\n");

    pthread_join(input_thread,&ret_number);

    int *number = (int *)ret_number;

    
    if(pthread_create(&output_thread,NULL,&printPrimeUntil,(void *)number))
       return -1*printf("Error in thread creation!!!\n");

    return pthread_join(output_thread,NULL); 
}








