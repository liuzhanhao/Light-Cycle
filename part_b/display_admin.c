#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simpl.h"
#include "message.h"


int main(int argc, char* argv[]) {

    char *fromWhom1 = NULL;
    char *fromWhom2 = NULL;
    MESSAGE msg1, msg2, reply1, reply2;
    MESSAGE fifo[20];
    int fifo_size = 0, fi = 0;

    FILE *f = fopen("file.txt", "w"); // for test
    fprintf(f, "1st line!\n");


    if (name_attach("Display_Admin", NULL) == -1) {
        fprintf(stderr, "Cannot attach name in display_admin.c!\n");
        exit(0);
    }

    while (msg2.type != END) {

        if (Receive(&fromWhom1, &msg1, sizeof(msg1)) == -1) {
            fprintf(stderr, "Cannot receive message from painter!\n");
            exit(0);
        }

        if (Receive(&fromWhom2, &msg2, sizeof(msg2)) == -1) {
            fprintf(stderr, "Cannot receive message from courier!\n");
            exit(0);
            }

        printf("%s\n", fromWhom2); // painter, bug

        if (msg2.type == DISPLAY_ARENA){
            fprintf(f, "DISPLAY_ARENA!\n");
            fifo[(fi + fifo_size) % 20] = msg2;
            fifo_size++;

            reply2.type = OKAY;
            if (Reply(fromWhom2, &reply2, sizeof(reply2)) == -1) {
                fprintf(f, "Cannot reply message!\n");
                exit(0);
            }
            fprintf(f, "replied OKAY!\n");
        }

        if (msg2.type == END){
            fprintf(f, "end!\n");
            fclose(f);
            reply1.type = END;
            reply1.arena = msg2.arena;
            reply1.cycleId = msg2.cycleId;
            if (Reply(fromWhom1, &reply1, sizeof(reply1)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }

            reply2.type = OKAY;
            if (Reply(fromWhom2, &reply2, sizeof(reply2)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
            break;
        }

        if (msg1.type == PAINTER_READY){

            reply1.type = PAINT;
            reply1.arena = fifo[fi].arena;
            if (fi < 19) fi++;
            else if (fi == 19) fi = 0;
            fifo_size--;

            if (Reply(fromWhom1, &reply1, sizeof(reply1)) == -1) {
                fprintf(stderr, "Cannot reply message!\n");
                exit(0);
            }
            fprintf(f, "replied PAINT!\n");
        }
    }

    //fprintf(f, "break!\n");
    

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach name!\n");
        exit(0);
    }

    
    return 0;
}
