#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "board.h"
#include "defines.h"
#include "draw.h"
#include "game.h"

#define MIN_HEIGHT 25
#define MIN_WIDTH 80

void draw(game_t* game);
void update(game_t* game, int input_char);

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

	// Game window tries to have at least 3 characters of padding in each margin

	height = MAX(MIN_HEIGHT, LINES - (2 * WINDOW_PADDING_VERT));
	width = MAX(MIN_WIDTH, COLS - (2 * WINDOW_PADDING_HORZ));

	start_y = (LINES - height) / 2;
	start_x = (COLS - width) / 2;

	refresh();

	game_t* game = game_new();
	game_init(game, height, width, start_y, start_x);

	int c;
	c = ' ';

	do
	{
		update(game, c);
		draw(game);
	} while ((c = getch()) != 'c'); // ALT or ESC

	endwin();

	return 0;
}


void draw(game_t* game)
{
	// Resize first if necessary
	if(game->resize)
	{	

		// Resizing math
		wresize(game->game_win, MAX(MIN_HEIGHT, LINES - (2 * WINDOW_PADDING_VERT)), MAX(MIN_WIDTH, COLS - (2 * WINDOW_PADDING_HORZ)));
		mvwin(game->game_win, (LINES - MAX(MIN_HEIGHT, LINES - (2 * WINDOW_PADDING_VERT))) / 2, (COLS - MAX(MIN_WIDTH, COLS - (2 * WINDOW_PADDING_HORZ))) / 2);

		int game_win_width, game_win_height;

    	getmaxyx(game->game_win, game_win_height, game_win_width);

		wresize(game->board->board_win, game_win_height - MARGIN_BOTTOM - MARGIN_TOP - 2, (game_win_width - 2));
		mvwin(game->board->board_win, ((LINES - game_win_height) / 2) + MARGIN_TOP + 1, ((COLS - game_win_width) / 2) + 1);
		
		// Clear screen
		clear();
		wclear(game->game_win);
		wclear(game->board->board_win);
		refresh();

		game->resize = false;
	}

	box(game->game_win, 0, 0);
	wnoutrefresh(game->game_win);

	draw_board(game);

	doupdate();
}


void update(game_t* game, int input_char)
{
	game_board_t* board = game->board;
	vec_2d_t max_dim;
	int max_y, max_x;

	getmaxyx(board->board_win, max_y, max_x);

	max_dim.x = board->tilemap->width;
	max_dim.y = board->tilemap->height;

	move_selected_tile(&board->selected_tile, max_dim, input_char);
	check_move_camera(&board->tilemap_camera, &board->selected_tile, max_y, max_x);

	if(input_char == KEY_RESIZE)
	{
		game->resize = true;
	}

}