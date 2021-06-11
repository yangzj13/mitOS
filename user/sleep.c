//
// Created by Smile on 2021/6/11.
//
#include "kernel/types.h"

#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(1, "Usage: sleep ticks\n");
        exit(1);
    }

    int d = atoi(argv[1]);
    sleep(d);
    exit(0);
}