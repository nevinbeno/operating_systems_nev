#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
    return (*((int*)a) - *((int*)b));
}

int binarySearch(int* arr, int n, int key)
{
    int left =0, right = n - 1;
    while(left <= right)
    {
        int mid = left + (right- left) / 2;
        if (key >= arr[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return right;
}

int c_scan(int* arr, int n, int head)
{
    if (n == 1)
        return abs(head - arr[0]);
    qsort(arr, n, sizeof(int), compare);
    if (head >= arr[n - 1])
        return head;
    else if (head < arr[0])
        return head + arr[n - 1] + abs(arr[n - 1] - arr[0]);
    else
    {
        int index = binarySearch(arr, n, head);
        index++;
        return head + arr[n - 1] + abs(arr[n - 1] - arr[index]);
    }
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
    
    int total_moves = c_scan(head, n_req, arr);
    printf("\nTotal no of head movements is: %d\n", total_moves);
    return 0;
}