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
    char *time_sets;
} th_arg_val;

typedef struct Output {
    bool val_found;
    double common_time;
} th_ret_val;

void *find_common_time(void *arg);

int main(int argc, char *argv[]) {
    if(argc==2) {
        int i;
        FILE *mainFp;
        pthread_t *tid[MAX_THREADS];
        for (i = 0; i < MAX_THREADS; i++)
            tid[i] = (pthread_t *) malloc(sizeof(pthread_t));

        mainFp = fopen(argv[1], "r");
        int setCount;
        fscanf(mainFp, "%d", &setCount);
        fgetc(mainFp);

        double d;
        char c;
        int currTh = 0;
        do {
            fscanf(mainFp, "%lf", &d);
            th_arg_val *argVal = (th_arg_val *) malloc(sizeof(th_arg_val));
            argVal->search_time = d;
            argVal->time_sets = argv[1];
            if (pthread_create (tid[currTh], NULL, find_common_time, 
                        (void *) argVal)) {
                fprintf(stderr, "Error creating thread %d", currTh);
                exit(THREAD_CREATION_FAILED);
            } 
            currTh++;
            fscanf(mainFp, "%c", &c);
        } while(c != '\n');

        void **retVal = (void **) malloc(sizeof(void *));
        for (i = 0; i < currTh; i++) {
            if (pthread_join (*tid[i], retVal)) {
                fprintf(stderr, "Error joining thread %d", i);
                exit(THREAD_JOIN_FAILED);
            }
            else {
                th_ret_val *result = (th_ret_val *) *retVal;
                printf("The time, %lf, was found to be: i\n", result->common_time);

            }            
        }

        fclose(mainFp);
    }
    else {
        printf("Please provide a text file's name as an argument\n");
    }

    exit(0);
}

void *find_common_time(void *arg) {
    double time;
    char *file;
    th_arg_val *input = (th_arg_val *) arg;
    printf("Thread with %lf sees file %s\n", input->search_time, input->time_sets);

    th_ret_val *retVal = (th_ret_val *) malloc(sizeof(th_ret_val));
    retVal->common_time = input->search_time;

    return ((void *) retVal);
}
