#include <pthread.h>


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define N 4     // Number of runways (limited resource)
#define M 10    // Number of planes (more than runways)
#define SLEEP 4 // Max sleep time (simulates arrival and landing duration)



/**
* ## 📦 Problem Statement: Airport Runway Management

At a busy airport, there are **n runways** and **m planes** (`m > n`).
Each plane arrives randomly and waits to land.
If a runway is free, it lands immediately, occupies the runway for a random time, then frees it.

Only **n planes can occupy runways at the same time**.
Simulate the landing and runway usage using threads, semaphores, and a mutex for output and shared data access.
*/
/
// Semaphore for counting available runways
sem_t sem_runways;

// Mutex for synchronized access to shared resources (runway array and printing)
sem_t mtx;

// Runway status array: -1 = free, otherwise contains plane ID
int runways[N];

// Thread IDs and corresponding plane IDs
pthread_t tid[M];
int planes[M];

// Start time to print relative timestamps
time_t start;

// Function executed by each plane thread
void* land(void* arg) {
    int id = *(int*)arg; // Plane ID
    int r;               // Runway index

    // Simulate random arrival delay before plane reaches airport
    sleep(1 + rand() % SLEEP);

    // Print request to land (protected by mutex to avoid print collisions)
    sem_wait(&mtx);
    printf("Time %lu - Plane %d is requesting landing\n", time(NULL) - start, id);
    sem_post(&mtx);

    // Wait for a runway to become available
    sem_wait(&sem_runways);

    // Find a free runway and assign it to this plane
    sem_wait(&mtx);
    for (r = 0; r < N; r++) {
        if (runways[r] == -1) { // Free runway found
            runways[r] = id;    // Occupy the runway
            break;
        }
    }
    printf("Time %lu - Plane %d is landing on runway %d\n", time(NULL) - start, id, r);
    sem_post(&mtx);

    // Simulate landing duration
    sleep(1 + rand() % SLEEP);

    // Free the runway
    sem_wait(&mtx);
    printf("Time %lu - Plane %d has left runway %d\n", time(NULL) - start, id, r);
    runways[r] = -1;
    sem_post(&mtx);

    // Signal that a runway has become available
    sem_post(&sem_runways);

    return NULL;
}

int main() {
    srand(time(NULL)); // Seed random generator

    // Initialize semaphore for runways with value N (all runways initially free)
    sem_init(&sem_runways, 0, N);

    // Initialize mutex (binary semaphore)
    sem_init(&mtx, 0, 1);

    // Mark all runways as free (-1 = free)
    for (int i = 0; i < N; i++) runways[i] = -1;

    // Assign unique IDs to each plane
    for (int i = 0; i < M; i++) planes[i] = i;

    // Save start time to print relative moments
    start = time(NULL);

    // Create one thread for each plane
    for (int i = 0; i < M; i++)
        pthread_create(&tid[i], NULL, land, &planes[i]);
        // NOTE: We use &planes[i] instead of &i to avoid passing same address to all threads

    // Wait for all plane threads to finish
    for (int i = 0; i < M; i++)
        pthread_join(tid[i], NULL);

    // Clean up semaphores
    sem_destroy(&sem_runways);
    sem_destroy(&mtx);

    return 0;
}
