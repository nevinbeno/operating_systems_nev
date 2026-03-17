#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_DISK 5000
#define NO_OF_CYLINDERS 10

int compare(const void* a, const void* b)
{
	return (*((int*)a) - *((int*)b));
}

int binarySearch(int* arr, int total, int key)
{
	int left = 0, right = total - 1;
	while(left <= right)
	{
		int mid = left + (right - left) / 2;
		if (key >= arr[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}

int absol(int a, int b)
{
	return abs(a - b);
}

void look(int* req, int total, int curr_head)
{
	printf("\n == LOOK Disk Scheduling Algo Implementation == \n");
	printf("We assume that, the head first, moves to the direction of increasing cylinder number. \n");
	int total_disk_moves = 0;
	
	int locn = binarySearch(req, total, curr_head);
	int return_locn = locn;
	if (req[locn] == curr_head)
		return_locn -= 1;
	locn++;
	printf("The path: \n");
	printf("%d ", curr_head);
	while(locn < total)
	{
		total_disk_moves += absol(curr_head, req[locn]);
		curr_head = req[locn];
		printf(" -> %d ", curr_head);
		locn++;
	}
	while(return_locn >= 0)
	{
		total_disk_moves += absol(curr_head, req[return_locn]);
		curr_head = req[return_locn];
		printf(" -> %d ", curr_head);
		return_locn--;
	}
	
	printf("\nThe total no of moves made = %d\n", total_disk_moves);
}

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: <%s, initial head position>\n", argv[0]);
		return 1;
	}
	
	int req[NO_OF_CYLINDERS];
	srand(time(NULL));
	
	sleep(1);
	
	printf("Let those random cylinders be: \n[");
	for (int i = 0; i < NO_OF_CYLINDERS; i++)
	{
		req[i] = rand() % MAX_DISK;
		if (i == NO_OF_CYLINDERS - 1)
			printf("%d]\n", req[i]);
		else
			printf("%d, ", req[i]);
	}
	
	qsort(req, NO_OF_CYLINDERS, sizeof(int), compare);
	
	look(req, NO_OF_CYLINDERS, atoi(argv[1]));
	printf("\n");
	return 0;
}
