#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define PRODUCERS 3
#define CONSUMERS 2

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        int item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Producer %d produced %d\n", id, item);
        in = (in + 1)% SIZE; 

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

void *consumer(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
         printf("Consumer %d consumed %d\n", id, item);
         out = (out + 1 ) % SIZE ;

         sem_post(&mutex);
         sem_post(&empty);

         sleep(2);

    }
    
}

int main()
{
    pthread_t p[PRODUCERS], c[CONSUMERS];
    int pid[PRODUCERS], cid[CONSUMERS];

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < PRODUCERS; i++)
    {
        pid[i] = i + 1;
        pthread_create(&p[i], NULL, producer, &pid[i]);
    }

    for (int i = 0; i < CONSUMERS; i++)
    {
        cid[i] = i + 1;
        pthread_create(&c[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < PRODUCERS ; i++)
    {
        pthread_join(p[i] , NULL);
    }

    for (int i = 0; i < CONSUMERS; i++)
    {
        pthread_join(c[i] , NULL);
    }

    return 0 ;
    
    
}