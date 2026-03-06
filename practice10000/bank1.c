#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main ()
{
	int n_processes, n_resources;
	printf("Enter the number of processes: ");
	scanf("%d", &n_processes);
	printf("\nEnter the number of resources: ");
	scanf("%d", &n_resources);
	
	int max_requirement[MAX][MAX];
	printf("Enter the maximim requirement for each process (matrix of order %d x %d)\n(Space separated values)\n", n_processes, n_resources);
	for (int i = 0; i < n_processes; i++)
	{
		printf("Process %d max requirement: \n", i);
		for (int j = 0; j < n_resources; j++)
			scanf("%d", &max_requirement[i][j]);
	}
	
	printf("\n");
	int current_allocation[MAX][MAX];
	printf("Enter the current allocation for the processes: \n(Space separated values)\n");
	for (int i = 0; i < n_processes; i++)
	{
		printf("Currently allocated resources for Process %d: \n", i);
		for (int j = 0; j < n_resources; j++)
			scanf("%d", &current_allocation[i][j]);
	}
	
	int available_resources[MAX];
	printf("Enter the available resources: \n");
	for (int i = 0; i < n_resources; i++)
	{
		printf("Resource %d: ", i);
		scanf("%d", &available_resources[i]);
	}
	
	// calculation of need matrix: 
	int need[MAX][MAX];
	for (int i = 0; i < n_processes; i++)
		for (int j = 0; j < n_resources; j++)
			need[i][j] = max_requirement[i][j] - current_allocation[i][j];
	
	bool process_finished[MAX] = {false};
	int safe_sequence[MAX];
	int k = 0;
	bool solution = false;
	while(true)
	{
		int no_of_requests_to_be_done = 0;
		for (int i = 0; i < n_processes; i++)
			if (process_finished[i] == false)
				no_of_requests_to_be_done++;
		if (no_of_requests_to_be_done == 0)
		{
			solution = true;
			printf("\nA Safe Sequence Exists...\n");
			break;
		}
		bool progress_made = false; // assumption
		for (int i = 0; i < n_processes; i++)
		{
			if (process_finished[i] == false)
			{
				bool need_satisfied = true; // assumption
				for (int j = 0; j < n_resources; j++)
				{
					if (need[i][j] > available_resources[j])
					{
						need_satisfied = false;
						break;
					}
				}
				if (need_satisfied == true)
				{
					progress_made = true;
					for (int j = 0; j < n_resources; j++)
						available_resources[j] += current_allocation[i][j];
					process_finished[i] = true;
					safe_sequence[k] = i;
					k++;
				}
			}
		}
		if (progress_made == true)
			continue; //  next pass
		else
		{
			printf("\nThere Exists a pass in which no process requests could be satisfied. Hence, NO safe sequence..\n");
			break;
		}
	}
	if (solution == true)
	{
		printf("\nThe safe sequence is: \n[");
		for (int i = 0; i < n_processes; i++)
		{
			if (i == n_processes - 1)
				printf("Process %d]", safe_sequence[i]);
			else
				printf("Process %d, ", safe_sequence[i]);
		}
	}
		
	printf("\n");
	return 0;
}
