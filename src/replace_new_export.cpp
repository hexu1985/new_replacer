#include "replace_new.h"
#include <new>

void *operator new(std::size_t size)
{
    allocate_func_ptr allocate_func = get_global_allocate_func();
    void *ptr = allocate_func(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new(std::size_t size, const std::nothrow_t& tag)
{
    allocate_func_ptr allocate_func = get_global_allocate_func();
    void *ptr = allocate_func(size);
    return ptr;
}

void *operator new[](std::size_t size)
{
    allocate_func_ptr allocate_func = get_global_allocate_func();
    void *ptr = allocate_func(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new[](std::size_t size, const std::nothrow_t& tag)
{
    allocate_func_ptr allocate_func = get_global_allocate_func();
    void *ptr = allocate_func(size);
    return ptr;
}

void operator delete(void* ptr)
{
    deallocate_func_ptr deallocate_func = get_global_deallocate_func();
    deallocate_func(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag)
{
    deallocate_func_ptr deallocate_func = get_global_deallocate_func();
    deallocate_func(ptr);
}

void operator delete [](void* ptr)
{
    deallocate_func_ptr deallocate_func = get_global_deallocate_func();
    deallocate_func(ptr);
}

void operator delete [](void* ptr, const std::nothrow_t& tag)
{
    deallocate_func_ptr deallocate_func = get_global_deallocate_func();
    deallocate_func(ptr);
}
