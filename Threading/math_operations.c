#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int a, b;

void* addition(void* arg)
{
	printf("\n=== Inside Thread 1 ===\n");
	int *result = (int*)malloc(sizeof(int));
	*result = a + b;
	return result;
}

void* multiplication(void* arg)
{
	printf("\n=== Inside Thread 2  ===\n");
	int *result = (int*)malloc(sizeof(int));
	*result = a * b;
	return result;
}

int main ()
{
	printf("Enter the value of 'a': ");
	scanf("%d", &a);
	printf("\nEnter the value of 'b': ");
	scanf("%d", &b);
	
	pthread_t t1, t2, t3, t4;
	
	pthread_create(&t1, NULL, addition, NULL);
	void* res;
	pthread_join(t1, &res);
	printf("\nThe addition answer is: %d\n", *((int*)res));
	
	pthread_create(&t2, NULL, multiplication, NULL);
	pthread_join(t2, &res);
	printf("\nThe multiplication answer is: %d\n", *((int*)res));
	
	free(res);
	return 0;
}
