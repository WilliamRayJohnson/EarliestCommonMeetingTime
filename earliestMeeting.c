/*
 * A concurrent program that solves the earliest common meeting time problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define THREAD_CREATION_FAILED -1
#define THREAD_JOIN_FAILED -2

#define MAX_THREADS 100

typedef struct Input {
    double search_time;
    FILE *time_sets;
} th_arg_val;

typedef struct Output {
    bool val_found;
    double common_time;
} th_ret_val;

void *find_common_time(void *arg);

int main(int argc, char *argv[]) {
    if(argc==2) {
        int i;
        FILE *fps[MAX_THREADS + 1];
        pthread_t *tid[MAX_THREADS];
        for (i = 0; i < MAX_THREADS; i++)
            tid[i] = (pthread_t *) malloc(sizeof(pthread_t));
        
        fps[0] = fopen(argv[1], "r");
        int setCount;
        fscanf(fps[0], "%d", &setCount);
        fgetc(fps[0]);

        double d;
        char c;
        do {
            fscanf(fps[0], "%lf", &d);
            printf("%lf\n", d);
            fscanf(fps[0], "%c", &c);
        } while(c != '\n');

        fclose(fps[0]);
    }
    else {
        printf("Please provide a text file's name as an argument\n");
    }
    
    exit(0);
}

void *find_common_time(void *arg) {

    return (NULL);
}
