#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>


/**
*  Write a program that creates 20 threads, giving each thread a string as parameter.
Each thread will count and add to the global variables v and n as follows:
the number of vowels contained by the string added to v, and the number of digits contained in
the string added to n. Synchronise threads using mutex and check for memory leaks.
*/
/
// Global counters for vowels and digits
int v = 0, n = 0;

// Mutexes for thread-safe updates
pthread_mutex_t mutexV, mutexN;

// Helper to check if a character is a vowel
int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Thread function to count vowels and digits in its string
void* count(void* arg) {
    char* str = (char*) arg;

    for (int i = 0; str[i]; i++) {
        if (is_vowel(str[i])) {
            pthread_mutex_lock(&mutexV);
            v++;
            pthread_mutex_unlock(&mutexV);
        }
        if (isdigit(str[i])) {
            pthread_mutex_lock(&mutexN);
            n++;
            pthread_mutex_unlock(&mutexN);
        }
    }

    free(str);
    return NULL;
}

int main() {
    pthread_t threads[20];
    pthread_mutex_init(&mutexV, NULL);
    pthread_mutex_init(&mutexN, NULL);

    for (int i = 0; i < 20; i++) {
        char buffer[100];

        printf("Enter string for thread %d: ", i + 1);
        scanf("%s", buffer);  // Assumes strings without spaces

        // Allocate and copy user input
        char* str = malloc(strlen(buffer) + 1);
        strcpy(str, buffer);

        pthread_create(&threads[i], NULL, count, str);
    }

    for (int i = 0; i < 20; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutexV);
    pthread_mutex_destroy(&mutexN);

    printf("\nFinal results:\n");
    printf("Total vowels: %d\n", v);
    printf("Total digits: %d\n", n);

    return 0;
}
