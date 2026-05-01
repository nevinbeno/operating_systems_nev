#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_DISK 5000
#define NO_OF_CYLINDERS 10

int compare(const void* a, const void* b)
{
	return (*((int*)a) - *((int*)b));
}

int binarySearch(int* arr, int total, int num)
{
	int left = 0, right = total - 1;
	while(left <= right)
	{
		int mid = left + ((right - left) / 2);
		if (num >= arr[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right; // this value will be the index of exact same head cyl, or the index of cyl, just smaller than head cyl. 
}

int absol(int a, int b)
{
	return (((a - b) >= 0) ? (a - b) : (b - a));
}

void sstf(int* req, int total, int curr_head)
{
	int total_disk_moves = 0;
	int left = binarySearch(req, total, curr_head);
	int right = left + 1;
	
	int left_abs, right_abs;
	printf("Disk movement: \n");
	printf("%d ", curr_head);
	while(left >= 0 || right < total)
	{
		if (left >= 0)
			left_abs = absol(curr_head, req[left]);
		if (right < total)
			right_abs = absol(curr_head, req[right]);
		
		if (left >= 0 && right < total)
		{
			if (left_abs < right_abs)
			{
				total_disk_moves += left_abs;
				printf(" -> %d ", req[left]);
				curr_head = req[left];
				left--;
			}
			else
			{
				total_disk_moves += right_abs;
				printf(" -> %d ", req[right]);
				curr_head = req[right];
				right++;
			}
		}
		else if (left >= 0)
		{
			total_disk_moves += left_abs;
			printf(" -> %d ", req[left]);
			curr_head = req[left];
			left--;
		}
		else if (right < total)
		{
			total_disk_moves += right_abs;
			printf(" -> %d ", req[right]);
			curr_head = req[right];
			right++;
		}
	}
	printf("\nThe total disk movement = %d", total_disk_moves);
}

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: <%s, initial head position>\n", argv[0]);
		return 1;
	}
	srand(time(NULL)); // setting the seed for random number generation. 
	
	int requests[NO_OF_CYLINDERS];
	printf("Let those random cylinders are: \n[");
	for (int i = 0; i < NO_OF_CYLINDERS; i++)
	{
		requests[i] = rand() % MAX_DISK;
		if (i == NO_OF_CYLINDERS - 1)
			printf("%d]\n", requests[i]);
		else
			printf("%d, ", requests[i]);
	}
	
	sleep(1);
	//int array[6] = {10, 20, 40, 80, 90, 60};
	qsort(requests, NO_OF_CYLINDERS, sizeof(int), compare);
	//qsort(array, 6, sizeof(int), compare);
	
	sstf(requests, NO_OF_CYLINDERS, atoi(argv[1]));
	//sstf(array, 6, atoi(argv[1]));
	printf("\n");
	return 0;
}
