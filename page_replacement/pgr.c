#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void fifo(int* ref, int length, int n_frame)
{
	int frame[n_frame];
	for (int i = 0; i < n_frame; i++)
		frame[i] = -1;
	
}

int main (int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Usage: <%s, length of reference string, no. of frames>\n", argv[0]);
		return 1;
	}
	int length = atoi(argv[1]);
	int n_frames = atoi(argv[2]);
	
	int page_request[length];
	
	printf("The refernce string is: \n[");
	srand(time(NULL));
	sleep(1);
	for (int i = 0; i < length; i++)
	{
		page_request[i] = rand() % 10;
		if (i == length - 1)
			printf("%d]\n", page_request[i]);
		else
			printf("%d, ", page_request[i]);
	}
	
		
	
	return 0;
}
