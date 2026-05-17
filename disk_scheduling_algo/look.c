#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
	return (*((int*)a) - *((int*)b));
}

int look(int* arr, int size, int head)
{
	qsort(arr, size, sizeof(int), compare);
	int sum = 0;
	sum += abs(arr[0] - arr[size -1]);
	if (head > arr[size - 1])
		sum += abs(head - arr[size - 1]);
	else
		sum += abs(head - arr[0]);
	return sum;
}

int main ()
{
    int n_req, head;
    printf("Enter the no. of requests: ");
    scanf("%d", &n_req);
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int arr[n_req];
    printf("Enter the request sequence: \n");
    for (int i = 0; i < n_req; i++)
        scanf("%d", &arr[i]);
    
    int total_moves = look(arr, n_req, head);
    printf("\nTotal no of head movements is: %d\n", total_moves);
    return 0;
}