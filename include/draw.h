#ifndef DRAW_H_
#define DRAW_H_

#include <curses.h>

#include "board.h"
#include "game.h"

/* draw_tile - Draw a given tile to a given window
 *    Handles drawing tile terrain BG, corners, and units on the tile
 *    Function is not dependent on game context
 *
 * Parameters:
 * - d_win - The window to draw the tile to
 * - tile - Pointer to the tile to be drawn
 * - tile_pos - where the tile is in the tilemap
 * - tilemap_camera - where the tilemap camera is focused on
 *
 * Returns:
 * - Nothing
 */
void draw_tile(WINDOW* d_win, tile_t* tile, vec_2d_t* tile_pos, vec_2d_t* tilemap_camera);


/* draw_tile - Draw the game board of a given game
 *
 * Parameters:
 * - game - The game context object
 *
 * Returns:
 * - Nothing
 */
void draw_board(game_t* game);

#endif // DRAW_H_