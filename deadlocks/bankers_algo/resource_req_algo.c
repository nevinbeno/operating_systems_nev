#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display(int* arr, int n)
{
	printf("The safe sequence is: \n[");
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1)
			printf("P%d]\n", arr[i]);
		else
			printf("P%d, ", arr[i]);
	}
}

bool bankers_resource_req_algo(int n_proc, int n_res, int curr[n_proc][n_res], int need [n_proc][n_res], int* available, int pid, int* req)
{
	for (int i = 0; i < n_res; i++)
		if (available[i] < req[i])
		{
			printf("Error: The new request is greater than available. \n");
			return false;
		}
	for (int i = 0; i < n_res; i++)
		if (need[pid][i] < req[i])
		{
			printf("Error: The new request is greater than need. \n");
			return false;
		}
	for (int i = 0; i < n_res; i++)
	{
		need[pid][i] -= req[i];
		curr[pid][i] += req[i];
		available[i] -= req[i];
	}
	return true;
}


bool bankers_safety_algo(int n_proc, int n_res, int curr_alloc[n_proc][n_res], int need[n_proc][n_res], int* available, int* safe_seq)
{
	int status[n_proc];
	for (int i = 0; i < n_proc; i++)
		status[i] = 0;
	bool progress;
	int completed = 0;
	int sp = 0;
	
	for (int i = 0; i < n_proc; i = (i + 1) % n_proc)
	{
		if (i == 0)
			progress = false; // reset
		if (completed == n_proc)
			return true;
		if (status[i] == 0)
		{
			bool doable = true;
			for (int j = 0; j < n_res; j++)
				if (need[i][j] > available[j])
					doable = false;
			
			if (doable)
			{
				progress = true;
				safe_seq[sp++] = i + 1;
				completed++;
				status[i] = 1;
				for (int j = 0; j < n_res; j++)
					available[j] += curr_alloc[i][j];
			}
		}
		if (i + 1 == n_proc && progress == false)
			return false;
	}
}

int main ()
{
	int n_proc, n_res;
	printf("Enter the no of processes: ");
	scanf("%d", &n_proc);
	printf("\nenter the no. of resources: ");
	scanf("%d", &n_res);
	
	int max_alloc[n_proc][n_res];
	printf("Enter the MAX allocation matrix: \n");
	for ( int i = 0; i < n_proc; i++)
	{
		printf("Process %d: ", i + 1);
		for (int j = 0; j < n_res; j++)
			scanf("%d", &max_alloc[i][j]);
		printf("\n");
	}
	
	int curr_alloc[n_proc][n_res];
	printf("Enter the current Alocation matrix: \n");
	for ( int i = 0; i < n_proc; i++)
	{
		printf("Process %d: ", i + 1);
		for (int j = 0; j < n_res; j++)
			scanf("%d", &curr_alloc[i][j]);
		printf("\n");
	}
	
	int need[n_proc][n_res];
	for (int i = 0; i < n_proc; i++)
		for (int j = 0; j < n_res; j++)
			need[i][j] = max_alloc[i][j] - curr_alloc[i][j];
	
	int available[n_res];
	printf("Enter Available Matrix: \n");
	for (int i = 0; i < n_res; i++)
		scanf("%d", &available[i]);
	
	
	int pid;
	printf("\nEnter the pid of the process you want to ask for new request: ");
	scanf("%d", &pid);
	pid--;
	int req[n_res];
	printf("\nEnter the new request sequence for Process P%d: ", pid + 1);
	for (int i = 0; i < n_res; i++)
		scanf("%d", &req[i]);
	
	bool is_valid = bankers_resource_req_algo(n_proc, n_res, curr_alloc, need, available, pid, req);
	
	if (!is_valid)
		return 0;
	int safe_seq[n_proc];
	bool is_safe = bankers_safety_algo(n_proc, n_res, curr_alloc, need, available, safe_seq);
	
	if (is_safe)
		display(safe_seq, n_proc);
	else
		printf("No safe sequence, \n");
		
	return 0;
}