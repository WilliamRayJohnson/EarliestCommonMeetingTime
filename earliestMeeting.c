/*
 * A concurrent program that solves the earliest common meeting time problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <float.h>

#define THREAD_CREATION_FAILED -1
#define THREAD_JOIN_FAILED -2

#define MAX_THREADS 100

typedef struct Input {
    double search_time;
    char *time_sets;
    int thread_id;
} th_arg_val;

typedef struct Output {
    bool val_found;
    double common_time;
} th_ret_val;

void *find_common_time(void *arg);

int main(int argc, char *argv[]) {
    if(argc>=2) {
        int i;
        double earliestCommonTime = DBL_MAX;
        FILE *mainFp;
        pthread_t *tid[MAX_THREADS];

        mainFp = fopen(argv[1], "r");
        fseek(mainFp, 0, SEEK_END);
        if (ftell(mainFp) != 0) {
            fseek(mainFp, 0, SEEK_SET);
            int setCount;
            fscanf(mainFp, "%d", &setCount);
            fgetc(mainFp);

            char c;
            c = fgetc(mainFp);
            if (c != '\n') {
                ungetc(c, mainFp);
                double d;
                int currTh = 0;
                do {
                    fscanf(mainFp, "%lf", &d);
                    th_arg_val *argVal = (th_arg_val *) malloc(sizeof(th_arg_val));
                    argVal->search_time = d;
                    argVal->time_sets = argv[1];
                    argVal->thread_id = currTh;
                    tid[currTh] = (pthread_t *) malloc(sizeof(pthread_t));
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
                        if (result->val_found && result->common_time <= earliestCommonTime)
                            earliestCommonTime = result->common_time;
                    }            
                }
            }
        }
        fclose(mainFp);
        if (earliestCommonTime != DBL_MAX) 
            printf("%lf\n", earliestCommonTime);
        else 
            printf("No common value exists.\n");
    }
    else 
        printf("Please provide a text file's name as an argument\n");

    exit(0);
}

void *find_common_time(void *arg) {
    double time;
    th_arg_val *input = (th_arg_val *) arg;
    time = input->search_time;

    FILE *fp;
    fp = fopen(input->time_sets, "r");
    int setAmount;
    fscanf(fp, "%d", &setAmount);
    fgetc(fp);

    double d;
    char c;
    int i = 1;
    bool lnTimeFound;
    bool commonTimeFound = true;
    while (i <= setAmount && commonTimeFound){
        lnTimeFound = false;
        c = fgetc(fp);
        if (c != '\n') {
            ungetc(c, fp);
            do {
                fscanf(fp, "%lf", &d);
                if (d == time)
                    lnTimeFound = true;
                fscanf(fp, "%c", &c);
            } while (c != '\n');
        }
        if (lnTimeFound) 
            commonTimeFound = true;
        else 
            commonTimeFound = false;
        i++;
    }
    fclose(fp);

    th_ret_val *retVal = (th_ret_val *) malloc(sizeof(th_ret_val));
    retVal->common_time = input->search_time;
    retVal->val_found = commonTimeFound;

    return ((void *) retVal);
}
