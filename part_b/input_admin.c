#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "simpl.h"
#include "message.h"
#include <curses.h>


typedef struct { 
    int id;
    DIRECTION dir;
    BOOST boost;
} HUMAN;


char *fromWhom = NULL;
char *human_pt[2] = {NULL, NULL};
char *keyboard_pt = NULL;
char *end_pt = NULL;
MESSAGE msg, reply;
HUMAN fifo[20];
DIRECTION human_dir[2];
DIRECTION dir;
BOOST boost;
int fifo_size = 0, fi = 0, human_ready[2] = {0, 0}, human_start[2] = {0, 0}, nHuman = 0;
int keyboard_ready = 0, nCourier = 0, humanId = 0, new_dir = 0;


int main(int argc, char* argv[]) {
    //FILE *f = fopen("file.txt", "w");
    //setlinebuf(f);

    if (name_attach("Input_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in input_admin.c!\n");
        exit(0);
    }


    int start_flag = 0;
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
            //fprintf(f, "REGISTER_COURIER\n");
        }


        if (msg.type == COURIER_READY){
            reply.type = REGISTER_HUMAN;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            //fprintf(f, "COURIER_READY\n");
        }


        if (msg.type == INIT){
            if (nHuman == 0){
                humanId = msg.humanId;
                human_pt[0] = fromWhom;
                nHuman = nHuman + 1;
            }
            else {
                human_pt[humanId] = human_pt[0];
                human_pt[msg.humanId] = fromWhom;
                nHuman = nHuman + 1;
            }
            
            reply.type = HUMAN_READY;
            reply.humanId = msg.humanId;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            //fprintf(f, "INIT\n");
        }

        if (msg.type == FAIL){
            //fprintf(f, "FAIL\n");
        }


        if (msg.type == START){
            //fprintf(f, "START\n");
            if (nHuman == 1){
                human_start[0] = 1;
                human_ready[0] = 1;
                human_pt[0] = fromWhom;
                humanId = msg.humanId; // only record humanId when nHuman = 1
                human_dir[0] = (humanId == 0) ? EAST : WEST;
                //fprintf(f, "START1\n");
            }
            else if (nHuman == 2){
                human_start[msg.humanId] = 1;
                human_ready[msg.humanId] = 1;
                human_pt[msg.humanId] = fromWhom;
                human_dir[msg.humanId] = (msg.humanId == 0) ? EAST : WEST;
                //fprintf(f, "START2\n");
            }
            // reply after human move
        }


        if (msg.type == REGISTER_KEYBOARD){
            keyboard_pt = fromWhom;
            reply.type = INIT;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                exit(0);
            }
            //fprintf(f, "REGISTER_KEYBOARD\n");
        }


        if (msg.type == KEYBOARD_READY || start_flag){
            if (msg.type == KEYBOARD_READY){
                keyboard_pt = fromWhom;
                keyboard_ready = 1;
                //fprintf(f, "KEYBOARD_READY\n");
                start_flag = 1;
            }

            if ((nHuman == 1 && human_start[0]) || (nHuman == 2 && human_start[0] && human_start[1])){
                reply.type = START;
                if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                }
                //fprintf(f, "start keyboard!\n");
                start_flag = 0;
                keyboard_ready = 0;
            }
        }


        if (msg.type == KEYBOARD_INPUT){
            int i;
            keyboard_pt = fromWhom;
            if (nHuman == 1){
                boost = NO;
                for (i = 0; i < MAX_KEYS; i++){
                    if (msg.key[i] == 'p'){
                        boost = YES;
                        break;
                    }
                }

                for (i = MAX_KEYS-1; i >= 0; i--){
                    // ASCII codes for four directions
                    if (msg.key[i] == 260 || msg.key[i] == 261 || msg.key[i] == 259 || msg.key[i] == 258){
                        new_dir = msg.key[i];
                        break;
                    }
                }
                if (new_dir == 260)
                    human_dir[0] = WEST;
                else if (new_dir == 261)
                    human_dir[0] = EAST;
                else if (new_dir == 259)
                    human_dir[0] = NORTH;
                else if (new_dir == 258)
                    human_dir[0] = SOUTH;
                
                dir = human_dir[0];
                // 1 for check one human player's keys, arrows
                //check_contain_move_key(1, humanId, msg.key, dir, boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = humanId;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
            }
            else if (nHuman == 2){
                // human[0]
                boost = NO;
                for (i = 0; i < MAX_KEYS; i++){
                    if (msg.key[i] == 'q'){
                        boost = YES;
                        break;
                    }
                }
                for (i = MAX_KEYS-1; i >= 0; i--){
                    // ASCII codes for four directions
                    if (msg.key[i] == 'a' || msg.key[i] == 'w' || msg.key[i] == 's' || msg.key[i] == 'd'){
                        new_dir = msg.key[i];
                        break;
                    }
                }
                if (new_dir == 'a')
                    human_dir[0] = WEST;
                else if (new_dir == 'd')
                    human_dir[0] = EAST;
                else if (new_dir == 'w')
                    human_dir[0] = NORTH;
                else if (new_dir == 's')
                    human_dir[0] = SOUTH;
                
                dir = human_dir[0];
                // 1 for check one human player's keys, arrows
                //check_contain_move_key(1, humanId, msg.key, dir, boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = 0;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
                // human[1]
                boost = NO;
                for (i = 0; i < MAX_KEYS; i++){
                    if (msg.key[i] == 'p'){
                        boost = YES;
                        break;
                    }
                }
                for (i = MAX_KEYS-1; i >= 0; i--){
                    // ASCII codes for four directions
                    if (msg.key[i] == 260 || msg.key[i] == 261 || msg.key[i] == 259 || msg.key[i] == 258){
                        new_dir = msg.key[i];
                        break;
                    }
                }
                if (new_dir == 260)
                    human_dir[1] = WEST;
                else if (new_dir == 261)
                    human_dir[1] = EAST;
                else if (new_dir == 259)
                    human_dir[1] = NORTH;
                else if (new_dir == 258)
                    human_dir[1] = SOUTH;
                
                dir = human_dir[1];
                // 1 for check one human player's keys, arrows
                //check_contain_move_key(1, humanId, msg.key, dir, boost);
                fifo[(fi + fifo_size) % 20].dir = dir;
                fifo[(fi + fifo_size) % 20].id = 1;
                fifo[(fi + fifo_size) % 20].boost = boost;
                fifo_size++;
            }

            keyboard_ready = 1;
            // reply after human move
            //fprintf(f, "KEYBOARD_INPUT %d\n", new_dir);
        }


        if (msg.type == UPDATE){
            if (nHuman == 1){
                human_ready[0] = 1;
                human_pt[0] = fromWhom;
            }
            else if (nHuman == 2){
                human_ready[msg.humanId] = 1;
                human_pt[msg.humanId] = fromWhom;
            }
            //fprintf(f, "UPDATE\n");
        }


        if (msg.type == END){
            end_pt = fromWhom;
            //fprintf(f, "END\n");
            break;
        }


        if (fifo_size > 0){
            //fprintf(stderr, "test!\n");
            while (fifo_size > 0){
                reply.type = HUMAN_MOVE;
                reply.dir = fifo[fi].dir;
                reply.boost = fifo[fi].boost;
                reply.humanId = fifo[fi].id;

                if (nHuman == 1 && human_ready[0]){
                    human_ready[0] = 0;
                    if (Reply(human_pt[0], &reply, sizeof(reply)) == -1) {
                        fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                        exit(0);
                    }
                    //fprintf(f, "HUMAN_MOVE\n");
                }
                else if (nHuman == 2 && human_ready[fifo[fi].id]) {
                    human_ready[fifo[fi].id] = 0;
                    if (Reply(human_pt[fifo[fi].id], &reply, sizeof(reply)) == -1) {
                        fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                        exit(0);
                    }
                    //fprintf(f, "HUMAN_MOVE %d\n", fifo[fi].id);
                }
                //maybe need to move into the above if {}
                fi = (fi + 1) % 20;
                fifo_size--;
            }

            reply.type = OKAY;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
            keyboard_ready = 0;
        }
    }
    

    if (nHuman == 1){
        if (!keyboard_ready){
            if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
                fprintf(stderr, "Cannot receive message in input_admin.c!\n");
                exit(0);
            }
            keyboard_pt = fromWhom;
        }

        reply.type = END;
        if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot reply message in input_admin.c!\n");
        }
    }

    else if (nHuman == 2){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in input_admin.c!\n");
            exit(0);
        }

        if (msg.type == END){
            reply.type = OKAY;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            if (!keyboard_ready){
                if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
                    fprintf(stderr, "Cannot receive message in input_admin.c!\n");
                    exit(0);
                }
                keyboard_pt = fromWhom;
            }

            reply.type = END;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
        }
        else{ //keyboard.input, keep receiving for another courier's end
            reply.type = END;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }

            if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
                fprintf(stderr, "Cannot receive message in input_admin.c!\n");
                exit(0);
            }
            reply.type = OKAY;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
        }
    }

    

    reply.type = OKAY;
    if (Reply(end_pt, &reply, sizeof(reply)) == -1) {
        fprintf(stderr, "Cannot reply message in input_admin.c!\n");
    }

    //fprintf(f, "END2!\n");
    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name in input_admin.c!\n");
        exit(0);
    }

    //fclose(f);
    return 0;
}