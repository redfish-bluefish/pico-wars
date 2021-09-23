#include "defines.h"
#include "game.h"
#include "log.h"

game_t* game_new()
{
    return calloc(1, sizeof(game_t));
}


int game_init(game_t* obj)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

	int rt;

	obj->resize = false;
	WINDOW* game_win = newwin(0, 0, 0, 0);

  	init_pair(MAIN_WIN_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(CURSOR_SELECT_COLOR, COLOR_YELLOW, COLOR_BLUE);

	// Tile colors
	init_pair(PLAIN_TILE_COLOR, COLOR_WHITE, COLOR_GREEN);

	// initialize game and board

	tile_properties_t* plains_tile = tile_property_new();
	tile_property_init(plains_tile, TER_PLAIN, 0, '.', PLAIN_TILE_COLOR);

	tilemap_t* tilemap = tilemap_new();
	tilemap_init(tilemap, 20, 10);

	game_board_t* game_board = game_board_new();
	game_board_init(game_board, tilemap, 0, 0, 0, 0, game_win, MAIN_WIN_COLOR);

    obj->board = game_board;
    obj->game_win = game_win;

	// Initialize tiles
	for(int i = 0; i < tilemap->width; i++)
	{
		for(int j = 0; j < tilemap->height; j++)
		{
			if((rt = tilemap_add_tile(tilemap, plains_tile, 0, 0, NULL, i, j)) != RET_SUCCESS)
			{
				log_fatal("Failed to add tile to (%d, %d)", i, j);
				return rt;
			}
		}
	}

    wbkgd(game_win, COLOR_PAIR(MAIN_WIN_COLOR));

    return RET_SUCCESS;
}