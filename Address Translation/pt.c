#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long vas; // MB
	long long ps; // KB
	long long va; // decimal
	
	printf("Enter Virtual Address Space in MB: ");
	scanf("%lld", &vas);
	printf("\nEnter Page Size in KB: ");
	scanf("%lld", &ps);
	printf("\nEnter the Virtual Address to translate (in decimal): ");
	scanf("%lld", &va);
	
	vas = vas* 1024*1024;
	ps = ps * 1024;
	
	long long n_pg = vas / ps;
	
	long long pg_no = va / ps;
	long long offset = va % ps;
	
	if (pg_no >= n_pg)
	{
		printf("\nPage miss!\n");
		return 1;
	}
	long long page_table[n_pg];
	for (long long i = 0; i < n_pg; i++)
		page_table[i] = i;
	printf("Page Table hit: \n");
	printf("<frame, offfset>: <%lld, %lld>\n", page_table[pg_no], offset);

	return 0;
}
