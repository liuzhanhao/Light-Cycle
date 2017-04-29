#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "simpl.h"
#include <stdbool.h>
#include "message.h"


int main(int argc, char* argv[]) {
    int fd_game, fd_display, fd_input, courierId;
    MESSAGE msg, reply_game, reply_display, reply_input;

    char name[] = "Courier ?";

    /* Use the argument to create a 'unique' name */
    if (argc > 1) {
        name[8] = argv[1][0];
    }

    courierId = name[8] - '0';

    if (courierId == 2) {
        if (name_attach(name, NULL) == -1) {
            fprintf(stderr, "Cannot attach name Courier 2 in courier.c!\n");
            exit(0);
        }

        /* Locate Admin who is the host of the game */
        if ((fd_game = name_locate("Game_Admin")) == -1) {
            fprintf(stderr, "Cannot locate Game_Admin in courier.c!\n");
            exit(0);
        }

        if ((fd_display = name_locate("Display_Admin")) == -1) {
            fprintf(stderr, "Cannot locate Display_Admin in courier.c!\n");
            exit(0);
        }

        msg.type = REGISTER_COURIER;

        if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
            fprintf(stderr, "Cannot send message to Game_Admin in courier.c!\n");
        }


        while (reply_game.type != INIT)
        {
            // do nothing
            //fprintf(stderr, "Successfully register!\n");
            if (reply_game.type == FAIL)
            {
                fprintf(stderr, "Fail to register in courier.c!\n");
                exit(0);
            }
        }

        msg.type = COURIER_READY;

        if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
            fprintf(stderr, "Cannot send COURIER_READY message!\n");
        }

        while (reply_game.type != END)
        {
            if (reply_game.type == DISPLAY_ARENA)
            {
                msg.type = DISPLAY_ARENA;
                msg.arena = reply_game.arena;
                if (Send(fd_display, &msg, &reply_display, sizeof(msg), sizeof(reply_display)) == -1) {
                    fprintf(stderr, "Cannot send DISPLAY_ARENA message!\n");
                }

                if (reply_display.type == OKAY)
                {
                    msg.type = OKAY;
                    if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
                        fprintf(stderr, "Cannot send OKAY message!\n");
                    }
                }
            }
        }

        msg.type = END;
        msg.cycleId = reply_game.cycleId;
        msg.arena = reply_game.arena;
        if (Send(fd_display, &msg, &reply_display, sizeof(msg), sizeof(reply_display)) == -1) {
            fprintf(stderr, "Cannot send END message!\n");
        }

        while (reply_display.type != OKAY)
        {
            // wait
        }
    }

    else if (courierId == 0 || courierId == 1) {
        if (name_attach(name, NULL) == -1) {
            fprintf(stderr, "Cannot attach name Courier 0/1 in courier.c!\n");
            exit(0);
        }

        /* Locate Admin who is the host of the game */
        if ((fd_input = name_locate("Input_Admin")) == -1) {
            fprintf(stderr, "Cannot locate Input_Admin in courier.c!\n");
            exit(0);
        }

        /* Locate Admin who is the host of the game */
        if ((fd_game = name_locate("Game_Admin")) == -1) {
            fprintf(stderr, "Cannot locate Game_Admin in courier.c!\n");
            exit(0);
        }

        msg.type = REGISTER_COURIER;

        if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
            fprintf(stderr, "Cannot send message to Input_Admin in courier.c!\n");
        }


        if (reply_input.type == INIT) {
            //humanId = reply_input.humanId;
        }
        else if (reply_input.type == FAIL) {
            fprintf(stderr, "Fail to register Courier 0/1 in courier.c!\n");
            exit(0);
        }

        msg.type = COURIER_READY;

        if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
            fprintf(stderr, "Cannot send COURIER_READY message!\n");
        }

        if (reply_input.type == REGISTER_HUMAN) {
            msg.type = REGISTER_HUMAN;
            if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
                fprintf(stderr, "Cannot send REGISTER_HUMAN message!\n");
            }

            if (reply_game.type == INIT) {
                msg.type = INIT;
                msg.humanId = reply_game.humanId;
                if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
                    fprintf(stderr, "Cannot send INIT message in courier.c!\n");
                }
            }
            else if (reply_game.type == FAIL) {
                msg.type = FAIL;
                if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
                    fprintf(stderr, "Cannot send FAIL message in courier.c!\n");
                }
                exit(0);
            }
        }

        if (reply_input.type == HUMAN_READY) {
            msg.type = HUMAN_READY;
            msg.humanId = reply_input.humanId;
            if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
                fprintf(stderr, "Cannot send HUMAN_READY message in courier.c!\n");
            }

            if (reply_game.type == START)
            {
                msg.type = START;
                msg.humanId = reply_game.humanId;

                if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
                    fprintf(stderr, "Cannot send START message in courier.c!\n");
                }
            }
        }

        while (reply_game.type != END) {
            if (reply_input.type == HUMAN_MOVE) {
                msg.type = HUMAN_MOVE;
                msg.humanId = reply_input.humanId;
                msg.dir = reply_input.dir;
                msg.boost = reply_input.boost;
                if (Send(fd_game, &msg, &reply_game, sizeof(msg), sizeof(reply_game)) == -1) {
                    fprintf(stderr, "Cannot send HUMAN_MOVE message in courier.c!\n");
                }
            }

            if (reply_game.type == UPDATE){
                msg.type = UPDATE;
                msg.humanId = reply_game.humanId;

                if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
                    fprintf(stderr, "Cannot send UPDATE message in courier.c!\n");
                }
            }
        }

        msg.type = END;
        if (Send(fd_input, &msg, &reply_input, sizeof(msg), sizeof(reply_input)) == -1) {
            fprintf(stderr, "Cannot send END message in courier.c!\n");
        }
    }

    if (name_detach() == -1) {
            fprintf(stderr, "Cannot detach COURIER name!\n");
            exit(0);
        }
    
    return 0;
}
