#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t wrt;
sem_t mutex;
int readcount = 0;
int n_r, n_w;

struct writers
{
    int id;
};

struct readers
{
    int id;
};

void* reader_fn(void* arg)
{
    struct readers* r = (struct readers*)arg;
    printf("Reader Process R %d requested to read..\n", r->id);
    for (int i = 0; i < 1; i++)
    {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
        {
            sem_wait(&wrt);
            printf("First reading attempt: Writer process blocked..\n");
        }
        sem_post(&mutex);
        printf("Reader Process R %d: Reading..\n", r->id);
        sleep(1);
        printf("Reader Process R %d: Reading Finished..\n", r->id);
        
        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&wrt);
            printf("Last reading attempt: Write enabled..\n");
        }
        sem_post(&mutex);        
    }
    return NULL;
}

void* writer_fn(void* arg)
{
    struct writers* w = (struct writers*)arg;
    printf("Writer Process W %d: requested to write..\n", w->id);
    sleep(1);
    for (int i = 0; i < 1; i++)
    {
        sem_wait(&wrt);
        printf("Writer Process W %d: attained write lock..\n", w->id);
        printf("Writer Process W %d: peforming write operation..\n", w->id);
        sleep(2);

        sem_post(&wrt);
        printf("Writer Process W %d: Released write lock..\n", w->id);
    }
    return NULL;
}

int main ()
{
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    printf("Enter the no. of readers: ");
    scanf("%d", &n_r);;
    printf("\nEnter the no of writers: ");
    scanf("%d", &n_w);

    pthread_t r_thread[n_r];
    pthread_t w_thread[n_w];

    struct writers w[n_w];
    struct readers r[n_r];

    for (int i = 0; i < n_r; i++)
    {
        r[i].id = i;
        pthread_create(&r_thread[i], NULL, reader_fn, &r[i]);
    }

    for (int i = 0; i < n_w; i++)
    {
        w[i].id = i;
        pthread_create(&w_thread[i], NULL, writer_fn, &w[i]);
    }

    for (int i = 0; i < n_r; i++)
        pthread_join(r_thread[i], NULL);


    for (int i = 0; i < n_w; i++)
        pthread_join(w_thread[i], NULL);
    return 0;
}