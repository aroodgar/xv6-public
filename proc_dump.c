#include "types.h"
#include "user.h"
#include "proc_info.h"
#include "param.h"

// a program for testing
// int proc_dump(struct proc_info*, int n)
// functionality


// if not testing, a correct program wouldn't have the part creating the processes.
// it would only consist of the first if checking the number of arguments and a call
// to the call_proc_dump() method.

struct local_info{
    int a;
    char c;
    float f;
};

void call_proc_dump();

int
main(int argc, char **argv)
{
    int i;
    if (argc > 1){
        printf(2, "Error! proc_dump takes (0) arguments, but was passed %d!\n", argc);
        exit();
    }
    int main_pid = getpid();
    struct local_info* li = 0;
    for (i = 0; i < 4; i++)
    {
        if (main_pid == getpid())
        {
            int pid = fork();
            if (pid == 0){
                li = (struct local_info*)(malloc((i + 1) * sizeof(struct local_info)));
                int j;
                for (j = 0; j < i + 1; j++)
                {
                    li[i].a = i * 64;
                    li[i].c = 96 + i;
                    li[i].f = 64.00 + i * 0.1;
                }
            }
        }
    } 

    if (getpid() == main_pid)
    {
        call_proc_dump();
    }
    else
    {
        // to kill time so the process would run for some time more than a blink of an eye... :)
        for (i = 0; i < 1000000; i++)
        {
            printf(2, "");
        }
    }

    if (getpid() == main_pid){
        int wpid;
        while ((wpid = wait()) >= 0);
    }

    exit();
}

// should only be called in the main process
void
call_proc_dump()
{
    int i;
    struct proc_info* procs_info = (struct proc_info*)(malloc(NPROC * sizeof(struct proc_info)));
    int cnt = proc_dump(procs_info, NPROC);
    if (cnt < 0){
        printf(2, "Error! Something went wrong while calling proc_dump system call...\n");
        exit();
    }
    printf(2, "A total of %d process(es) found with RUNNABLE/RUNNING state.\n", cnt);
    printf(2, "PID\tMEMSIZE\n");
    for (i = 0; i < cnt; i++)
    {
        printf(2, "%d\t%d\n", procs_info[i].pid, procs_info[i].memsize);
    }
}