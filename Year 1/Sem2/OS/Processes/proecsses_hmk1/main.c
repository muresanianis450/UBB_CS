#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int call_compare(int a, int b){
    pid_t pid = fork();
    if( pid < 0 ){ perror("fork failed"); exit(1);}

    if(pid == 0 ){
        //in child process: replace with ./compare a b

        char arg1[20], arg2[20];
        sprintf(arg1,"%d",a);
        sprintf(arg2,"%d",b);
        execl("./compare","compare",arg1,arg2,NULL);
        perror("execl failed");
        exit(1); // if execl fails
    }

    //in parent process
    int status;
    waitpid(pid,&status,0);

    if ( WIFEXITED(status)){
        return WEXITSTATUS(status);
    }
    else
        return 1;

}

int main(){

    int numbers[100],n;

    printf("Enter the number of values: ");

    scanf("%d",&n);
    if(n < 2) {
        printf("Need at least two numbers to compare.\n");
        return 1;
    }
    printf("Enter %d integers:\n",n);
    for( int i = 0 ; i < n ; i++){
        scanf("%d",&numbers[i]);
    }

    int all_equal = 1;
    for( int i = 0; i < n -1 ; i++){
        if(call_compare(numbers[i],numbers[i+1]) != 0 ){
            all_equal = 0;
            break;
        }
    }

    if(all_equal)
        printf("All numbers are equal.\n");
    else
        printf("Not all numbers are equal.\n");
    return 0;


}