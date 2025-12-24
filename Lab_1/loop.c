#include <stdio.h>
#include <unistd.h>
int main ()
{
	while(1)
	{
		printf("Running...\n");
		fflush(stdout); // make it to line buffer mode
		sleep(5);
	}
	return 0;
}
