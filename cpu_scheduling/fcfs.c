#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 10

float avg_waiting_time;
float avg_tat;

struct process_metadata
{
	int id;
	
	int arrival_time;
	int burst_time;
	
	int remaining_time; // rr
	int completion_time;
	int tat; // (completion_time - arrival time)
	int waiting_time; // (tat - burst_time)
};

void clear_calculations(struct process_metadata* process, int total)
{
	for (int i = 0; i < total; i++)
	{
		process[i].completion_time = 0;
		process[i].tat = 0;
		process[i].waiting_time = 0;
		process[i].remaining_time = 0;
	}
}

int compare(const void* a, const void* b)
{
	struct process_metadata* p1 = (struct process_metadata*)a;
	struct process_metadata* p2 = (struct process_metadata*)b;
	return (p1->arrival_time - p2->arrival_time);
}

int max(int a, int b)
{
	return (a > b ? a : b);
}

void export_csv(struct process_metadata* process, int total, char* filename)
{
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "Process ID, Arrival Time, Burst Time, Completion Time, Turn Around Time, Waiting time\n");
	for (int i = 0; i < total; i++)
	{
		fprintf(fp, "P%d, %d, %d, %d, %d, %d\n", 
			process[i].id, 
			process[i].arrival_time, 
			process[i].burst_time, 
			process[i].completion_time, 
			process[i].tat, 
			process[i].waiting_time);
	}
	fclose(fp);
}

void fcfs(struct process_metadata* process, int total)
{
	qsort(process, total, sizeof(struct process_metadata), compare);
	int current_time = 0;
	// assumption: arrival time is >= 0;
	process[0].completion_time = process[0].arrival_time + process[0].burst_time;
	process[0].tat = process[0].completion_time - process[0].arrival_time;
	process[0].waiting_time = process[0].tat - process[0].burst_time;
	for (int i = 1; i < total; i++)
	{
		process[i].completion_time = max(process[i - 1].completion_time, process[i].arrival_time) + process[i].burst_time;
		process[i].tat = process[i].completion_time - process[i].arrival_time;
		process[i].waiting_time = process[i].tat - process[i].burst_time;
	}
	int total_wt = 0, total_tat = 0;
	for (int i = 0; i < total; i++)
	{
		total_wt += process[i].waiting_time;
		total_tat += process[i].tat;
	}
	
	char filename[] = "fcfs.csv";
	export_csv(process, total, filename);
	printf("\n	FCFS update: fcfs.csv is saved in the directory, containing all the details of the processes. \n");
	
	avg_waiting_time = ((float)total_wt) / total;
	avg_tat = ((float)total_tat) / total;
	
	printf("\n === FCFS Scheduling ===\n");
	printf("	Average Waiting Time = %f\n", avg_waiting_time);
	printf("	Average Turn Around Time = %f\n", avg_tat);
	return;
}

int main ()
{
	printf("=== CPU Scheduling Algorithms Illustration ===\n\n");
	struct process_metadata process[MAX];
	
	int total_processes;
	printf("Enter the number of processes: ");
	scanf("%d", &total_processes);
	printf("The processes are assumed to be indexed as P0, ..., P%d\n", total_processes - 1);
	printf("Enter the metadata of each process: \n");
	for (int i = 0; i < total_processes; i++)
	{
		printf("Process %d: \n", i);
		process[i].id = i;
		printf("	Arrival time: ");
		scanf("%d", &process[i].arrival_time);
		printf("	Burst time: ");
		scanf("%d", &process[i].burst_time);
	}
	
	// fcfs
	fcfs(process, total_processes);
	
	clear_calculations(process, total_processes);
	
	return 0;
}
