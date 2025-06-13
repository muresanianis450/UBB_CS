#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int v2 = 0, v3 = 0, v5 = 0;

int total_generated = 0;
pthread_mutex_t mutex2, mutex3, mutex5,mutex_total_generated;


void* generate_numbers(void* arg){

    (void) arg;
    while(1){

        pthread_mutex_lock(&mutex_total_generated);

        if(total_generated >= 30 ){

            pthread_mutex_unlock(&mutex_total_generated);
            break;
        }


        total_generated++;
        pthread_mutex_unlock(&mutex_total_generated);

        int num = rand()%100 + 1;
        printf("thread %ld generated number: %d\n", (long) pthread_self(),num);

        if(num %2 ==0 ) pthread_mutex_lock(&mutex2), v2++ , pthread_mutex_unlock(&mutex2);
        if(num % 3 == 0) pthread_mutex_lock(&mutex3), v3++, pthread_mutex_unlock(&mutex3);
        if( num % 5 == 0 ) pthread_mutex_lock(&mutex5), v5++, pthread_mutex_unlock(&mutex5);
    }

    return NULL;
}


int main(){

    srand(time(NULL));

    pthread_t threads[4] ; //Array to store thread IDs
    //

    pthread_mutex_init(&mutex2,NULL);
    pthread_mutex_init(&mutex3,NULL);
    pthread_mutex_init(&mutex5,NULL);
    pthread_mutex_init(&mutex_total_generated,NULL);
    for(int i = 0 ; i < 4; i++){

        pthread_create(&threads[i],NULL,generate_numbers,NULL);
    }
    for(int i = 0 ; i < 4; i++)
        pthread_join(threads[i], NULL);


    printf("\nFinal counts:\n");
    printf("v2 (multiples of 2): %d\n", v2);
    printf("v3 (multiples of 3): %d\n", v3);
    printf("v5 (multiples of 5): %d\n", v5);
    printf("Numbers generated: %d\n" , total_generated);
    pthread_mutex_destroy(&mutex_total_generated);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);
    pthread_mutex_destroy(&mutex5);
}