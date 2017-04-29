#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <time.h>
#include <unistd.h>
#include "simpl.h"
#include <stdbool.h>
#include "message.h"

int cycleId;
ARENA arena;
CYCLE mycycle, oppocycle;
DIRECTION dir;

// check if dir is reachable for mycycle
bool check(DIRECTION dir)
{
    if (dir == EAST)
        return arena.wall[mycycle.pos.x+1][mycycle.pos.y] == NONE && !((mycycle.pos.x+1 == oppocycle.pos.x) && (mycycle.pos.y == oppocycle.pos.y));
    else if (dir == SOUTH)
        return arena.wall[mycycle.pos.x][mycycle.pos.y+1] == NONE && !((mycycle.pos.x == oppocycle.pos.x) && (mycycle.pos.y+1 == oppocycle.pos.y));
    else if (dir == WEST)
        return arena.wall[mycycle.pos.x-1][mycycle.pos.y] == NONE && !((mycycle.pos.x-1 == oppocycle.pos.x) && (mycycle.pos.y == oppocycle.pos.y));
    else if (dir == NORTH)
        return arena.wall[mycycle.pos.x][mycycle.pos.y-1] == NONE && !((mycycle.pos.x == oppocycle.pos.x) && (mycycle.pos.y-1 == oppocycle.pos.y));
    return false;
}


int main(int argc, char* argv[]) {
    int fd;
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

    msg.type = CYCLE_READY;
    msg.cycleId = cycleId;
    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send CYCLE_READY message!\n");
        }

    while (reply.type != END)
    {
        if (reply.type == START)
        {
            //fprintf(stderr, "Dont know what to start!\n");
            //sleep(1);
            arena = reply.arena;
            mycycle = arena.cycle[cycleId];
            oppocycle = arena.cycle[1 - cycleId];
        }
        
        else if (reply.type == UPDATE)
        {
            //fprintf(stderr, "Dont know what to update!\n");
            arena = reply.arena;
            mycycle = arena.cycle[cycleId];
            oppocycle = arena.cycle[1 - cycleId];
            //sleep(1);
        }

        // MOVE
        if (check(mycycle.dir))
            dir = mycycle.dir;
        else
        {
            int i;
            for (i = 0; i < 4; i++)
                if (mycycle.dir != i && check(i))
                    break;

            if (i < 4)
                dir = i;
            else    
                dir = mycycle.dir;
        }
        msg.type = MOVE;
        msg.dir = dir;
        msg.cycleId = cycleId;
        msg.boost = NO;

        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot send MOVE message in cycle.c!\n");
            }
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach CYCLE name!\n");
        exit(0);
    }

    return 0;
}
