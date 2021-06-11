#include "kernel/types.h"
#include "user/user.h"

void
proc(int *p) {
    if (fork() == 0) {
        // child
        close(p[1]);
        int left;
        while (read(p[0], &left, 4) > 0) {
            fprintf(1, "number %d \n", left);
        }
        exit(0);
    } else {
        close(p[1]);
        wait(0);
    }
    close(p[0]);
}

int
main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    for (int i = 2; i < 36; i++) {
        write(p[1], &i, 4);
    }  
    proc(p);
    exit(0);
}

