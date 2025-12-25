#include <stdio.h>
#include <unistd.h>

int main ()
{
	FILE *f = fopen("straceTest.txt", "w");
	fprintf(f, "Hello OS Lab\n");
	fclose(f);
	return 0;
}
