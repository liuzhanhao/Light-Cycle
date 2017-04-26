#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"

int main(int argc, char* argv[]) {
    int target, lowerBound, upperBound;
    char *fromWhom = NULL;
    MESSAGE msg, reply;

    /* Randomly pick a target number */
    srand(time(NULL));
    target = rand() % 100;
    printf("Target is %d.\n", target);

    /* Initial bounds */
    lowerBound = 0;
    upperBound = 99;
    printf("Bounds = [%d, %d]\n", lowerBound, upperBound);

    if (name_attach("Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name!\n");
        exit(0);
    }

    while (lowerBound < upperBound) {
        /* Receive a guess from a worker */
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message!\n");
            exit(0);
        }

        /* Adjust the bounds
         * When guess == target, then lowerBound == upperBound
         * */
        if (msg.guess >= lowerBound && msg.guess <= upperBound) {
            if (msg.guess == target) {
                upperBound = target;
                lowerBound = target;
            } else if (msg.guess > target) {
                upperBound = msg.guess - 1;
            } else if (msg.guess < target) {
                lowerBound = msg.guess + 1;
            }
            printf("Bounds = [%d, %d]\n", lowerBound, upperBound);
        }

        /* Return an updated bounds to that worker */
        reply.lowerBound = lowerBound;
        reply.upperBound = upperBound;
        if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot reply message!\n");
            exit(0);
        }
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
