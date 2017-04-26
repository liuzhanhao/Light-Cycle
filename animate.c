#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* Maximum number of keys to read in from the keyboard at once */
#define MAX_WIDTH	   200
#define MAX_HEIGHT	   100

/* Direction */
typedef enum { 
	EAST = 0, SOUTH = 1, WEST = 2, NORTH = 3
} DIRECTION;

/* Coordinate */
typedef struct { 
	int y,x;
} COORDINATE;

/* Cycle */
typedef struct {
	COORDINATE pos;
	DIRECTION dir;
}CYCLE;

/* Wall for part a */
typedef enum {
	NONE = 0, REDCYCLE = 1, LIGHT = 2, BOUNDARY = 3
}WALL;


static WALL arena[MAX_WIDTH][MAX_HEIGHT];
static CYCLE cycle;

enum {NONE_COL = 1, CYCLE_COL, LIGHT_COL, BOUNDARY_COL};	// color pairs

void assigncolors() {
	init_pair(NONE_COL, COLOR_WHITE, COLOR_BLACK);
	init_pair(CYCLE_COL, COLOR_RED, COLOR_BLACK);
	init_pair(LIGHT_COL, COLOR_RED, COLOR_BLACK);
	init_pair(BOUNDARY_COL, COLOR_WHITE, COLOR_WHITE);
}

/*
CYCLE create_cycle(COORDINATE pos, DIRECTION dir) 
{
	CYCLE c;
	c.pos = pos;
	c.dir = dir;
	return c;
}*/


void init_screen()
{
    int i, j;

    initscr();
    start_color();
    cbreak(); // disable line buffering
    curs_set(FALSE); // hide cursor
    noecho(); // keyboard inputs shouldn't be displayed
    assigncolors();

    // initialize all block to be blank
    for(i = 0; i < MAX_WIDTH; i++)
    	for (j = 0; j < MAX_HEIGHT; j++)
    		arena[i][j] = NONE;

    // initialize the boundary
    for(i = 0; i < MAX_WIDTH; i++)
    {
        arena[i][0] = BOUNDARY;
        arena[i][MAX_HEIGHT-1] = BOUNDARY;
    }

    for(i = 0; i < MAX_HEIGHT; i++)
    {
        arena[0][i] = BOUNDARY;
        arena[MAX_WIDTH-1][i] = BOUNDARY;
    }

    clear();

    // initialize the cycle
    srand(time(NULL));
    // random initial position
    COORDINATE pos = {.x = 1 + rand() % (MAX_WIDTH - 2), .y = 1 + rand() % (MAX_HEIGHT - 2)};
	cycle.pos = pos;
	cycle.dir = rand() % 4;
	arena[cycle.pos.x][cycle.pos.y] = REDCYCLE;
}

void draw_map()
{
    int x, y, maxx, maxy;
    char ch;

    getmaxyx(stdscr, maxy, maxx);
    int margin_x = cycle.pos.x - maxx / 2;
    int margin_y = cycle.pos.y - maxy / 2;

    for(y = 0; y < maxy; y++)
    {
        for(x = 0; x < maxx; x++)
        {
            move(y, x);

            if ((x + margin_x >=  MAX_WIDTH) | (x + margin_x < 0) | (y + margin_y >= MAX_HEIGHT) | (y + margin_y < 0))
            {
            	color_set(NONE_COL, NULL);
                ch = ' ';
            }
            else if (arena[x + margin_x][y + margin_y] == NONE)
            {
            	color_set(NONE_COL, NULL);
                ch = ' ';
            }
            else if (arena[x + margin_x][y + margin_y] == REDCYCLE)
            {
            	color_set(CYCLE_COL, NULL);
                ch = '@';
            }
            else if (arena[x + margin_x][y + margin_y] == LIGHT)
            {
            	color_set(LIGHT_COL, NULL);
                ch = 'L';
            }
            else if (arena[x + margin_x][y + margin_y] == BOUNDARY)
            {
            	color_set(BOUNDARY_COL, NULL);
                ch = ' ';
            }
            else
            {
            	color_set(CYCLE_COL, NULL);
                ch = '?';
            }

            addch(ch);
        }
    }
    move(0, 0);
    refresh();
}

