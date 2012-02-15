#include "unistd.h"
#include "string.h"
#include "sys/syscall.h"

int main(void)
{
    int i = 0;
    if (syscall(SYS_fork)) {
        while (1) {
            syscall(SYS_write, 1, "parent\n", 7);
            syscall(SYS_yield);

            if (i++ >= 10) {
                char *msg = "parent doing nothing\n";
                syscall(SYS_write, 1, msg, strlen(msg));
                syscall(SYS_wait);
                syscall(SYS_write, 1, "done waiting\n", 13);

                while (1) {
                }
            }
        }
    } else {
        while (1) {
            syscall(SYS_write, 1, "child\n", 6);
            syscall(SYS_yield);

            if (i++ >= 7) {
                syscall(SYS_write, 1, "child exiting\n", 14);
                /*syscall(SYS_exit, 0);*/
                return 0;
            }
        }
    }

    return 0;
}
