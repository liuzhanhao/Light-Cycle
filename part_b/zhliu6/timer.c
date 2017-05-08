/*
* CSCI3180 Principles of Programming Languages
*
* --- Declaration ---
*
* I declare that the assignment here submitted is original except for source
* material explicitly acknowledged. I also acknowledge that I am aware of
* University policy and regulations on honesty in academic work, and of the
* disciplinary guidelines and procedures applicable to breaches of such policy
* and regulations, as contained in the website
* http://www.cuhk.edu.hk/policy/academichonesty/
*
* Assignment 5A
* Name : Liu Zhan Hao
* Student ID : 1155092201
* Email Addr : zhliu6@cse.cuhk.edu.hk
*/

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
    char name[] = "Timer";

    srand(time(NULL));

    if (name_attach(name, NULL) == -1) {
        fprintf(stderr, "Cannot attach name in timer.c!\n");
        exit(0);
    }

    /* Locate Admin who is the host of the game */
    if ((fd = name_locate("Game_Admin")) == -1) {
        fprintf(stderr, "Cannot locate name in timer.c!\n");
        exit(0);
    }

    msg.type = REGISTER_TIMER;

    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send REGISTER_TIMER message!\n");
        }

    //if (reply.type == INIT)
        //fprintf(stderr, "Successfully register!\n");
    if (reply.type == FAIL)
    {
        fprintf(stderr, "Fail to register in timer.c!\n");
        exit(0);
    }


    while (reply.type != END)
    {
        msg.type = TIMER_READY;
        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot send TIMER_READY message!\n");
            }

        if (reply.type == SLEEP)
        {
            usleep(reply.interval);
        }
    }
    
    //printf("Timer end of use!\n");

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach TIMER name!\n");
        exit(0);
    }

    return 0;
}
