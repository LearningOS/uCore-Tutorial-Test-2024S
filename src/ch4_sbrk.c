#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>


const int WIDTH = 10;
const int HEIGHT = 5;

/*
理想结果：
*/

int main()
{
	void *pret;

    pret = sbrk(0);
    printf ("heap start: %p\n", pret);
	puts("Test sbrk OK!");
	return 0;
}