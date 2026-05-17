#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main ()
{
    int n_req, start;
    printf("Enter the no. of requests: ");
    scanf("%d", &n_req);
    printf("Enter the initial head position: ");
    scanf("%d", &start);

    int arr[n_req];
    printf("Enter the request sequence: \n");
    for (int i = 0; i < n_req; i++)
        scanf("%d", &arr[i]);
    
    int sum = 0;
    for (int i = 0; i < n_req - 1; i++)
        sum += abs(arr[i] - arr[i + 1]);
    sum += abs(arr[0] - start);
    printf("The total head movements: %d\n", sum);
    return 0;
}