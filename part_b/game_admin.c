#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"

char *fromWhom = NULL;
char *timer_pt = NULL;
char *cycle_pt[2] = {NULL, NULL};
char *courier_pt[3] = {NULL, NULL, NULL};
ARENA arena;
MESSAGE msg, reply, msg_temp;
MESSAGE fifo_msg[20];
ARENA fifo[20];
int fifo_size = 0, fi = 0, fifo_msg_size = 0, fi_msg = 0;
int nCycle = 0, timer_flag = 0, courier_flag = 0;
int cycle_ready[2] = {0, 0}, timer_ready = 0, courier2_ready = 0;


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


int check_end(){
    return arena.wall[arena.cycle[0].pos.x][arena.cycle[0].pos.y] != NONE || arena.wall[arena.cycle[1].pos.x][arena.cycle[1].pos.y] != NONE;
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


    int end_flag = 0, move_flag = 0, move_ready = 0;
    while (1){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in game_admin.c!\n");
            exit(0);
        }

        if (msg.type == REGISTER_CYCLE){
            printf("test_cycle\n");
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
            printf("test_timer\n");
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
        }


        if (msg.type == REGISTER_COURIER){
            printf("test_courier\n");
            if (courier_flag){
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
            else{
                courier_flag = 1;
                courier_pt[2] = fromWhom;
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
            }
        }


        if (msg.type == REGISTER_HUMAN){
            printf("test_human\n");
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
            printf("test_cycle_ready\n");
            cycle_pt[msg.cycleId] = fromWhom;
            cycle_ready[msg.cycleId] = 1;

            if (cycle_ready[0] && cycle_ready[1])
            {
                printf("start\n");
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
            }
            //else, let the cycle wait
        }


        if (msg.type == TIMER_READY){
            printf("test_timer_ready\n");
            timer_ready = 1;
            move_ready = 1;
            timer_pt = fromWhom;
        }


        if (msg.type == COURIER_READY){
            printf("test_courier_ready\n");
            courier_pt[2] = fromWhom;

            if (fifo_size > 0){
                reply.type = DISPLAY_ARENA;
                reply.arena = fifo[fi];
                fi = (fi + 1) % 20;
                fifo_size--;

                courier2_ready = 0;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
            }
            else
                courier2_ready = 1;
        }


        if (msg.type == HUMAN_READY){
            printf("test_human_ready\n");
            courier_pt[msg.humanId] = fromWhom;
            cycle_ready[msg.humanId] = 1;

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
            }
            //else, let the human wait
        }


        if (msg.type == OKAY){
            courier_pt[2] = fromWhom;

            if (fifo_size > 0){
                reply.type = DISPLAY_ARENA;
                reply.arena = fifo[fi];
                fi = (fi + 1) % 20;
                fifo_size--;

                courier2_ready = 0;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
            }
            else
                courier2_ready = 1;
        }

        // cycle move
        if (msg.type == MOVE || move_flag){
            if (msg.type == MOVE && timer_ready){

                //这里要记录cycle的pt, 等计时完后用来update
                timer_ready = 0;
                move_ready = 0;
                reply.type = SLEEP;
                cycle_pt[msg.cycleId] = fromWhom;

                fifo_msg[(fi_msg + fifo_msg_size) % 20] = msg;
                fifo_msg_size++;

                if (msg.boost == YES)
                    reply.interval = 10000;
                else if (msg.boost == NO)
                    reply.interval = 50000;

                if (Reply(timer_pt, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }
                move_flag = 1;
            }
            if (move_ready){
                if (fifo_msg_size > 0){
                    msg_temp = fifo_msg[fi_msg];
                    fi_msg = (fi_msg + 1) % 20;
                    fifo_msg_size--;
                }

                move(msg_temp.cycleId, msg_temp.dir);
                move_flag = 0;
                
                reply.type = UPDATE;
                reply.arena = arena;
                // 这个fromwhom要改成记录在buffer里面的cycle的pt
                if (Reply(cycle_pt[msg.cycleId], &reply, sizeof(reply)) == -1) {
                        fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                        exit(0);
                    }

                fifo[(fi + fifo_size) % 20] = arena;
                fifo_size++;
            }
        }


        // human move
        if (msg.type == HUMAN_MOVE){
            courier_pt[msg.humanId] = fromWhom;
            move(msg.humanId, msg.dir);

            reply.type = UPDATE;
            reply.humanId = msg.humanId;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in game_admin.c!\n");
                    exit(0);
                }

            fifo[(fi + fifo_size) % 20] = arena;
            fifo_size++;
        }


        // check end
        if (check_end() || end_flag){
            if (cycle_ready[0] && cycle_ready[1] && timer_ready && courier2_ready){

                end_flag = 0;
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

                if (Reply(courier_pt[0], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }

                if (Reply(courier_pt[1], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }

                reply.arena = msg.arena;
                reply.cycleId = get_winner();
                if (Reply(courier_pt[2], &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
                break;
            }
            
            else{
                end_flag = 1;
            }
        }

        //sleep(1);
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
