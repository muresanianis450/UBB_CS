#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//fd[0] - read end
//fd[1] - write end
//

int main(int argc, char* argv[]){

    (void) argc;
    (void) argv;


    int fd[2]; //creating the pipe

    if(pipe(fd) == -1){
        printf("An error ocurred while creating the pipe");
        exit(1);
    }
    int pid = fork();

    if(pid == -1){
        printf("An error ocurred while forking");
        exit(1);
    }

    if(pid == 0){

        close(fd[0]);//Closing the read end of the pipe

        int x;
        printf("Enter a number to be read by the child process: ");

        scanf("%d",&x);

        write(fd[1],&x, sizeof(int));
        close(fd[1]);
    }else{
        close(fd[1]);
        int y;
        read(fd[0],&y,sizeof(int));
        close(fd[0]);
        printf("Got the number from child process: %d\n",y);
    }
    return 0;