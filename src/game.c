#include "defines.h"
#include "game.h"

game_t* game_new()
{
    return calloc(1, sizeof(game_t));
}


int game_init(game_t* obj, int win_h, int win_w, int win_y, int win_x)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

	WINDOW* game_win = newwin(win_h, win_w, win_y, win_x);

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

    obj->board = game_board;
    obj->game_win = game_win;

	// Initialize tiles
	for(int i = 0; i < tilemap->width; i++)
	{
		for(int j = 0; j < tilemap->height; j++)
		{
			tile_init(ARR_2D_LOOKUP(tilemap->tiles, tilemap->width, i, j), plains_tile, 0, 0, NULL);
		}
	}

    wbkgd(game_win, COLOR_PAIR(MAIN_WIN_COLOR));

    return RET_SUCCESS;
}