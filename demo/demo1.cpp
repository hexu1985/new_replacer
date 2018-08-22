#include <stdlib.h>
#include <stdio.h>
#include "replace_new.h"

using namespace std;

char *gPool = NULL;

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

	gPool = new char[100*1024*1024];
	delete [] gPool;

	printf("Done.\n");

    set_global_allocate_func(old_allocate_func);
    set_global_deallocate_func(old_deallocate_func); 

	return 0;
}

