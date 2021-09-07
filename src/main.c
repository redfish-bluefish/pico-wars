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
#define MAIN_WIN_COLOR 1


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

	WINDOW* game_win = newwin(height, width, start_y, start_x);

  	init_pair(MAIN_WIN_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(CURSOR_SELECT_COLOR, COLOR_YELLOW, COLOR_BLUE);
	init_pair(PLAIN_TILE_COLOR, COLOR_WHITE, COLOR_GREEN);

	// initialize game and board

	tile_properties_t* plains_tile = tile_property_new();
	tile_property_init(plains_tile, TER_PLAIN, 0, '.', PLAIN_TILE_COLOR);

	tilemap_t* tilemap = tilemap_new();
	tilemap_init(tilemap, 3, 2);

	game_board_t* game_board = game_board_new();
	game_board_init(game_board, tilemap, 0, 0, 0, 0, game_win, MAIN_WIN_COLOR);

	game_t* game = game_new();
	game_init(game, game_board, game_win);

	// Initialize tiles
	for(int i = 0; i < tilemap->width; i++)
	{
		for(int j = 0; j < tilemap->height; j++)
		{
			tile_init(ARR_2D_LOOKUP(tilemap->tiles, tilemap->width, i, j), plains_tile, 0, 0, NULL);
		}
	}

    wbkgd(game_win, COLOR_PAIR(MAIN_WIN_COLOR));


	box(game_win, 0, 0);
	wrefresh(game_win);			

	draw_board(game);

	// Draw box on window


	getch();

	endwin();

	return 0;
}