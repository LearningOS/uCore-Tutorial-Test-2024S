#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

#define SYS_sbrk 300


int main()
{
	printf("Test sbrk start.\n");
	uint64 PAGE_SIZE = 0x1000;
	uint64 origin_brk = sbrk(0);
	printf("origin break point = %p\n", origin_brk);
	uint64 brk = sbrk(PAGE_SIZE);
	if(brk != origin_brk){
		return -1;
	}
	brk = sbrk(0);
	printf("one page allocated, break point = %p\n", brk);
	printf("try write to allocated page\n");
	char *new_page = (char *)origin_brk;
	for(uint64 i = 0;i < PAGE_SIZE;i ++) {
		new_page[i] = 1;
	}
	printf("write ok\n");
	sbrk(PAGE_SIZE * 10);
	brk = sbrk(0);
	printf("10 page allocated, break point = %p\n", brk);
	sbrk(PAGE_SIZE * -11);
	brk = sbrk(0);
	printf("11 page DEALLOCATED, break point = %p\n", brk);
	printf("try DEALLOCATED more one page, should be failed.\n");
	uint64 ret = sbrk(PAGE_SIZE * -1);
	if(ret != -1){
		printf("Test sbrk failed!\n");
		return -1;
	}
	printf("Test sbrk almost OK!\n");
	printf("now write to deallocated page, should cause page fault.\n");
	for(uint64 i = 0;i < PAGE_SIZE;i ++){
		new_page[i] = 2;
	}
	return 0;
}
