#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("ERROR; usage: <%s, virt_adr_space_in_MB, page_size_in_KB, virt_adress>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// extract the data in proper way: 
	long size_of_vas_MB = atol(argv[1]);
	long page_size_KB = atol(argv[2]);
	long va = atol(argv[3]);
	
	// convert into bytes
	long virt_adr_space_in_bytes = size_of_vas_MB * 1024 * 1024; // 1 MB = 2^20 B => 2^10 * 2^10
	long page_size_in_bytes = page_size_KB * 1024;
	
	// using Virtual Address Space: compute page table size (no. of pages)
	long no_of_pages = virt_adr_space_in_bytes / page_size_in_bytes;
	
	// array[page virtual] = frame (physical)
	int page_table[no_of_pages];
	
	// initializing the values for page table: array[i] = i
	for (int i = 0; i < no_of_pages; i++)
		page_table[i] = i;
	
	// calculate the (req) page number + offset
	long page_number = va / page_size_in_bytes;
	long offset = va % page_size_in_bytes;
	
	if (page_number >= no_of_pages) // miss
		printf("Page Table miss..\n");
	else
	{		
		int frame_number = page_table[page_number];
		printf("Page Table Hit: \n<frame number, offset> = <%d, %ld>\n", frame_number, offset);
	}		
	return 0;
}
