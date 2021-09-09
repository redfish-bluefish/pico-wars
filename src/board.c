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


void move_selected_tile(vec_2d_t* selected_tile, vec_2d_t max_dim, int input_char)
{
    // Selected tile is only moved if new tile is within bounds
    // Otherwise nothing happens
    switch(input_char)
    {
        case KEY_LEFT:
            if(selected_tile->x > 0)
            {
                selected_tile->x -= 1;
            }
            break;

        case KEY_RIGHT:
            if(selected_tile->x < max_dim.x - 1)
            {
                selected_tile->x += 1;
            }
            break;

        case KEY_UP:
            if(selected_tile->y > 0)
            {
                selected_tile->y -= 1;
            }
            break;

        case KEY_DOWN:
            if(selected_tile->y < max_dim.y - 1)
            {
                selected_tile->y += 1;
            }
            break;

        default:
            // Do nothing
            break;
    }
}


void check_move_camera(vec_2d_t* camera, vec_2d_t* selected_tile, int max_y, int max_x)
{
    vec_2d_t tile_delta;

    tile_delta.x = camera->x - selected_tile->x;
    tile_delta.y = camera->y - selected_tile->y;

    // Relies on the fact that the camera tile is always centered in the game window
    // Camera too far left (tile delta negative)
    while((tile_delta.x * TILE_WIDTH) - (TILE_WIDTH / 2) < -(max_x / 2))
    {
        tile_delta.x += 1;
        camera->x += 1;
    }
    // Camera too far right (tile delta positive)
    while((tile_delta.x * TILE_WIDTH) + (TILE_WIDTH / 2) > (max_x / 2))
    {
        tile_delta.x -= 1;
        camera->x -= 1;
    }
    // Camera too far up (tile delta negative)
    while((tile_delta.y * TILE_HEIGHT) - (TILE_HEIGHT / 2) < -(max_y / 2))
    {
        tile_delta.y += 1;
        camera->y += 1;
    }
    // Camera too far down (tile delta positive)
    while((tile_delta.y * TILE_HEIGHT) + (TILE_HEIGHT / 2) > (max_y / 2))
    {
        tile_delta.y -= 1;
        camera->y -= 1;
    }
}