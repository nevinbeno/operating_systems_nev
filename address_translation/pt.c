#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Usage: \n");
		printf("Program exiting..");
		return 1;
	}
	
	int s_va_mb = atoi(argv[1]);
	int s_pg_kb = atoi(argv[2]);
	int va = strtol(argv[3], NULL, 0);
	
	long s_va_b = (long)s_va_mb*1024*1024;
	long s_pg_b = (long)s_pg_kb*1024;
	
	int n_pages = s_va_b / s_pg_b;
	
	int pt[n_pages];
	for (int i = 0; i < n_pages; i++)
		pt[i] = i + 10;
	
	int pg_of_va = va / s_pg_b;
	int offset = va % s_pg_b;
	
	if (pg_of_va < n_pages)
	{
		printf("PA for VA %d is <frame, offset>: <%d, %d>\n", va, pt[pg_of_va], offset);
		long pa = pt[pg_of_va] * s_pg_b + offset;
		printf("PA: %ld\n", pa);
		printf("PA (hex): 0x%lx\n", pa);
	}
	else
		printf("PT miss!\n");
	return 0;
}
