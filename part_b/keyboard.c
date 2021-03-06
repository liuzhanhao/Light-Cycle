#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "simpl.h"
#include "message.h"


int main(int argc, char* argv[]) {
    int fd, i;
    MESSAGE msg, reply;

    char name[] = "Keyboard";

    //FILE *f = fopen("file.txt", "w");
    //setlinebuf(f);

    srand(time(NULL));

    if (name_attach(name, NULL) == -1) {
        fprintf(stderr, "Cannot attach name in keyboard.c!\n");
        exit(0);
    }

    /* Locate Admin who is the host of the game */
    if ((fd = name_locate("Input_Admin")) == -1) {
        fprintf(stderr, "Cannot locate name in keyboard.c!\n");
        exit(0);
    }

    msg.type = REGISTER_KEYBOARD;

    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot register keyboard!\n");
            exit(0);
        }

    if (reply.type == INIT)
    {
        msg.type = KEYBOARD_READY;
        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in keyboard.c!\n");
            exit(0);
        }
    }


    msg.type = KEYBOARD_INPUT;
    // initialize the window
    initscr();
    nodelay(stdscr,TRUE);
    cbreak(); // disable line buffering
    noecho(); // keyboard inputs shouldn't be displayed
    keypad(stdscr,TRUE);

    while (reply.type != END)
    {
        
        for (i = 0; i < MAX_KEYS; i++){
            msg.key[i] = getch();
        }

        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in painter.c!\n");
            exit(0);
        }
    }

    //endwin();
    
    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach PAINTER name!\n");
        exit(0);
    }

    //fprintf(f, "end!\n");
    //fclose(f);
    return 0;
}
