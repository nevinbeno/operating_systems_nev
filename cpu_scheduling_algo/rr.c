#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

struct md
{
	int at;
	int bt;
	int ct;
	int rt;;
	int tat;
	int wt;
};

int main ()
{
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	
	printf("\nAssumption: arrival time of all process are 0. \n");
	
	printf("Enter the burst time for the  processes: ");
	
	struct md process[50];
	for (int i = 0; i < n; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &process[i].bt);
		process[i].rt = process[i].bt;
		process[i].at = 0;
	}
	
	int tq;
	printf("Enter the time quantum: ");
	scanf("%d", &tq);
	
	bool finished = true;
	int time = 0;
	
	printf("The order of execution: \n");
	do
	{
		finished = true;
		for (int i = 0; i < n; i ++)
		{
			if (process[i].rt > 0)
			{
				finished = false;
				if (process[i].rt > tq)
				{
					printf("Process %d: (%d -> %d)\n", i, time, time + tq);
					process[i].rt -= tq;
					time += tq;
				}
				else
				{
					printf("Process %d: (%d -> %d)\n", i, time, time + process[i].rt);
					time += process[i].rt;
					process[i].rt = 0; // process i finishes. 
					process[i].ct = time;
					process[i].tat = process[i].ct - process[i].at;
					process[i].wt = procecss[i].tat - process[i].bt;
				}
			}
		}
	}while(!finished);
	
	
	return 0;
}
