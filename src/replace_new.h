#ifndef __new_replace_h
#define __new_replace_h

#include <stddef.h>

typedef void *(* allocate_func_ptr)(size_t);
typedef void (* deallocate_func_ptr)(void *);

extern "C" {

allocate_func_ptr set_global_allocate_func(allocate_func_ptr allocate_func);
allocate_func_ptr get_global_allocate_func();

deallocate_func_ptr set_global_deallocate_func(deallocate_func_ptr deallocate_func);
deallocate_func_ptr get_global_deallocate_func();

}   // extern "C"

#endif
