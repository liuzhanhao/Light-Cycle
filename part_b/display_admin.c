#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"


int main(int argc, char* argv[]) {

    char *fromWhom = NULL;
    MESSAGE msg, reply;

    if (name_attach("Display_Admin", NULL) == -1) {
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
