#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"

COORDINATE generate_pos(int nCycle){
    COORDINATE pos;
    if (nCycle == 0){
        pos.x = MAX_WIDTH * 0.35f; 
        pos.y = MAX_HEIGHT / 2;
    }
    else if (nCycle == 1){
        pos.x = MAX_WIDTH * 0.65f; 
        pos.y = MAX_HEIGHT / 2;
    }
    else
        printf("generate_pos error!\n");
    return pos;
}


void generate_wall(ARENA arena){
    // to do
}


void move(ARENA arena, int cycleId, DIRECTION dir, BOOST boost){
    // to do
}



int main(int argc, char* argv[]) {

    char *fromWhom = NULL;
    char *timer_pt = NULL;
    char *cycle_pt[2] = {NULL, NULL};
    char *courier_pt = NULL;
    ARENA arena;
    MESSAGE msg, reply;
    //MESSAGE fifo[20];
    //int fifo_size = 0, fi = 0;
    int nCycle = 0, timer_flag = 0, courier_flag = 0;
    int cycle_ready[2] = {0, 0}, timer_ready = 0, courier_ready = 0;

    if (name_attach("Game_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in game_admin.c!\n");
        exit(0);
    }


    //int flag = 0;
    while (1){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in game_admin.c!\n");
            exit(0);
        }

        if (msg.type == REGISTER_CYCLE){
            if (nCycle < 2){
                arena.cycle[nCycle].pos = generate_pos(nCycle);

                reply.cycleId = nCycle;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                nCycle++;
            }
            else{
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
        }

        if (msg.type == REGISTER_TIMER){
            if (timer_flag){
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            else{
                timer_pt = fromWhom;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
        }


        if (msg.type == REGISTER_COURIER){
            if (courier_flag){
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            else{
                courier_pt = fromWhom;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
        }


        if (msg.type == REGISTER_HUMAN){
            if (nCycle < 2){
                arena.cycle[nCycle].pos = generate_pos(nCycle);
                reply.humanId = nCycle;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                nCycle++;
            }
            else{
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
        }


        if (msg.type == CYCLE_READY){
            cycle_pt[msg.cycleId] = fromWhom;
            cycle_ready[msg.cycleId] = 1;

            if (cycle_ready[0] && cycle_ready[1])
            {
                generate_wall(arena); // to do
                reply.arena = arena;
                reply.type = START;
                if (Reply(cycle_pt[0], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }

                if (Reply(cycle_pt[1], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            //else, let the cycle wait
        }


        if (msg.type == TIMER_READY){
            timer_ready = 1;
            timer_pt = fromWhom;
        }


        if (msg.type == COURIER_READY){
            courier_pt = fromWhom;
            courier_ready = 1;
        }


        if (msg.type == HUMAN_READY){
            cycle_pt[msg.humanId] = fromWhom;
            cycle_ready[msg.humanId] = 1;

            if (cycle_ready[0] && cycle_ready[1])
            {
                generate_wall(arena); // to do
                reply.arena = arena;
                reply.type = START;
                if (Reply(cycle_pt[0], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }

                if (Reply(cycle_pt[1], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            //else, let the human wait
        }


        if (msg.type == OKAY){
            //courier finish display_arena
        }

        // cycle move
        if (msg.type == MOVE){
            move(arena, msg.cycleId, msg.dir, msg.boost);

            reply.type = UPDATE;
            reply.arena = arena;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
        }


        // human move
        if (msg.type == HUMAN_MOVE){
            move(arena, msg.humanId, msg.dir, msg.boost);

            reply.type = UPDATE;
            reply.humanId = msg.humanId;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
        }




        
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
