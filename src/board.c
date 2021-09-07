#include <curses.h>

#include "defines.h"
#include "board.h"


game_board_t* game_board_new()
{
    return calloc(1, sizeof(game_board_t));
}


int game_board_init(game_board_t* obj, tilemap_t* tilemap, 
                    int tilemap_camera_x, int tilemap_camera_y,
                    int selected_tile_x, int selected_tile_y,
                    WINDOW* game_win, int game_win_color)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    int game_win_width, game_win_height;

    getmaxyx(game_win, game_win_height, game_win_width);

    obj->tilemap = tilemap;
    obj->tilemap_camera.x = tilemap_camera_x;
    obj->tilemap_camera.y = tilemap_camera_y;
    obj->selected_tile.x = selected_tile_x;
    obj->selected_tile.y = selected_tile_y;

    // Game board is buffered by top and bottom margins PLUS
    // Fits within game win width-wise
    // Additional extra +1 to margins for external border
    obj->board_win = newwin(game_win_height - MARGIN_BOTTOM - MARGIN_TOP - 2, (game_win_width - 2),
                            ((LINES - game_win_height) / 2) + MARGIN_TOP + 1, ((COLS - game_win_width) / 2) + 1);
    wbkgd(obj->board_win, COLOR_PAIR(game_win_color));

    return RET_SUCCESS;
}