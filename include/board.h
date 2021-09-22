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


typedef enum board_state {
    SB_MAIN_TILEMAP,
    SB_MINI_TILEMAP,
    SB_SELECT_MENU,
    SB_INFO_POPUP,
    SB_ERR_POPUP
} boardState;


typedef enum acycle_tilemap {
    A_BASE = 1,
    A_PATH = 2,
    A_HEALTH = 3,
    A_AMMO = 4,
    A_SUPPLY = 5
} aCycleTilemap;


typedef enum board_event_type {
    EVENT_MOVE,
    EVENT_ATTACK,
    EVENT_LOAD,
    EVENT_UNLOAD,
    EVENT_BUILD,
    EVENT_RESUPPLY
} boardEventType;


typedef struct board_event {

} board_event_t;


/* game_board_t - A struct holding the playable game state and associated data 
 *
 * tilemap - The grid of tiles the game is occuring on
 * movement_map - Grid that maps to tilemap of available spaces for selected unit to move
 * attack_map - Grid that maps to tilemap of available spaces for selected unit to attack
 * tilemap_camera - 2D vector of which tile the render should center on
 * selected_tile - 2D vector of which tile is currently selected by the player
 * board_win - The window the game board should be drawn to 
 */
typedef struct game_board {
    tilemap_t* tilemap;
    int* movement_map;
    int* attack_map;
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


/* check_move_camera - Determine if the camera needs to be moved and do so
 *     Camera needs to be moved if selected tile is fully or partially off-screen
 *     Moves camera focus a minimal amount 
 *     Assumes camera is always centered in the middle of the game window
 *
 * Parameters:
 * - camera - Pointer to vector describing the tile the camera is focused on
 * - selected_tile - Pointer to the vector describing the selected tile
 * - max_y, max_x - The maximum board window dimensions (in characters)
 * 
 * Returns:
 * - Nothing
 */
void check_move_camera(vec_2d_t* camera, vec_2d_t* selected_tile, int max_y, int max_x);


/* move_selected_tile - Move to new selected tile based on given input
 *     Controlled with the arrow keys and only changes tile if within tilemap range 
 *     and proper keys are pressed
 *
 * Parameters:
 * - selected_tile - Pointer to the vector describing the selected tile
 * - max_dim - The dimensions of the tilemap (act as max restrictions on movement)
 * - input_char - The character pressed by the player
 * 
 * Returns:
 * - Nothing
 */
void move_selected_tile(vec_2d_t* selected_tile, vec_2d_t max_dim, int input_char);


#endif // BOARD_H_




