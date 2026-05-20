#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void display(int n, struct process* p)
{
	printf("== Result ==\n");
	printf("Pid  AT  BT  CT  TAT  WT \n");
	for (int i = 0; i < n; i++)
		printf("%d    %d  %d  %d  %d  %d \n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
}

void rr(int n_proc, struct process* p, int tq)
{
	int time = 0;
	int completed = 0;
	while(completed < n_proc)
	{
		bool executed = false;
		for (int i = 0; i < n_proc; i++)
		{
			if (p[i].at <= time && p[i].rem > 0)
			{
				executed = true;
				if (p[i].rem > tq)
				{
					p[i].rem -= tq;
					time += tq;
				}
				else
				{
					time += p[i].rem;
					p[i].ct = time;
					p[i].rem = 0;
					completed++;
				}
			}
		}
		if (!executed)
			time++;
	}

	for (int i = 0; i < n_proc; i++)
	{
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
	}

}

int main()
{
	int n_proc;
	printf("Enter the no of processes: ");
	scanf("%d", &n_proc);

	struct process p[n_proc];

	printf("Enter AT BT: \n");
	for (int i = 0; i < n_proc; i++)
	{
		printf("Process %d: ", i);
		p[i].pid = i;
		scanf("%d %d", &p[i].at, &p[i].bt);
		p[i].rem = p[i].bt;
	}

	int tq;
	printf("Time quantum: ");
	scanf("%d", &tq);

	rr(n_proc, p, tq);

	display(n_proc, p);

	return 0;
}