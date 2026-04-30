#include <stdio.h> // printf()
#include <stdlib.h> // qsort()
#include <time.h> // srand(), rand()
#include <unistd.h> // 

#define CYL 5000 // 0 to 4999
#define REQ 10 // maximum requests

int compare(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}	

int binarySearch(int* arr, int size, int key)
{
	int left = 0, right = size - 1;
	while(left <= right)
	{
		int mid = left + ((right - left) / 2);
		if (key >= arr[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}

int absolute(int a, int b)
{
	int ans = a - b;
	if (ans < 0)
		return -(ans);
	else
		return ans;
}

void sstf(int* arr, int size, int head)
{
	int total_head_movements = 0;
	int left = binarySearch(arr, size, head);
	int right = left + 1;
	
	int left_dist, right_dist;
	
	printf("Head movement: \n%d ", head);
	while(left  >= 0 || right < size)
	{
		if (left >= 0) // valid left index
			left_dist = absolute(arr[left], head);
		if (right < size) // valid right index
			right_dist = absolute(arr[right], head);
		if (left >= 0 && right < size)
		{
			if (right_dist < left_dist) // by default, we wish to move in left direction. 
			{
				total_head_movements += right_dist;
				head = arr[right];
				printf("-- (%d) -- > %d ", right_dist, head);
				right++;
			}
			else
			{
				total_head_movements += left_dist;
				head = arr[left];
				printf("-- (%d) -- > %d ", left_dist, head);
				left--;
			}
		}
		else if (left >= 0)
		{
			total_head_movements += left_dist;
			head = arr[left];
			printf("-- (%d) -- > %d ", left_dist, head);
			left--;
		}
		else if (right < size)
		{
			total_head_movements += right_dist;
			head = arr[right];
			printf("-- (%d) -- > %d ", right_dist, head);
			right++;
		}
	}
	printf("\nTotal distance covered by head = %d \n", total_head_movements);
}

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: <%s, Head starting position>\nProgram exiting with return value 1\n", argv[0]);
		return 1;
	}
	
	srand(time(NULL));
	int request[REQ];
	printf("Let the requests are: \n[");
	for (int i = 0; i < REQ; i++)
	{
		request[i] = rand() % CYL;
		if (i == REQ - 1)
			printf("%d]\n", request[i]);
		else
			printf("%d, ", request[i]);
	}
	
	qsort(request, REQ, sizeof(int), compare);
	
	int initialHeadPosition = atoi(argv[1]);
	sstf(request, REQ, initialHeadPosition);
	
	return 0;
}
