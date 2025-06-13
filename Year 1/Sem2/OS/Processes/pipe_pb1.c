
int main(){

    int p2c[2] ; // pipe parent to child
    int c2p[2] ; // pipe child to parent


    int a,b,s,pid;

    pipe(p2c);
    pipe(c2p);

    pid = fork();
    if( pid == -1) {printf("Error occured during forking..."); return 1;}

    if ( pid == 0){
        //Child process

        close(p2c[1]);
        read(p2c[0],&a,sizeof(int));
        read(p2c[0],&b,sizeof(int));

        s = a+b;

        write(c2p[1],&s,sizeof(int));

        close(p2c[0]);
        close(c2p[0]);
        close(c2p[1]);
        exit(0);
    }

    //parent process

    a = 7;
    b = 3;
    write(p2c[1],&a,sizeof(int));
    write(p2c[1],&b,sizeof(int));

    read(c2p[0],&s,sizeof(int));
    printf("Sum read from child process: %d\n",s);
    close(p2c[0]);
    close(p2c[1]);
    close(c2p[0]);
    close(c2p[1]);
    wait(0);



}