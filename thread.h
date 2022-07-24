typedef unsigned int uint;
typedef uint lock_t;

int thread_create(void*(*start_routine)(void*), void* arg);
int thread_join();
void lock_init(uint* lock);
void lock_acquire(uint* lock);
void lock_release(uint* lock);