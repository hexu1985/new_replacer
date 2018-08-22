#include "replace_new.h"
#include <stdlib.h>
#include <new>

namespace {

void *std_allocate_func(size_t size) 
{
	void *pReturn = NULL;
	if (size == 0)
		size =1;	// 至少分配1字节

	while (1) {
		pReturn = malloc(size);
		if (pReturn != NULL) {
			return pReturn;
		}

        std::new_handler globalhandler = std::get_new_handler();	// 找到新的new_handler

		if (globalhandler) {
			(*globalhandler)();	// 如果内存不足了, 就调用new_handler
		} else {
			return NULL;
		}
	}
}

void std_deallocate_func(void *ptr)
{
    if (ptr == NULL)
        return;
    free(ptr);
}

allocate_func_ptr global_allocate_func = &std_allocate_func;
deallocate_func_ptr global_deallocate_func = &std_deallocate_func; 

}   // namespace

allocate_func_ptr set_global_allocate_func(allocate_func_ptr allocate_func)
{
    allocate_func_ptr old_allocate_func = global_allocate_func; 
    global_allocate_func = allocate_func;
    return old_allocate_func; 
}

allocate_func_ptr get_global_allocate_func()
{
    return global_allocate_func; 
}

deallocate_func_ptr set_global_deallocate_func(deallocate_func_ptr deallocate_func)
{
    deallocate_func_ptr old_deallocate_func = global_deallocate_func; 
    global_deallocate_func = deallocate_func;
    return old_deallocate_func; 
}

deallocate_func_ptr get_global_deallocate_func()
{
    return global_deallocate_func; 
}

