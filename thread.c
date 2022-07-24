#include "types.h"
#include "user.h"
#include "mmu.h"
#include "x86.h"

int thread_create(void*(*start_routine)(void*), void* arg)
{
    void* newstack = malloc(PGSIZE);
    if((uint)newstack <= 0){
        printf(2, "Stack allocation to thread using malloc failed in thread_create()!\n");
        return -1;
    }
    int cid = clone(newstack, PGSIZE);
    if (cid == 0){
        (*start_routine)(arg);
        free(newstack);
        exit();
    }
    else{
        return cid;
    }
}

int thread_join()
{
    return join();
}

void lock_init(uint* lock)
{
    xchg(lock, 0);
}

void lock_acquire(uint* lock)
{
    while (xchg(lock, 1) == 1);
}

void lock_release(uint* lock)
{
    xchg(lock, 0);
}