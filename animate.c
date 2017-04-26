#include <ncurses.h>
#include <unistd.h>

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
    COORDINATE pos = {.x = MAX_WIDTH / 2, .y = MAX_HEIGHT - 2};
	//cycle = create_cycle(pos, EAST);
	cycle.pos = pos;
	cycle.dir = EAST;
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

            if ((x + margin_x >=  MAX_WIDTH) | (y + margin_y >= MAX_HEIGHT))
            {
            	color_set(NONE_COL, NULL);
                ch = ' ';
            }
            else if (arena[x + margin_x][y + margin_y] == NONE)
            {
            	color_set(NONE_COL, NULL);
                ch = 'N';
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

void move_cycle(CYCLE c)
{
    DIRECTION dir = c.dir;

    if (dir == EAST)
    {
    	arena[c.pos.x + 1][c.pos.y] = REDCYCLE;
    	arena[c.pos.x][c.pos.y] = LIGHT;
    }
    else if (dir == SOUTH)
    {
    	arena[c.pos.x][c.pos.y+1] = REDCYCLE;
    	arena[c.pos.x][c.pos.y] = LIGHT;
    }
    else if (dir == WEST)
    {
    	arena[c.pos.x-1][c.pos.y] = REDCYCLE;
    	arena[c.pos.x][c.pos.y] = LIGHT;
    }
    else if (dir == NORTH)
    {
    	arena[c.pos.x][c.pos.y-1] = REDCYCLE;
    	arena[c.pos.x][c.pos.y] = LIGHT;
    }

    //clear();
   	draw_map();
}


int main(int argc, char *argv[]) 
{

	init_screen();
	draw_map();
	sleep(2);
	move_cycle(cycle);

	sleep(10);
	endwin();

	return 0;
}