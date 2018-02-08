/*
 * A concurrent program that solves the earliest common meeting time problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define THREAD_CREATION_FAILED -1
#define THREAD_JOIN_FAILED -2

typedef struct Input {
    double search_time;
    double *time_sets;
} th_arg_val;

typedef struct Output {
    bool val_found = false;
    double common_time;
} th_ret_val;

void *find_common_time(void *arg);

int main() {

    exit(0);
}

void *find_common_time(void *arg) {

    return (NULL);
}
