#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "simpl.h"
#include "message.h"


int main(int argc, char* argv[]) {
    int fd, cycleId;
    CYCLE c;
    MESSAGE msg, reply;

    char name[] = "Cycle ?";

    /* Use the argument to create a 'unique' name */
    if (argc > 1) {
        name[6] = argv[1][0];
    }

    if (name_attach(name, NULL) == -1) {
        fprintf(stderr, "Cannot attach name in cycle.c!\n");
        exit(0);
    }

    /* Locate Admin who is the host of the game */
    if ((fd = name_locate("Game_Admin")) == -1) {
        fprintf(stderr, "Cannot locate name in cycle.c!\n");
        exit(0);
    }

    msg.type = REGISTER_CYCLE;

    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in cycle.c!\n");
        }

    if (reply.type == INIT)
        cycleId = reply.cycleId;
    else if (reply.type == FAIL)
    {
        fprintf(stderr, "Fail to register in cycle.c!\n");
        exit(0);
    }

    while (reply.type != END)
    {
        msg.type = CYCLE_READY;
        msg.cycleId = cycleId;
        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot send CYCLE_READY message!\n");
            }

        if (reply.type == START)
        {
            fprintf(stderr, "Dont know what to start!\n");
            sleep(1);
            if (cycleId == 0)
            {
                c.pos.x = MAX_WIDTH * 0.35f;
                c.pos.y = MAX_HEIGHT / 2;
                c.dir = EAST;

                reply.arena.cycle[0] = c;
            }
            else if (cycleId == 1)
            {
                c.pos.x = MAX_WIDTH * 0.65f;
                c.pos.y = MAX_HEIGHT / 2;
                c.dir = WEST;
                
                reply.arena.cycle[1] = c;
            }
        }

        else if (reply.type == MOVE)
        {
            //fprintf(stderr, "Dont know what to move!\n");
            //sleep(1);
            if (reply.boost == YES)
                usleep(10000);
            else if (reply.boost == NO)
                usleep(50000);

            cycleId = reply.cycleId;
            c = reply.arena.cycle[cycleId];

            if (cycleId == 0)
                reply.arena.wall[reply.arena.cycle[cycleId].pos.x][reply.arena.cycle[cycleId].pos.y] = REDCYCLE;
            else if (cycleId == 1)
                reply.arena.wall[reply.arena.cycle[cycleId].pos.x][reply.arena.cycle[cycleId].pos.y] = GREENCYCLE;

            c.dir = reply.dir;
            if (c.dir == EAST)
                reply.arena.cycle[cycleId].pos.x = ++c.pos.x;
            else if (c.dir == SOUTH)
                reply.arena.cycle[cycleId].pos.y = ++c.pos.y;
            else if (c.dir == WEST)
                reply.arena.cycle[cycleId].pos.x = --c.pos.x;
            else if (c.dir == NORTH)
                reply.arena.cycle[cycleId].pos.y = --c.pos.y;

            reply.arena.cycle[cycleId].dir = c.dir;
        }

        else if (reply.type == UPDATE)
        {
            //fprintf(stderr, "Dont know what to update!\n");
            c.pos.x = reply.arena.cycle[cycleId].pos.x;
            c.pos.y = reply.arena.cycle[cycleId].pos.y;
            c.dir = reply.arena.cycle[cycleId].dir;
            //sleep(1);
        }
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach CYCLE name!\n");
        exit(0);
    }

    return 0;
}
