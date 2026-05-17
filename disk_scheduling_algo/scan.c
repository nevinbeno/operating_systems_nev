#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
    return (*((int*)a) - *((int*)b));
}

int scan(int head, int n_req, int* arr)
{
    qsort(arr, n_req, sizeof(int), compare);
    if (head >= arr[n_req - 1])
        return head;
    else
        return head + arr[n_req - 1];
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
    
    int total_moves = scan(head, n_req, arr);
    printf("\nTotal no of head movements is: %d\n", total_moves);
    return 0;
}