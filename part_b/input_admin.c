#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "simpl.h"
#include "message.h"


typedef struct { 
    int id;
    DIRECTION dir;
    BOOST boost;
} HUMAN;


char *fromWhom = NULL;
char *human_pt[2] = {NULL, NULL};
char *keyboard_pt = NULL;
MESSAGE msg, reply;
HUMAN fifo[20];
DIRECTION human_dir[2];
int fifo_size = 0, fi = 0, human_ready[2] = {0, 0}, human_start[2] = {0, 0}, nHuman = 0;
int keyboard_ready = 0, start_flag = 0, nCourier = 0, humanId = 0;


void check_contain_move_key(int id, int key[], DIRECTION* dir, BOOST* boost){
    int i, new_dir = -1;
    *boost = NO;
    for (i = 0; i < MAX_KEYS; i++){
        if ((key[i] == 'q' && id == 0) || (key[i] == 'p' && id == 1)){
            *boost = YES;
            break;
        }
    }

    if (id == 0){
        for (i = 0; i < MAX_KEYS; i++){
            if (key[i] == 'a' || key[i] == 'w' || key[i] == 's' || key[i] == 'd'){
                new_dir = key[i];
            }
        }
    }
    else if (id == 1){
        for (i = 0; i < MAX_KEYS; i++){
            // ASCII codes for four directions
            if (key[i] == 72 || key[i] == 80 || key[i] == 75 || key[i] == 77){
                new_dir = key[i];
            }
        }
    }

    if (new_dir == 'a' || new_dir == 75)
        *dir = WEST;
    else if (new_dir == 'd' || new_dir == 77)
        *dir = EAST;
    else if (new_dir == 'w' || new_dir == 72)
        *dir = NORTH;
    else if (new_dir == 's' || new_dir == 80)
        *dir = SOUTH;
    else if (new_dir == -1){
        *dir = human_dir[id];//key does not contain a valid direction
    }
}


int main(int argc, char* argv[]) {

    if (name_attach("Input_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in input_admin.c!\n");
        exit(0);
    }


    while (1){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in input_admin.c!\n");
            exit(0);
        }

        if (msg.type == REGISTER_COURIER){
            if (nCourier < 2){
                reply.type = INIT;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                    exit(0);
                }
                nCourier++;
            }
            else{
                reply.type = FAIL;
                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                    exit(0);
                }
            }
            fprintf(stderr, "1\n");
        }


        if (msg.type == REGISTER_KEYBOARD){
            fprintf(stderr, "2.1\n");
            reply.type = INIT;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                exit(0);
            }
            fprintf(stderr, "2.2\n");
        }


        if (msg.type == COURIER_READY){
            reply.type = REGISTER_HUMAN;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            fprintf(stderr, "3\n");
        }


        if (msg.type == INIT){
            if (nHuman == 0){
                humanId = msg.humanId;
                human_pt[0] = fromWhom;
                nHuman++;
            }
            else if (nHuman == 1){
                human_pt[humanId] = human_pt[0];
                human_pt[msg.humanId] = fromWhom;
                nHuman++;
            }
            //human_ready[nHuman] = 1;
            
            reply.type = HUMAN_READY;
            reply.humanId = msg.humanId;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            fprintf(stderr, "4\n");
        }


        if (msg.type == FAIL){
           //
        }


        if (msg.type == KEYBOARD_READY){
            keyboard_pt = fromWhom;
            keyboard_ready = 1;
            //reply when all human are ready
            fprintf(stderr, "5\n");
        }


        if (msg.type == START){
            if (nHuman == 1){
                human_start[0] = 1;
                human_ready[0] = 1;
                humanId = msg.humanId; // only record humanId when nHuman = 1
                human_dir[0] = (humanId == 0) ? EAST : WEST;
                fprintf(stderr, "6.1\n");
            }
            else if (nHuman == 2){
                human_start[msg.humanId] = 1;
                //human_pt[msg.humanId] = fromWhom; //address of the courier corresponding to the human
                human_ready[msg.humanId] = 1;
                human_dir[msg.humanId] = (msg.humanId == 0) ? EAST : WEST;
                fprintf(stderr, "6.2\n");
            }
            // reply after human move
        }


        if (msg.type == KEYBOARD_INPUT){

            DIRECTION dir;
            BOOST boost;
            if (nHuman == 1){
                // 1 for check one human player's keys, arrows
                check_contain_move_key(1, msg.key, &dir, &boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = humanId;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
                human_ready[0] = 1;
            }
            else if (nHuman == 2){
                // 0 for check 1st human player's keys, w s a d
                check_contain_move_key(0, msg.key, &dir, &boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = 0;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
                human_ready[0] = 1;
                // 1 for check 2rd human player's keys, arrows
                check_contain_move_key(1, msg.key, &dir, &boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = 1;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
                human_ready[1] = 1;
            }
            // reply after human move
            fprintf(stderr, "keyboard!\n");
        }


        if (msg.type == UPDATE){
            if (nHuman == 1)
                human_ready[0] = 1;
            else
                human_ready[msg.humanId] = 1;
            reply.type = OKAY;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            fprintf(stderr, "update\n");
        }


        if (msg.type == END){
            fprintf(stderr, "7.1\n");
            reply.type = END;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }

            reply.type = OKAY;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            fprintf(stderr, "7.2\n");
            break;
        }


        if (keyboard_ready && ((nHuman == 1 && human_start[0]) || (nHuman == 2 && human_start[0] && human_start[1]))){
            //reply keyboard to start
            reply.type = START;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            fprintf(stderr, "start!\n");
            keyboard_ready = 0; // avoid double start the keyboard
        }


        if (fifo_size > 0){
            while (fifo_size > 0){
                reply.type = HUMAN_MOVE;
                reply.dir = fifo[fi].dir;
                reply.boost = fifo[fi].boost;
                reply.humanId = fifo[fi].id;

                if (nHuman == 1){
                    human_ready[0] = 1;
                    if (Reply(human_pt[0], &reply, sizeof(reply)) == -1) {
                        fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                        exit(0);
                    }
                }
                else {
                    human_ready[fifo[fi].id] = 0;
                    if (Reply(human_pt[fifo[fi].id], &reply, sizeof(reply)) == -1) {
                        fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                        exit(0);
                    }
                }

                fi = (fi + 1) % 20;
                fifo_size--;
            }

            fprintf(stderr, "human move\n");

            reply.type = OKAY;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
        }

    }
    
    

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name in input_admin.c!\n");
        exit(0);
    }

    return 0;
}
