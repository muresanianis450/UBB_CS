#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int p,i;
    p = fork();

    if ( p == -1 ) {perror("fork impossible!"); exit(1);}

    if (p == 0) { // we are in the child process

        for(i = 0 ; i < 10 ; i++){
            printf("Child: i=%d pid=%d, ppid=%d\n", i,getpid(),getppid());
            //              exit(0);
        }


    }else{
        for(i = 0 ; i< 10 ; i++){
            printf("Parent: i=%d pid=%d ppid=%d\n",i,getpid(),getppid());
            wait(0);
        }

    }
    printf("Finished; pid=%d ppid=%d\n",getpid(),getppid());
}