#include <stdio.h>
#include <sys/uio.h>
#include <asm/ptrace.h>
#include <elf.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int nGlobalVar = 0;
 
int tempFunction(int a, int b)
{
    printf("tempFunction is called, a = %d, b = %d \n", a, b);
    return (a + b);
}

int main()
{
    int n;
    n = 1;
    n++;
    n--;
 
    nGlobalVar += 100;
    nGlobalVar -= 12;
 
    printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);
 
    n = tempFunction(1, 2);
    printf("n = %d\n", n);
 
    return 0;
}
