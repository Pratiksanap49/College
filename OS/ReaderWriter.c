#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t r, w;
int count = 0;

void *reader(void *arg)
{
    sem_wait(&r);
    count++;

    if (count == 1)
    {
        sem_wait(&w);
    }
    sem_post(&r);

    printf("Reader %ld is READING\n", pthread_self());
    sleep(1);

    sem_wait(&r);
    count--;

    if (count == 0)
    {
        sem_post(&w);
    }

    sem_post(&r);

    return NULL;
}
void *writer(void *arg)
{
    sem_wait(&w);

    printf("Writter %ld is WRITING\n", pthread_self());
    sleep(1);

    sem_post(&w);

    return NULL;
}

int main()
{
    pthread_t read[3], writeT[3];

    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&read[i], NULL, reader, NULL);
        pthread_create(&writeT[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(read[i], NULL);
        pthread_join(writeT[i], NULL);
    }

    return 0;
}