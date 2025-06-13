#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){


    if( argc < 3){
        fprintf(stderr,"Usage: %s num1 num2 [num3...]\n",argv[0]);
        return 1;
    }
    int first = atoi(argv[1]);
    for(int i = 2; i < argc; i++){
        if(atoi(argv[i] )!= first)
            return 1; //Not all numbers are equal
    }
    return 0; //All numbers are equal

}