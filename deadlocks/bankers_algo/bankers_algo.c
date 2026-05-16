#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_proc 10

void display(int* arr, int n)
{
	printf("The safe sequence is: \n[");
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1)
			printf("P%d]\n", arr[i] + 1);
		else
			printf("P%d, ", arr[i] + 1);
	}
}

bool bankers_safety_algo(int n_proc, int n_res, int curr_alloc[n_proc][n_res], int need[n_proc][n_res], int *available, int *safe_seq)
{
	bool progress;
	int status[n_proc];
	for (int i = 0; i < n_proc; i++)
		status[i] = 0;
	int sp = 0; // pointer to the safe sequence
	int no_completed = 0;
	
	for (int i = 0; i < n_proc; i = (i + 1) % n_proc)
	{
		if (i == 0)
			progress = false;
		if (no_completed == n_proc)
			return true;
		
		if (status[i] == 0)
		{
			int doable = 1;
			for (int j = 0; j < n_res; j++)
				if (need[i][j] > available[j])
					doable = 0;
			if (doable)
			{
				for (int j = 0; j < n_res; j++)
					available[j] += curr_alloc[i][j];
				status[i] = 1;
				safe_seq[sp++] = i;
				no_completed++;
				progress = true;
			}
		}
		if (i + 1 == n_proc && progress == false)
			return false;
	}
}

int main()
{
	int n_proc;
	int n_res;
	printf("Enter the no. of processes: ");
	scanf("%d", &n_proc);
	printf("\nEnter the no. of resources: ");
	scanf("%d", &n_res);
	
	int max_req[n_proc][n_res];
	printf("\nEnter the MAXIMUM ALLOCATION matrix for the proceses: \n");
	for (int i = 0; i < n_proc; i++)
	{
		printf("Process %d: ", i + 1);
		for (int j = 0; j < n_res; j++)
			scanf("%d", &max_req[i][j]);
		printf("\n");
	}
	
	int curr_alloc[n_proc][n_res];
	printf("\nEnter the CURRENT ALLOCATION matrix for the proceses: \n");
	for (int i = 0; i < n_proc; i++)
	{
		printf("Process %d: ", i + 1);
		for (int j = 0; j < n_res; j++)
			scanf("%d", &curr_alloc[i][j]);
		printf("\n");
	}
	
	int need[n_proc][n_res];
	for (int i = 0; i < n_proc; i++)
		for (int j = 0; j < n_res; j++)
			need[i][j] = max_req[i][j] - curr_alloc[i][j];
			
	int available[n_res];
	printf("Enter the AVAILABLE MATRIX: \n");
	for (int i = 0; i < n_res; i++)
		scanf("%d", &available[i]);
	
	int safe_seq[n_proc];
	for (int i = 0; i < n_proc; i++)
		safe_seq[i] = -1;
		
	bool ans = bankers_safety_algo(n_proc, n_res, curr_alloc, need, available, safe_seq);
	if (!ans)
		printf("No safe sequence\n");
	else
	{
		printf("Safe sequence exists !\n");
		display(safe_seq, n_proc);
	}
	return 0;
}