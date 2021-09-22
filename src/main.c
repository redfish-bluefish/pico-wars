#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "board.h"
#include "defines.h"
#include "draw.h"
#include "game.h"
#include "log.h"

#define MIN_HEIGHT 25
#define MIN_WIDTH 80

void resize_clear(game_t* game);
void draw(game_t* game);
void update(game_t* game, int input_char);
char* err_to_str(int err);

int handle_popup(game_t* game);

typedef int (*popup_handler)(game_t* game);

static popup_handler p_handlers[1];

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


	FILE* log_file = fopen("log.txt", "w");
	if(log_file == NULL)
	{
		fprintf(stderr, "Failed to create/open log file, quitting...");
		exit(1);
	}

	int rt;

	log_set_quiet(true);
	log_set_level(LOG_TRACE);
	log_add_fp(log_file, LOG_TRACE);
	log_debug("test log!");

	noecho();
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);

	game_t* game = game_new();
	if((rt = game_init(game)) != RET_SUCCESS)
	{
		log_fatal(err_to_str(rt));
		endwin();
		exit(1);
	}
	resize_clear(game);

	// Primary loop
	int c;
	c = ' ';

	do
	{
		update(game, c);
		draw(game);
	} while ((c = getch()) != 'c'); // ALT or ESC

	fclose(log_file);
	endwin();

	return 0;
}


void resize_clear(game_t* game)
{
	// Game window
	RESIZE_WIN(game->game_win, GAME_WIN_H, GAME_WIN_W, GAME_WIN_Y, GAME_WIN_X);

	// Board window
	int game_win_width, game_win_height;

	// must do this step AFTER resizing game window as board_win relies on game win dims
	getmaxyx(game->game_win, game_win_height, game_win_width);

	RESIZE_WIN(game->board->board_win, BOARD_WIN_H(game_win_height), 
			   BOARD_WIN_W(game_win_width), BOARD_WIN_Y(game_win_height), 
			   BOARD_WIN_X(game_win_width));
	

	// Clear screen to refresh everything
	clear();
	wclear(game->game_win);
	wclear(game->board->board_win);
	refresh();

}


void draw(game_t* game)
{
	log_trace("In draw loop");

	// Resize first if necessary
	if(game->resize)
	{	
		resize_clear(game);
		game->resize = false;
	}

	box(game->game_win, 0, 0);
	wnoutrefresh(game->game_win);

	draw_board(game);

	doupdate();
}


void update(game_t* game, int input_char)
{
	log_trace("In update loop");

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


char* err_to_str(int err)
{
	switch(err)
	{
		case(RET_BAD_ARG):
			return "ERROR: Recieved a bad argument";
		case(RET_ADD_CONFLICT):
			return "ERROR: Conflict when adding to structure";
		case(RET_ALLOC_FAIL):
			return "ERROR: Memory allocation failed";
		default:
			return "Unknown error";
	}
}