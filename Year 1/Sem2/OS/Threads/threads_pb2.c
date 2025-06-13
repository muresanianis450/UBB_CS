#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



#define T 100
#define N 10000000

//Counter is global variable
//We need syncronize;
//
int counter =0;
pthread_mutex_t mtx;

void* increment(void* p)
{
    int i, t;
    for(i = 0; i< N; i++){

        pthread_mutex_lock(&mtx); // lock the access to counter so it works counter++
        counter++;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;

}

int main(){
    int i;

    pthread_t thr[T];

    pthread_mutex_init(&mtx,NULL);


    for(i = 0; i< T; i++){

        pthread_create(&thr[i],NULL,increment,NULL);

    }

    for(i = 0 ; i < T; i++){

        pthread_join(thr[i],NULL);

    }

    pthread_mutex_destroy(&mtx);
    printf("%i\n",counter);
    return 0;

}