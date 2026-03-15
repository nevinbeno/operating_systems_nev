#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int value;

void* squarer(void* arg)
{
	printf("== Inside thread 1 == \n");
	int* result = (int*)malloc(sizeof(int));
	*result = value * value;
	return result;
}

void* cuber(void* arg)
{
	printf("== Inside thread 2 ==\n");
	int* result = (int*)malloc(sizeof(int));
	*result = value*value*value;
	return result;
}

int main ()
{
	printf("Enter a value: ");
	scanf("%d", &value);
	printf("\n");
	
	pthread_t t1, t2;
	
	void* res;
	
	pthread_create(&t1, NULL, squarer, NULL);
	pthread_create(&t2, NULL, cuber, NULL);
	
	//printf("Value returned by thread 1: square(%d) = %d\n", value, *(int*)res);
	
//	pthread_create(&t2, NULL, cuber, NULL);	
	pthread_join(t1, &res);
	printf("Value returned by thread 1: square(%d) = %d\n", value, *(int*)res);
	free(res);
	
	pthread_join(t2, &res);
	printf("Value returned by thread 2: cube(%d) = %d\n", value, *(int*)res);
	
	free(res);
	return 0;
}
