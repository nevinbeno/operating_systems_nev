#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int rem;
    int ct;
    int tat;
    int wt;
};

int compare(const void* a, const void* b)
{
    struct process* p1 = (struct process*)a;
    struct process* p2 = (struct process*)b;

    return p1->at - p2->at;
}

void display(struct process* p, int n)
{
    printf("== Result ==\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i ++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
}

void fcfs(struct process* p, int n)
{
    int time = 0;
    qsort(p, n, sizeof(struct process), compare);
    time += p[0].at; // idle time

    for (int i = 0; i < n; i++)
    {
        if (p[i].at > time)
            time =p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

int main()
{
    int n;
    printf("Enter no. of proesses: ");
    scanf("%d", &n);

    struct process p[n];

    printf("Enter AT BT: \n");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i;
        printf("Process %d: ", i);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rem = p[i].bt;
    }

    
    fcfs(p, n);

    display(p, n);
}