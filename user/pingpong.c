#include "kernel/types.h"
#include "user/user.h"

/**
 * 
 * father -> p1[0, 1] -> child
 * child -> p2[0, 1] -> father
*/

int
main(int argc, char *argv[]) {

    int p1[2];
    int p2[2];
    char *buf[10];
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        // child process
        close(p1[0]);
        close(p2[1]);
        read(p1[1], buf, 1);
        close(p1[1]);
        fprintf(1, "%d: received ping\n", getpid());
        write(p2[0], "p", 1);
        close(p2[0]);
    } else {
        // father process
        close(p1[1]);
        close(p2[0]);
        write(p1[0], "p",  1);
        close(p1[0]);
        wait(0);
        read(p2[1], buf, 1);
        close(p2[1]);
        fprintf(1, "%d: received pong\n", getpid());
    }
    exit(0);
}