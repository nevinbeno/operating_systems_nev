#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

void display(struct process* p, int n)
{
    printf("== Result ==\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i ++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
}   

void srtf(struct process* p, int n)
{
    int time = 0, completed = 0;
    while(completed < n)
    {
        int index = -1;
        int min_rem = INT_MAX;

        for (int i = 0; i < n; i++)
            if (p[i].at <= time && p[i].rem > 0 && p[i].rem < min_rem)
            {
                index = i;
                min_rem = p[i].rem;
            }
        if (index == -1)
        {
            time++;
            continue;
        }
        p[index].rem--;
        time++;
        if (p[index].rem == 0)
        {
            completed++;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
        }
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

    
    srtf(p, n);

    display(p, n);
}