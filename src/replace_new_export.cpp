#include "replace_new.h"
#include <new>

void *operator new(std::size_t size)
{
    void *ptr = operator_new_universal(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new(std::size_t size, const std::nothrow_t& tag)
{
    void *ptr = operator_new_universal(size);
    return ptr;
}

void *operator new[](std::size_t size)
{
    void *ptr = operator_new_universal(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new[](std::size_t size, const std::nothrow_t& tag)
{
    void *ptr = operator_new_universal(size);
    return ptr;
}

void operator delete(void* ptr)
{
    operator_delete_universal(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag)
{
    operator_delete_universal(ptr);
}

void operator delete [](void* ptr)
{
    operator_delete_universal(ptr);
}

void operator delete [](void* ptr, const std::nothrow_t& tag)
{
    operator_delete_universal(ptr);
}
