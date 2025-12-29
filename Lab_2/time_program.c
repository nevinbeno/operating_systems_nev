#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main ()
{
	time_t t;
	time(&t);
	printf("Current time is: %s\n", ctime(&t));
	sleep(10);
	return 0;
}
