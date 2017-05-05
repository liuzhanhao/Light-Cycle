#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "simpl.h"
#include "message.h"


char *fromWhom = NULL;
char *courier_pt[2] = {NULL, NULL};
ARENA arena;
MESSAGE msg, reply;
MOVE_MSG fifo_move[20];
int fifo_move_size = 0, fi_move = 0, nCourier = 0;


int main(int argc, char* argv[]) {

    if (name_attach("Input_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in input_admin.c!\n");
        exit(0);
    }


    int start_flag = 0, end_flag = 0;

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
        }


        if (msg.type == REGISTER_KEYBOARD){
            reply.type = INIT;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
                exit(0);
            }
            keyboard_flag = 1;
        }


        if (msg.type == COURIER_READY){
            reply.type = REGISTER_HUMAN;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
        }


        if (msg.type == INIT){
            humanId[nHuman] = msg.humanId;
            human_pt[nHuman] = fromWhom;
            //human_ready[nHuman] = 1;
            nHuman++;
            
            reply.type = HUMAN_READY;
            reply.humanId = msg.humanId;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
        }


        if (msg.type == FAIL){
           //
        }


        if (msg.type == KEYBOARD_READY){
            keyboard_pt = fromWhom;
            keyboard_ready = 1;
        }


        if (msg.type == START){
            human_start[msg.humanId] = 1;
            human_pt[msg.humanId] = fromWhom;
            // 先不回复courier,等有Human move再回复
        }


        if (msg.type == KEYBOARD_INPUT){
            //check input
        }


        if (keyboard_ready && ((nHuman == 1 && human_start[0]) || (nHuman == 2 && human_start[0] && human_start[1]))){
            //reply keyboard to start
            reply.type = START;
            if (Reply(keyboard_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message in input_admin.c!\n");
            }
            keyboard_ready = 0; // avoid double start the keyboard
        }
    }
    
    

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
