#include "thread.h"
#include "types.h"

lock_t lock;

void* sum_thread(void* arg)
{
    int* sum = (int *)arg;
    int i;
    for (i = 0; i < 100; i++)
    {
        lock_acquire(&lock);
        *sum += 1;
        lock_release(&lock);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int sum = 0;
    lock_init(&lock);
    int i;
    for (i = 0; i < 10; i++)
    {
        void *arg = (void *)&sum;
        thread_create(*sum_thread, arg);
    }
    for (i = 0; i < 10; i++)
    {
        thread_join();
    }
    printf(2, "sum = %d\n", sum);
    exit();
}