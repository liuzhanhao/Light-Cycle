#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"

// fifo used to store the move msg and the cycle's address
typedef struct { 
    MESSAGE msg;
    char *fromWhom;
    int id;
    int human_flag;
} MOVE_MSG;

char *fromWhom = NULL;
char *timer_pt = NULL;
char *cycle_pt[2] = {NULL, NULL};
char *courier_pt[3] = {NULL, NULL, NULL};
ARENA arena;
MESSAGE msg, reply, msg_temp;
MOVE_MSG fifo_move[20];
int fifo_move_size = 0, fi_move = 0;
int nCycle = 0, timer_flag = 0, courier2_flag = 0;
int cycle_ready[2] = {0, 0}, timer_ready = 0, courier2_ready = 0;


COORDINATE generate_pos(int nCycle){
    COORDINATE pos;
    if (nCycle == 0){
        pos.x = MAX_WIDTH * 0.30f; 
        pos.y = MAX_HEIGHT / 2;
    }
    else if (nCycle == 1){
        pos.x = MAX_WIDTH * 0.70f; 
        pos.y = MAX_HEIGHT / 2;
    }
    else
        printf("generate_pos error!\n");
    return pos;
}


void generate_wall(){
    int i, j;
    for(i = 0; i < MAX_WIDTH; i++)
        for (j = 0; j < MAX_HEIGHT; j++)
        {
            if (i == 0 || j == 0 || i == MAX_WIDTH-1 || j == MAX_HEIGHT-1)
                arena.wall[i][j] = BOUNDARY;
            else
                arena.wall[i][j] = NONE;
        }
}


int check_end(){
    return arena.wall[arena.cycle[0].pos.x][arena.cycle[0].pos.y] != NONE || arena.wall[arena.cycle[1].pos.x][arena.cycle[1].pos.y] != NONE || (arena.cycle[0].pos.x == arena.cycle[1].pos.x && arena.cycle[0].pos.y == arena.cycle[1].pos.y);
}


void move(int cycleId, DIRECTION dir){

    COORDINATE pos;
    pos.x = arena.cycle[cycleId].pos.x;
    pos.y = arena.cycle[cycleId].pos.y;

    if (cycleId == 0)
        arena.wall[pos.x][pos.y] = REDCYCLE;
    else if (cycleId == 1)
        arena.wall[pos.x][pos.y] = GREENCYCLE;

    arena.cycle[cycleId].dir = dir;

    if (dir == EAST)
        arena.cycle[cycleId].pos.x = arena.cycle[cycleId].pos.x + 1;
    else if (dir == SOUTH)
        arena.cycle[cycleId].pos.y = arena.cycle[cycleId].pos.y + 1;
    else if (dir == WEST)
        arena.cycle[cycleId].pos.x = arena.cycle[cycleId].pos.x - 1;
    else if (dir == NORTH)
        arena.cycle[cycleId].pos.y = arena.cycle[cycleId].pos.y - 1;
}


int get_winner(){
    // to improve
    if (arena.cycle[0].pos.x == arena.cycle[1].pos.x && arena.cycle[0].pos.y == arena.cycle[1].pos.y)
        return -1;
    else if (arena.wall[arena.cycle[0].pos.x][arena.cycle[0].pos.y] != NONE)
        return 1;
    else
        return 0;
}


