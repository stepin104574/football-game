#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include <semaphore.h> 
#include <unistd.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include "passer.h"
#include "receiver.h"
void* task_body();
void* task_body2();
void* task_body3();
void* task_body4();
sem_t mutex;
int main(void)
{

    sem_init(&mutex,0,1);
    pthread_t thread[4];
    pthread_create(&thread[0], NULL, task_body, NULL);
    pthread_create(&thread[1], NULL, task_body2, NULL);
    pthread_create(&thread[2], NULL, task_body3, NULL);
    pthread_create(&thread[3], NULL, task_body4, NULL);
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    pthread_join(thread[2],NULL);
    pthread_join(thread[3],NULL);
    pthread_exit(NULL);
    sem_destroy(&mutex);
    return EXIT_SUCCESS;
}

void* task_body()
{
    sem_wait(&mutex);
    printf("1st person passing the ball to 2nd person\n");
        passer();
       sem_post(&mutex);
    return NULL;
}
void* task_body2()
{
    sem_wait(&mutex);
        sleep(1);
        printf("Second person RECEIVED the ball from 1st person\n");
        receiver();
        sleep(3);
    	printf("2nd person passing the ball to 3rd person\n");
        passer();
    sem_post(&mutex);
    return NULL;
    EXIT_SUCCESS;
}
void* task_body3()
{
    sem_wait(&mutex);
        sleep(1);
        printf("3rd person RECEIVED the ball from 2nd person\n");
        receiver();
        sleep(3);
    	printf("3rd person passing the ball to 1st person\n");
        passer();
    sem_post(&mutex);
    return NULL;
    EXIT_SUCCESS;
}
void* task_body4()
{
    sem_wait(&mutex);
        sleep(1);
        printf("1st person RECEIVED the ball from 3rd person\n");
        receiver();
        printf("Passing Complete\n");
    sem_post(&mutex);
    return NULL;
    EXIT_SUCCESS;
}
