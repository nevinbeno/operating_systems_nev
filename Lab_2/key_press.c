#include <stdio.h>
#include <unistd.h>

int main ()
{
	printf("Press enter key\n");
	fflush(stdout);
	sleep(10);
	getchar();
	sleep(10);
	return 0;
}
