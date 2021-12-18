//
//  MutualExclusion.cpp
//  MutualExclusion
//
//  Created by Sajjad Islam on 11/22/21.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int counter = 0;
sem_t semaphore;

void* thread_1_routine (void *arg) {
    while (1) {
        sem_wait(&semaphore);
        counter++;
        printf("Thread 1: Counter : %d\n",counter);
        //sleep(1);
        sem_post(&semaphore);
    }
    return NULL;
}

void* thread_2_routine (void *arg) {
    while (1) {
        sem_wait(&semaphore);
        counter--;
        printf("Thread 2: Counter : %d\n",counter);
        //sleep(1);
        sem_post(&semaphore);
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    pthread_t thread1, thread2;
    sem_init(&semaphore, 0, 1);
    pthread_create(&thread1, NULL, thread_1_routine, NULL);
    pthread_create(&thread2, NULL, thread_2_routine, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);
    return 0;
}
