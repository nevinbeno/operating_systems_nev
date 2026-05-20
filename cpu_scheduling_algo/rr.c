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
	int rt;
};

void rr(int n_proc, struct process* p)
{
	
}

int main()
{
	int n_proc;
	printf("Enter the no of processes: ");
	scanf("%d", &n_proc);

	struct process p[n_proc];

	return 0;
}