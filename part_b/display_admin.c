#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"


int main(int argc, char* argv[]) {

    //char *fromWhom1 = NULL;
    //char *fromWhom2 = NULL;
    char *fromWhom = NULL;
    char *Courier_pt = NULL;
    char *Painter_pt = NULL;
    //MESSAGE msg1, msg2, reply1, reply2;
    MESSAGE msg, reply;
    MESSAGE fifo[20];
    int fifo_size = 0, fi = 0;

    //FILE *f = fopen("file.txt", "w"); // for test
    //fprintf(f, "1st line!\n");


    if (name_attach("Display_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in display_admin.c!\n");
        exit(0);
    }


    int painter_flag = 0, end_flag = 0;
    while (1){
        if (Receive(&fromWhom, &msg, sizeof(msg)) == -1) {
            fprintf(stderr, "Cannot receive message in display_admin.c!\n");
            exit(0);
        }

        if (msg.type == PAINTER_READY){
            if (fifo_size > 0){
                reply.type = PAINT;
                reply.arena = fifo[fi].arena;
                fi = (fi + 1) % 20;
                fifo_size--;

                if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
            }
            // fifo_size == 0, painter_flag = 1 means painter is ready but have no work to do yet
            else{
                painter_flag = 1;
                Painter_pt = fromWhom;
            }
        }

        if (msg.type == DISPLAY_ARENA){
            if (painter_flag){
                reply.type = PAINT;
                reply.arena = msg.arena;

                painter_flag = 0;
                if (Reply(Painter_pt, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
            }

            // painter is not ready yet, buffer the msg
            else{
                fifo[(fi + fifo_size) % 20] = msg;
                fifo_size++;
            }

            // reply the courier that we had dealt with the display request
            reply.type = OKAY;
            if (Reply(fromWhom, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
        }

        if (msg.type == END || end_flag){
            if (msg.type == END)
                Courier_pt = fromWhom;

            if (!painter_flag){
                end_flag = 1;
                Courier_pt = fromWhom;
                // flag the end msg and store the pointer to courier, wait till painter is ready
            }
            else{
                end_flag = 0;
                reply.type = END;
                reply.arena = msg.arena;
                reply.cycleId = msg.cycleId;
                if (Reply(Painter_pt, &reply, sizeof(reply)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
                }

                reply.type = OKAY;
                if (Reply(Courier_pt, &reply, sizeof(reply)) == -1) {
                    fprintf(stderr, "Cannot reply message!\n");
                    exit(0);
                }
                break;
            }
        }
    }

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    return 0;
}
