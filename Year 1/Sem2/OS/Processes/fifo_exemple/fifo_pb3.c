#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//TODO NOT WORKING !
int main(){

    int p2c[2],c2p[2];

    if(pipe(p2c) == -1){
        printf("An error ocurred with opening the pipe\n");
        return 1;

    }
    if(pipe(c2p) == -1){
        printf("An error ocurred with opening the pipe\n");
        return 1;

    }
    char string[100];

    int id = fork();


    if ( id == 0) {
        //Child process

        read(p2c[0],string,strlen(string)*sizeof(char));

        for( int i = 0; i < strlen(string); i++)
            if(strchr("aeiou",string[i])){
                for(int j = i; j < strlen(string) - 1;j++)
                    string[j] = string[j+1];
                break;
            }
        write(c2p[1],string,strlen(string)*sizeof(char));
        close(c2p[1]);
        close(c2p[0]);
        close(p2c[1]);
        close(p2c[0]);
    }



    //Parent process
    printf("Enter a string: ");
    read("%s",string,sizeof(char)*100);
    printf("\n");
    printf("%s",string);
    return 0;





}
