#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    int fd[2];
    // fd[0] - read
    // fd[1] - write

    if (pipe(fd) == -1 ){
        printf("An error ocurred with opening the pipe\n");
        return 1;
    }
    int id  = fork();
    if(id == 0){
        close(fd[0]); //close the read end
        int x;
        printf("Input a number: ");
        scanf("%d",&x);
        write(fd[1],&x,sizeof(int)); // write to write end of the child
        close(fd[1]);
    }else{
        close(fd[1]); // close the write end of the parent
        int y;
        read(fd[0],&y,sizeof(int));
        close(fd[0]);
        printf("Got from child process %d\n",y);
    }
    return 0;

}