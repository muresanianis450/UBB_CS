#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv){


    mkfifo("fifob2a", 0666);
    mkfifo("fifoa2b", 0666);

    int fa2b, fb2a;
    int fa = fork();
    if (fa < 0)
    {


        printf("error");
        exit (1);


    }

    if (fa == 0) // process A
    {


        int x1, x2;
        scanf("%d", &x1);
        scanf("%d", &x2);
        fa2b = open("fifoa2b", O_WRONLY); // Only for writing

        write(fa2b, &x1, sizeof(int));
        write(fa2b, &x2, sizeof(int));

        close(fa2b);

        fb2a = open("fifob2a", O_RDONLY);// Only for reading
        int d;
        read (fb2a, &d, sizeof(int));
        printf("%d", d);

        close(fb2a);
        exit(0);
    }


    else
    {


        int fb = fork();
        if (fb < 0)

        {

            printf("error");
            exit (1);

        }
        if (fb == 0) //process B
        {
            fa2b = open("fifoa2b", O_RDONLY);
            int x, xx;
            read(fa2b, &x, sizeof(int));
            read(fa2b, &xx, sizeof(int));

            close(fa2b);

            fb2a = open("fifob2a", O_WRONLY);
            int r = rand();
            if (x > xx)
            {int aux = xx;
                xx=x;
                x = aux;}

            while (!(r>x && r<xx))
            {
                r = rand();
            }
            write(fb2a,&r, sizeof(int));
            close(fb2a);
            exit(0);


        }

    }
    wait(0);
    wait(0);
    return (0);

}