int main(int argc, char* argv[]) {

    if (name_attach("Game_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in game_admin.c!\n");
        exit(0);
    }


    int start_flag = 0, end_flag = 0;

    while (1){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in game_admin.c!\n");
            exit(0);
        }

        if (msg.type == REGISTER_CYCLE){
            if (nCycle < 2){
                arena.cycle[nCycle].pos = generate_pos(nCycle);
                if (nCycle == 0)
                    arena.cycle[nCycle].dir = EAST;
                else
                    arena.cycle[nCycle].dir = WEST;
                reply.cycleId = nCycle;
                reply.type = INIT;
                cycle_pt[nCycle] = fromWhom;
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
            continue;
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
                timer_flag = 1;
                timer_pt = fromWhom;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            continue;
        }


        if (msg.type == REGISTER_COURIER){
            if (courier2_flag){
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            else{
                courier2_flag = 1;
                courier_pt[2] = fromWhom;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            continue;
        }


        if (msg.type == REGISTER_HUMAN){

            if (nCycle < 2){
                arena.cycle[nCycle].pos = generate_pos(nCycle);
                if (nCycle == 0)
                    arena.cycle[nCycle].dir = EAST;
                else
                    arena.cycle[nCycle].dir = WEST;

                reply.humanId = nCycle;
                reply.type = INIT;
                cycle_pt[nCycle] = fromWhom;
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
            continue;
        }


        if (msg.type == CYCLE_READY){
            cycle_pt[msg.cycleId] = fromWhom;
            cycle_ready[msg.cycleId] = 1;

            if (cycle_ready[0] && cycle_ready[1])
            {
                generate_wall();
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
                cycle_ready[0] = cycle_ready[1] = 0;
                start_flag = 1;
            }
            //else, let the cycle wait
            continue;
        }


        if (msg.type == COURIER_READY){
            courier_pt[2] = fromWhom;
            courier2_ready = 1;
            continue;
        }


        if (msg.type == HUMAN_READY){
            courier_pt[msg.humanId] = fromWhom;
            cycle_ready[msg.humanId] = 1;

            if (cycle_ready[0] && cycle_ready[1])
            {
                generate_wall();
                reply.type = START;
                fprintf(stderr, "start\n");
                reply.humanId = 0;
                if (Reply(cycle_pt[0], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                reply.humanId = 1;
                if (Reply(cycle_pt[1], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                cycle_ready[0] = cycle_ready[1] = 0;
                start_flag = 1;
            }
            //else, let the human wait
            continue;
        }


        if (msg.type == OKAY){
            courier_pt[2] = fromWhom;
            courier2_ready = 1;
            continue;
        }

        // cycle move
        if (msg.type == MOVE){
            fifo_move[(fi_move + fifo_move_size) % 20].msg = msg;
            fifo_move[(fi_move + fifo_move_size) % 20].fromWhom = fromWhom;
            fifo_move[(fi_move + fifo_move_size) % 20].id = msg.cycleId;
            fifo_move[(fi_move + fifo_move_size) % 20].human_flag = 0;
            fifo_move_size++;
            cycle_pt[msg.cycleId] = fromWhom;
            cycle_ready[msg.cycleId] = 1;
            continue;
        }


        // human move
        if (msg.type == HUMAN_MOVE){
            //prevent the human player to move the cycle towards itself
            if (arena.cycle[msg.humanId].dir == (msg.dir + 2) % 4)
                msg.dir = arena.cycle[msg.humanId].dir;

            fifo_move[(fi_move + fifo_move_size) % 20].msg = msg;
            fifo_move[(fi_move + fifo_move_size) % 20].fromWhom = fromWhom;
            fifo_move[(fi_move + fifo_move_size) % 20].id = msg.humanId;
            fifo_move[(fi_move + fifo_move_size) % 20].human_flag = 1;
            fifo_move_size++;
            cycle_pt[msg.humanId] = fromWhom;
            cycle_ready[msg.humanId] = 1;
            continue;
        }


        if (msg.type == TIMER_READY && start_flag){
            timer_pt = fromWhom;
            timer_ready = 1;
            int boost_flag = 0;
            while (fifo_move_size > 0){
                move(fifo_move[fi_move].id, fifo_move[fi_move].msg.dir);

                if (check_end()){
                    end_flag = 1;
                    break;
                }

                if (fifo_move[fi_move].human_flag){
                    // human move
                    reply.type = UPDATE;
                    reply.humanId = fifo_move[fi_move].id;
                }
                else{
                    // cycle move
                    reply.type = UPDATE;
                    reply.arena = arena;
                }
                if (fifo_move[fi_move].msg.boost == YES)
                    boost_flag = 1;

                cycle_ready[fifo_move[fi_move].id] = 0;
                if (Reply(fifo_move[fi_move].fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                fi_move = (fi_move + 1) % 20;
                fifo_move_size--;
            }

            reply.type = DISPLAY_ARENA;
            reply.arena = arena;
            courier2_ready = 0;
            if (Reply(courier_pt[2], &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }

            if (end_flag)   break;

            reply.type = SLEEP;
            reply.interval = boost_flag ? 10000 : 50000;
            timer_ready = 0;
            if (Reply(timer_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
        }
    }
    
    while (!(cycle_ready[0] && cycle_ready[1] && timer_ready && courier2_ready)){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in game_admin.c!\n");
            exit(0);
        }
        if (msg.type == MOVE)
            cycle_ready[msg.cycleId] = 1;
        else if (msg.type == HUMAN_MOVE)
            cycle_ready[msg.humanId] = 1;
        else if (msg.type == TIMER_READY)
            timer_ready = 1;
        else if (msg.type == OKAY)
            courier2_ready = 1;
    }

    reply.type = END;
    if (Reply(cycle_pt[0], &reply, sizeof(reply)) == -1) {
        fprintf(stderr, "Cannot reply message!\n");
        exit(0);
    }
    if (Reply(cycle_pt[1], &reply, sizeof(reply)) == -1) {
        fprintf(stderr, "Cannot reply message!\n");
        exit(0);
    }
    if (Reply(timer_pt, &reply, sizeof(reply)) == -1) {
        fprintf(stderr, "Cannot reply message!\n");
        exit(0);
    }

    reply.arena = msg.arena;
    reply.cycleId = get_winner();
    if (Reply(courier_pt[2], &reply, sizeof(reply)) == -1) {
        fprintf(stderr, "Cannot reply message!\n");
        exit(0);
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
