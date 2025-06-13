#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>



int main(int argc,char* argv[]){

    int arr[] = {1,2,3,4,1,2};
    int arrSize = sizeof(arr)/sizeof(int);
    int start,end;

    int fd[2];

    if(pipe(fd) == -1) return 1;

    int id = fork();

    if(id == -1)
        return 2;

    if(id == 0){
        start = 0;
        end = arrSize/2;

    }else{

        start= arrSize/2;
        end = arrSize;
    }


    int sum = 0 ;
    int i;
    for(i = start; i < end; i++){

        sum+=arr[i];
    }
    if( id == 0){

        close(fd[0]);
        write(fd[1],&sum,sizeof(int));
        close(fd[1]);

    }else{ int sumFromChild;
        close(fd[1]);
        write(fd[1],&sum,sizeof(int));
        close(fd[1]);

    }else{ int sumFromChild;
        close(fd[1]);
        read(fd[0],&sumFromChild,sizeof(sumFromChild));
        close(fd[0]);

        printf("Sum from children: %d\n",sumFromChild);
        int totalSum = sumFromChild + sum;
        printf("Sum from parend: %d\n",sum);
        printf("Calculated overall sum: %d\n",totalSum);
        wait(NULL);

    }
    return 0;
}