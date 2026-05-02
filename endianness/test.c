#include <stdio.h>
int main ()
{
    int x = 0x12345678;
    printf("%d\n", x);

    printf("hexa equivalent: %x\n", x);
    printf("The address of variabkle x is: %p", (void*)&x);
    
    return 0;
}