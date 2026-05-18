#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

sem_t forks[N];

struct philosopher
{
    int id;
    int left_fork;
    int right_fork;
    bool reversed;
};

void* dine(void* arg)
{
    struct philosopher* p = (struct philosopher*)arg;
    for (int i = 0; i < 1; i++) // a definite count & design principle for reusability
    {
        printf("Philosopher %d is thinking...\n", p->id);
        sleep(1);

        if (p->reversed)
        {
            sem_wait(&forks[p->right_fork]);
            printf("Philosopher %d picked fork %d..\n", p->id, p->right_fork);
            sleep(1);
            sem_wait(&forks[p->left_fork]);
            printf("Philpsopher %d picked fork %d..\n", p->id, p->left_fork);
            sleep(1);
        }
        else
        {
            sem_wait(&forks[p->left_fork]);
            printf("Philosopher %d picked fork %d..\n", p->id, p->left_fork);
            sleep(1);
            sem_wait(&forks[p->right_fork]);
            printf("Philpsopher %d picked fork %d..\n", p->id, p->right_fork);
            sleep(1);
        }
        printf(YELLOW"Philosopher %d attained both forks; eating...\n"RESET, p->id);
        sleep(2);
        printf("Philosopher %d has finished eating\n", p->id);
        sem_post(&forks[p->left_fork]);
        sem_post(&forks[p->right_fork]);
        printf("Philosopher %d has released both of their forks..\n", p->id);
    }
}

int main ()
{
    pthread_t threads[N];
    struct philosopher p[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        p[i].id = i;
        p[i].left_fork = i;
        p[i].right_fork = (i + 1) % N;
        if (p[i].left_fork < p[i].right_fork)
            p[i].reversed = false;
        else
            p[i].reversed = true;
        pthread_create(&threads[i], NULL, dine, &p[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}