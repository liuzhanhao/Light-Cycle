#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "simpl.h"
#include "message.h"

int main(int argc, char* argv[]) {
    int fd;
    MESSAGE msg, reply;
    char name[] = "Worker?";

    srand(time(NULL));

    /* Use the argument to create a 'unique' name */
    if (argc > 1) {
        name[6] = argv[1][0];
    }

    if (name_attach(name, NULL) == -1) {
        fprintf(stderr, "Cannot attach name!\n");
        exit(0);
    }

    /* Locate Admin who is the host of the game */
    if ((fd = name_locate("Admin")) == -1) {
        fprintf(stderr, "Cannot locate name!\n");
        exit(0);
    }

    /* Initial bound
     * - may not be the current bounds in Admin
     * - just pick a number from the bounds as starting point
     */
    reply.lowerBound = 0;
    reply.upperBound = 99;
    while (reply.lowerBound < reply.upperBound) {
        sleep(1);
        
        /* Randomly pick a number from the bounds */
        msg.guess = reply.lowerBound +
                        rand() % (reply.upperBound - reply.lowerBound + 1);
        printf("Guessing %d\n", msg.guess);
        /* The bounds in 'reply' will be updated */
        // fd = name_locate("Admin")) defined below
        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message!\n");
            exit(0);
        }
    }

    /* Only winner can reach this point... */
    printf("I win!\n");

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
