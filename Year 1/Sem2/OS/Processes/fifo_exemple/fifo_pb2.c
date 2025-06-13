#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *fifoAB = "fifoAB";
    const char *fifoBA = "fifoBA";

    // Create the FIFOs (named pipes)
    mkfifo(fifoAB, 0666);
    mkfifo(fifoBA, 0666);

    pid_t pidA = fork();

    if (pidA == -1) {
        perror("Fork A failed");
        exit(1);
    }

    if (pidA == 0) {
        // Child process A
        int fd_write = open(fifoAB, O_WRONLY);
        int fd_read = open(fifoBA, O_RDONLY);

        int n = 45;
        printf("Process A starts with %d\n", n);
        write(fd_write, &n, sizeof(int));

        while (1) {
            if (read(fd_read, &n, sizeof(int)) <= 0) break;

            if (n < 10) {
                printf("Process A received final value: %d\n", n);
                break;
            }

            printf("Process A received %d, subtracts 1 ---> %d\n", n, n - 1);
            n -= 1;
            write(fd_write, &n, sizeof(int));
        }

        close(fd_write);
        close(fd_read);
        exit(0);
    }
    // Only fork B after A to ensure correct FIFO order
    pid_t pidB = fork();

    if (pidB == -1) {
        perror("Fork B failed");
        exit(1);
    }

    if (pidB == 0) {
        // Child process B
        int fd_read = open(fifoAB, O_RDONLY);
        int fd_write = open(fifoBA, O_WRONLY);

        int n;
        while (1) {
            if (read(fd_read, &n, sizeof(int)) <= 0) break;

            if (n < 10) {
                printf("Process B received final value: %d\n", n);
                write(fd_write, &n, sizeof(int));
                break;
            }

            printf("Process B received %d, subtracts 4 ---> %d\n", n, n - 4);
            n -= 4;
            write(fd_write, &n, sizeof(int));
        }

        close(fd_write);
        close(fd_read);
        exit(0);
    }

    // Parent waits for both children
    wait(NULL);
    wait(NULL);

    // Cleanup FIFOs
    unlink(fifoAB);
    unlink(fifoBA);

    return 0;
}