#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "simpl.h"
#include "message.h"

// color pairs
enum {NONE_COL = 1, REDCYCLE_COL, GREENCYCLE_COL, REDLIGHT_COL, GREENLIGHT_COL, BOUNDARY_COL};

void assigncolors() {
    init_pair(NONE_COL, COLOR_WHITE, COLOR_BLACK);
    init_pair(REDCYCLE_COL, COLOR_RED, COLOR_BLACK);
    init_pair(GREENCYCLE_COL, COLOR_GREEN, COLOR_BLACK);
    init_pair(REDLIGHT_COL, COLOR_RED, COLOR_RED);
    init_pair(GREENLIGHT_COL, COLOR_GREEN, COLOR_GREEN);
    init_pair(BOUNDARY_COL, COLOR_WHITE, COLOR_WHITE);
}

void draw_map(ARENA arena)
{
    //WALL* wall = arena.wall;
    CYCLE* cycle = arena.cycle;

    int x, y, maxx, maxy;
    int center_x = (cycle[0].pos.x + cycle[1].pos.x) / 2;
    int center_y = (cycle[0].pos.y + cycle[1].pos.y) / 2;

    getmaxyx(stdscr, maxy, maxx);
    int margin_x = center_x - maxx / 2;
    int margin_y = center_y - maxy / 2;

    for(y = 0; y < maxy; y++)
    {
        for(x = 0; x < maxx; x++)
        {
            move(y, x);

            if ((x + margin_x >=  MAX_WIDTH) | (x + margin_x < 0) | (y + margin_y >= MAX_HEIGHT) | (y + margin_y < 0))
            {
                color_set(NONE_COL, NULL);
                addch(' ');
            }
            else if (arena.wall[x + margin_x][y + margin_y] == BOUNDARY)
            {
                color_set(BOUNDARY_COL, NULL);
                addch(' ');
            }
            else if (arena.wall[x + margin_x][y + margin_y] == REDCYCLE)
            {
                color_set(REDLIGHT_COL, NULL);
                addch(' ');
            }
            else if (arena.wall[x + margin_x][y + margin_y] == GREENCYCLE)
            {
                color_set(GREENLIGHT_COL, NULL);
                addch(' ');
            }
            else if ((x + margin_x) == cycle[0].pos.x && (y + margin_y) == cycle[0].pos.y)
            {
                color_set(REDCYCLE_COL, NULL);
                addch('@' | A_BOLD);
            }
            else if ((x + margin_x) == cycle[1].pos.x && (y + margin_y) == cycle[1].pos.y)
            {
                color_set(GREENCYCLE_COL, NULL);
                addch('@' | A_BOLD);
            }
            else if (arena.wall[x + margin_x][y + margin_y] == NONE)
            {
                color_set(NONE_COL, NULL);
                addch(' ');
            }
            else
            {
                color_set(REDCYCLE_COL, NULL);
                addch('?');
            }
        }
    }

    move(0, 0);
    refresh();
}

int main(int argc, char* argv[]) {
    int fd;
    MESSAGE msg, reply;

    char name[] = "Painter";

    srand(time(NULL));

    if (name_attach(name, NULL) == -1) {
        fprintf(stderr, "Cannot attach name in painter.c!\n");
        exit(0);
    }

    /* Locate Admin who is the host of the game */
    if ((fd = name_locate("Display_Admin")) == -1) {
        fprintf(stderr, "Cannot locate name in painter.c!\n");
        exit(0);
    }

    msg.type = PAINTER_READY;

    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in painter.c!\n");
            exit(0);
        }

    if (reply.type == PAINT)
    {
        // initialize the painter
        initscr();
        start_color();
        cbreak(); // disable line buffering
        curs_set(FALSE); // hide cursor
        noecho(); // keyboard inputs shouldn't be displayed
        assigncolors();
        draw_map(reply.arena);
    }

    if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in painter.c!\n");
            exit(0);
        }

    while (reply.type != END)
    {
        draw_map(reply.arena);
        // painter the arena

        if (Send(fd, &msg, &reply, sizeof(msg), sizeof(reply)) == -1) {
            fprintf(stderr, "Cannot send message in painter.c!\n");
            exit(0);
        }
    }
    
    //reply.type == END
    draw_map(reply.arena);
    if (reply.cycleId == 0)
        fprintf(stderr, "*        RED wins the game!        *\n");
    else if (reply.cycleId == 1)
        fprintf(stderr, "*        GREEN wins the game!        *\n");
    else if (reply.cycleId == 0)
        fprintf(stderr, "*        It's a draw!        *\n");
    

    if (name_detach() == -1) {
        fprintf(stderr, "Cannot detach PAINTER name!\n");
        exit(0);
    }

    return 0;
}
