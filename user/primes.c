#include "kernel/types.h"
#include "user/user.h"

void
proc(int *p) {
    if (fork() == 0) {
        // child
        close(p[1]);
        int left;
        int prime;
        int ret = read(p[0], &prime, sizeof(int));
        if (ret == 0) {
            // no more primes
            close(p[0]);
            exit(0);
        }
        fprintf(1, "prime %d \n", prime);
        int rpipe[2] = {0, 0};
        while (read(p[0], &left, sizeof(int)) > 0) {
            if ((left % prime) != 0) {
                // create a new pipe
                if (rpipe[0] == 0) {
                    pipe(rpipe);
                    // fork a new process
                    proc(rpipe);
                    // ! do NOT close rpipe[0] before fork child process, or else child process cannot read from it
                    // father process
                    close(rpipe[0]);
                }
                write(rpipe[1], &left, sizeof(int));
            }
        }
        if (rpipe[1] > 0) {
            close(rpipe[1]);
        }
        wait(0);
        exit(0);
    }
}

int
main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++) {
        write(p[1], &i, sizeof(int));
    }  
    proc(p);
    close(p[1]);
    // ! do not close p[0] before call proc
    close(p[0]);
    wait(0);
    exit(0);
}

