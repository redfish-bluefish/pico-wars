#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "defines.h"
#include "draw.h"
#include "game.h"

#define MIN_HEIGHT 25
#define MIN_WIDTH 80

void draw(game_t* game);
void update(game_t* game);


int main()
{	
	// ncurses window and color setup

	if(initscr() == NULL)
	{
		fprintf(stderr, "Could not create screen");
		exit(1);
	}

	if((start_color() == ERR) || !has_colors() || !can_change_color())
	{
		endwin();
		refresh();
		fprintf(stderr, "Could not use colors");
		exit(1);
	}

	noecho();
	raw();
	keypad(stdscr, TRUE);

	// Create game window

	int height, width;
	int start_x, start_y;

	height = MIN_HEIGHT;
	width = MIN_WIDTH;

	start_y = (LINES - height) / 2;
	start_x = (COLS - width) / 2;

	refresh();

	game_t* game = game_new();
	game_init(game, height, width, start_y, start_x);

	do
	{
		update(game);
		draw(game);
	} while (getch() != 'c'); // ALT or ESC

	endwin();

	return 0;
}


void draw(game_t* game)
{
	// Clear screen of characters to redraw
	werase(game->game_win);

	box(game->game_win, 0, 0);
	wrefresh(game->game_win);			

	draw_board(game);
}


void update(game_t* game)
{
	// Move board camera
}