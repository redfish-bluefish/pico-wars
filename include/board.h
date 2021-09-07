#ifndef BOARD_H_
#define BOARD_H_

#include <curses.h>

#include "tilemap.h"

/* vec_2d_t - A struct representing a 2D vector position
 *
 * x, y - horizontal and vertical coordinates
 */
typedef struct vec_2d {
    int x;
    int y;
} vec_2d_t;


/* game_board_t - A struct holding the playable game state and associated data 
 *
 * tilemap - The grid of tiles the game is occuring on
 * tilemap_camera - 2D vector of which tile the render should center on
 * selected_tile - 2D vector of which tile is currently selected by the player
 * board_win - The window the game board should be drawn to 
 */
typedef struct game_board {
    tilemap_t* tilemap;
    vec_2d_t tilemap_camera;
    vec_2d_t selected_tile;
    WINDOW* board_win;
} game_board_t;


game_board_t* game_board_new();

/* game_board_init - Initializes the values of an allocated game_board_t to the passed ones
 *
 * Parameters:
 * - obj - The allocated (but not yet initialized) game_board_t object
 * - tilemap - The tilemap this game board should use
 * - tilemap_camera_x/y - Which tile the camera should be centered on
 * - selected_tile_x/y - Which tile should be initially selected by the player
 * - game_win - The window the board should be drawn to
 * - game_win_color - Color pair ID to draw info text/BG with
 * 
 * Returns:
 * - RET_SUCCESS on success
 * - RET_BAD_ARG if obj is NULL 
 */
int game_board_init(game_board_t* obj, tilemap_t* tilemap, 
                    int tilemap_camera_x, int tilemap_camera_y,
                    int selected_tile_x, int selected_tile_y,
                    WINDOW* game_win, int game_win_color);

#endif // BOARD_H_




