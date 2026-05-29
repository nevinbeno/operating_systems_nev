#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
};

void display(struct process* p, int n)
{
    printf("== Result ==\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i ++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
}

int compare(const void* a, const void* b)
{
    struct process* p1 = (struct process*)a;
    struct process* p2 = (struct process*)b;
    return p1->priority - p2->priority; // assumption: lower the number higher the priority
}

int compare2(const void* a, const void* b)
{
    struct process* p1 = (struct process*)a;
    struct process* p2 = (struct process*)b;
    return p1->pid - p2->pid;
}

void npps(struct process* p, int n)
{
    int time = 0;
    qsort(p, n, sizeof(struct process), compare);
    for (int i = 0; i < n; i++)
    {
        if (p[i].at > time)
            time = p[i].at;
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

    printf("Enter AT BT Priority: \n");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i;
        printf("Process %d: ", i);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
    }

    
    npps(p, n);
    qsort(p, n, sizeof(struct process), compare2);
    display(p, n);
}