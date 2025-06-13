#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    printf("A %d %d\n",getppid(),getpid());
    if(fork() == 0){

        printf("B %d %d\n", getppid(),getpid());
        if(fork() == 0){
            printf("C %d %d\n", getppid(),getpid());
            if(fork() == 0){
                printf("D %d %d\n",getppid(),getpid());
                exit(0);
            }
            wait(0);
            exit(0);
        }
        wait(0);
        exit(0);
    }
    //wait(0);
    exit(0);
}