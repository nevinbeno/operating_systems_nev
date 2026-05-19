#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t wrt;
sem_t read_mutex;
sem_t write_mutex;
sem_t read_gate;

int readcount = 0;
int writecount = 0;

struct writer
{
    int id;
};

struct reader
{
    int id;
};

void* reader_fn(void* arg)
{
    sem_wait(&read_gate);
    sem_post(&read_gate);

    struct reader* r = (struct reader*)arg;
    printf("Reader Process R %d: requested to read..\n", r->id);

    sem_wait(&read_mutex);
    readcount++;
    if (readcount == 1)
    {
        sem_wait(&wrt);
        printf("First read: writes blocked\n");
    }
    sem_post(&read_mutex);

    printf("Reader Process R %d: Reading..\n", r->id);
    sleep(1);
    printf("Reader Process R %d: Reading completed..\n", r->id); 

    sem_wait(&read_mutex);
    readcount--;
    if (readcount == 0)
    {
        sem_post(&wrt);
        printf("Last read: writes enabled..\n");
    }
    sem_post(&read_mutex);

    return NULL;
}

void* writer_fn(void* arg)
{
    struct writer* w = (struct writer*)arg;
    printf("Writer Process W %d: requested to write..\n", w->id);

    sem_wait(&write_mutex);
    writecount++;
    
    if (writecount == 1)
    {
        printf("Write request detected.. Hence, readers are bocked..\n");
        sem_wait(&read_gate);
    }
    sem_post(&write_mutex);
    sem_wait(&wrt);
    printf("Writer Process W %d: acquired write lock..\n", w->id);

    printf("Writer Process W %d: Writing..\n", w->id);
    sleep(2);
    printf("Writer Process W %d: Writing Completed..\n", w->id);

    sem_post(&wrt);
    printf("Writer Process W %d: released write lock..\n", w->id);
    sem_wait(&write_mutex);
    writecount--;
    if (writecount == 0)
    {
        printf("Last Write.. Hence, readers are enabled..\n");
        sem_post(&read_gate);
    }
    sem_post(&write_mutex);

    return NULL;
}

int main()
{
    int n_r, n_w;
    printf("Enter the no. of readers: ");
    scanf("%d", &n_r);
    printf("Enter the no. of writers: ");
    scanf("%d", &n_w);

    sem_init(&read_gate, 0, 1);
    sem_init(&read_mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    struct writer w[n_w];
    struct reader r[n_r];

    pthread_t r_thread[n_r];
    pthread_t w_thread[n_w];

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