// remain_dir = EAST = 1, SOUTH = 2, WEST = 3, NORTH = 4
int move_cycle(CYCLE* c)
{
    DIRECTION dir = c->dir;
    arena[c->pos.x][c->pos.y] = LIGHT;

    if (dir == EAST)
    {
        if (arena[c->pos.x + 1][c->pos.y] != NONE)
        {
            if (arena[c->pos.x][c->pos.y+1] == NONE)
            {
                c->dir = SOUTH;
                return move_cycle(c);
            }
            else if (arena[c->pos.x-1][c->pos.y] == NONE)
            {
                c->dir = WEST;
                return move_cycle(c);
            }
            else if (arena[c->pos.x][c->pos.y-1] == NONE)
            {
                c->dir = NORTH;
                return move_cycle(c);
            }
            return 0;
        }
    	arena[++c->pos.x][c->pos.y] = REDCYCLE;
    }
    else if (dir == SOUTH)
    {
        if (arena[c->pos.x][c->pos.y + 1] != NONE)
        {
            if (arena[c->pos.x + 1][c->pos.y] == NONE)
            {
                c->dir = EAST;
                return move_cycle(c);
            }
            else if (arena[c->pos.x-1][c->pos.y] == NONE)
            {
                c->dir = WEST;
                return move_cycle(c);
            }
            else if (arena[c->pos.x][c->pos.y-1] == NONE)
            {
                c->dir = NORTH;
                return move_cycle(c);
            }
            return 0;
        }
    	arena[c->pos.x][++c->pos.y] = REDCYCLE;
    }
    else if (dir == WEST)
    {
        if (arena[c->pos.x - 1][c->pos.y] != NONE)
        {
            if (arena[c->pos.x][c->pos.y+1] == NONE)
            {
                c->dir = SOUTH;
                return move_cycle(c);
            }
            else if (arena[c->pos.x + 1][c->pos.y] == NONE)
            {
                c->dir = EAST;
                return move_cycle(c);
            }
            else if (arena[c->pos.x][c->pos.y-1] == NONE)
            {
                c->dir = NORTH;
                return move_cycle(c);
            }
            return 0;
        }
    	arena[--c->pos.x][c->pos.y] = REDCYCLE;
    }
    else if (dir == NORTH)
    {
        if (arena[c->pos.x][c->pos.y - 1] != NONE)
        {
            if (arena[c->pos.x][c->pos.y+1] == NONE)
            {
                c->dir = SOUTH;
                return move_cycle(c);
            }
            else if (arena[c->pos.x-1][c->pos.y] == NONE)
            {
                c->dir = WEST;
                return move_cycle(c);
            }
            else if (arena[c->pos.x + 1][c->pos.y] == NONE)
            {
                c->dir = EAST;
                return move_cycle(c);
            }
            return 0;
        }
    	arena[c->pos.x][--c->pos.y] = REDCYCLE;
    }

    clear();
   	draw_map();
    return 1;
}

// check if the cycle can move to that direction
bool check(CYCLE c, DIRECTION dir)
{
    if (dir == EAST)
        return arena[c.pos.x+1][c.pos.y] == NONE;
    else if (dir == SOUTH)
        return arena[c.pos.x][c.pos.y+1] == NONE;
    else if (dir == WEST)
        return arena[c.pos.x-1][c.pos.y] == NONE;
    else if (dir == NORTH)
        return arena[c.pos.x][c.pos.y-1] == NONE;
    return false;
}

void pick_an_direction(CYCLE *c)
{
    int x = c->pos.x, y = c->pos.y;
    // if all direction is unreachable, break
    if (arena[x+1][y] != NONE || arena[x][y+1] != NONE || arena[x-1][y] != NONE || arena[x][y] != NONE)
    {
        DIRECTION old_dir = c->dir;
        DIRECTION new_dir = rand() % 4;
        while (new_dir == old_dir || !check(cycle, new_dir))
        {
            new_dir = rand() % 4;
        }
        c->dir = new_dir;
    }
}


int main(int argc, char *argv[]) 
{

	init_screen();
	draw_map();
    int flag = 1;
    while(flag)
    {
        usleep(50000);
        flag =  move_cycle(&cycle);
        //judge if next position is a wall
        if (rand() % 10 == 0)
            pick_an_direction(&cycle);
    }

	sleep(3);
	endwin();
    printf("Game Over!\n");
	return 0;
}