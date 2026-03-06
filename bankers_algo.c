#include <stdio.h>
#include <stdbool.h>

#define MAX 10 // maximum no. of processes is 10
int main ()
{
	int n_processes, n_resources;
	printf("Enter the number of processes: ");
	scanf("%d", &n_processes);
	

	printf("Enter the number of resources: ");
	scanf("%d", &n_resources);
	
	
	int current_allocation[MAX][MAX];
	int max_allocation_possible[MAX][MAX];
	
	printf("\nEnter the maximum allocation of resources for each processes: \n");
	for (int i = 0; i < n_processes; i++)
	{
		printf("Process %d maximum requirement of resources: \n", i + 1);
		for (int j = 0; j < n_resources; j++)
			scanf("%d", &max_allocation_possible[i][j]);
	}
	
	printf("\n");
	printf("\nEnter the current allocation schemas for each processes: \n");
	for (int i = 0; i < n_processes; i++)
	{
		printf("Process %d requirements: \n", i + 1);
		for (int j = 0; j < n_resources; j++)
			scanf("%d", &current_allocation[i][j]);
	}
	
	int available_resources[MAX];
	printf("\nEnter the available resources: \n");
	for (int i = 0; i < n_resources; i++)
	{
		printf("Resource %d: ", i + 1);
		scanf("%d", &available_resources[i]);
	}
	
	int need[MAX][MAX];
	for (int i = 0; i < n_processes; i++)
		for (int j = 0; j < n_resources; j++)
			need[i][j] = max_allocation_possible[i][j] - current_allocation[i][j];
	
	bool process_status[MAX] = {false};
	int final_alloc[MAX];
	int k = 0;
	bool solution = false;
	while (true)
	{
		int total_req = 0;
		for (int j = 0; j < n_processes; j++)
			if (process_status[j] == false)
				total_req ++;
		if (total_req == 0)
		{
			solution = true;
			printf("Success, there is a possible allocation. . . \n");
			break;
		}
		
		bool progress_made = false;
		for (int i = 0; i < n_processes; i++)
		{
			if (process_status[i] == false)
			{
				bool is_satisfiable = true;
				for (int j = 0; j < n_resources; j++)
				{
					if (need[i][j] > available_resources[j])
					{
						is_satisfiable = false;
						break;
					}
				}
				if (is_satisfiable)
				{
					progress_made = true;
					process_status[i] = true;
					for (int j = 0; j < n_resources; j++)
						available_resources[j] += current_allocation[i][j];
					final_alloc[k] = i;
					k++;
				}
			}
		}
		if (progress_made)
			continue;
		else
		{
			printf("ERROR: No progress made in an iteration, having atleast one requesting process. \n");
			break;
		}
	}
	if (solution)
	{
		printf("\nA valid sequence is: \n[");
		for (int i = 0; i < n_processes; i++)
		{
			if (i == n_processes - 1)
				printf("Process %d]", final_alloc[i]);
			else
				printf("Process %d, ", final_alloc[i]);
		}
	}
	printf("\n");
	return 0;
}
