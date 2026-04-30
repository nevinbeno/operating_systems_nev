#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int x;
    printf("Enter a value: ");
    scanf("%d", &x);
    printf("The hexadcimal version of %d: 0x%08x\n", x, x); 

    char *c = (char*)&x;
    printf("The Least Significant Byte of the %d is %d\n", x, (int)*c);
    printf("The address of variable x: %p\n", (void*)&x);
    printf("Sizeof int: %zu Bytes\n", sizeof(int));

    return 0;
}