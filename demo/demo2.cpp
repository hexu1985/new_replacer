#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "replace_new.h"

using namespace std;

char *gPool = NULL;

void my_new_handler();

void *my_allocate_func(size_t size) 
{
	printf("my operator new\n");
    return malloc(size);
}

void my_deallocate_func(void *p)
{
	printf("my operator delete\n");
	return free(p);
}

int main()
{
    allocate_func_ptr old_allocate_func = set_global_allocate_func(my_allocate_func);
    deallocate_func_ptr old_deallocate_func = set_global_deallocate_func(my_deallocate_func);
    new_handler old_new_handler = set_new_handler(my_new_handler);

	gPool = new char[100*1024*1024];
	if (gPool != NULL) {
		printf("Preserve 100MB memory at %x.\n", gPool);
	}

	char *p = NULL;
	for (int i = 0; i < 40; i++) {
		p = new char[100*1024*1024];
		memset(p, 0, 100*1024*1024);
		printf("%d * 100M, p = %x\n", i+1, p);
	}

	printf("Done.\n");

    set_global_allocate_func(old_allocate_func);
    set_global_deallocate_func(old_deallocate_func); 
    set_new_handler(old_new_handler);

	return 0;
}

void my_new_handler()
{
	if (gPool != NULL) {
		printf("try to get more memory ...\n");
		delete [] gPool;
		gPool = NULL;
		return;
	} else {
		printf("I can not help ...\n");
		throw bad_alloc();
	}
	return;
}
