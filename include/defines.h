#ifndef DEFINES_H_
#define DEFINES_H_

#include <curses.h>

/* taken from dan04's answer in 
 * https://stackoverflow.com/questions/3437404/min-and-max-in-c 
 */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define ARR_2D_LOOKUP(arr, width, x, y) ((arr) + ((x) + ((y) * (width))))

#define IN_TILEMAP_RANGE(tilemap, x, y) ((x) < (tilemap)->width && (x) >= 0 && (y) < (tilemap)->height && (y) >= 0)

#define TILE_WIDTH 5
#define TILE_HEIGHT 3

#define WINDOW_PADDING_HORZ 3
#define WINDOW_PADDING_VERT 3

#define MARGIN_TOP 3
#define MARGIN_BOTTOM 3
#define MARGIN_RIGHT 1
#define MARGIN_LEFT 1

// I apologize for this monstrosity

#define RESIZE_WIN(win, h, w, y, x) do{ wresize((win), (h), (w)); mvwin((win), (y), (x)); } while(0)

#define GAME_WIN_H (MAX(MIN_HEIGHT, LINES - (2 * WINDOW_PADDING_VERT)))
#define GAME_WIN_W (MAX(MIN_WIDTH, COLS - (2 * WINDOW_PADDING_HORZ)))
#define GAME_WIN_Y ((LINES - MAX(MIN_HEIGHT, LINES - (2 * WINDOW_PADDING_VERT))) / 2)
#define GAME_WIN_X ((COLS - MAX(MIN_WIDTH, COLS - (2 * WINDOW_PADDING_HORZ))) / 2)

// Game board is buffered by top and bottom margins PLUS
// Additional extra +1 to margins for external border
// Fits within game win width-wise

#define BOARD_WIN_H(gw_h) ((gw_h) - MARGIN_BOTTOM - MARGIN_TOP - 2)
#define BOARD_WIN_W(gw_w) ((gw_w) - 2)
#define BOARD_WIN_Y(gw_h) (((LINES - (gw_h)) / 2) + MARGIN_TOP + 1)
#define BOARD_WIN_X(gw_w) (((COLS - (gw_w)) / 2) + 1)

/* Tile Color Codes */

#define MAIN_WIN_COLOR 1
#define CURSOR_SELECT_COLOR 2

#define ROAD_TILE_COLOR 10
#define PLAIN_TILE_COLOR 11
#define WOOD_TILE_COLOR 12
#define WATER_TILE_COLOR 13
#define BEACH_TILE_COLOR 14
#define BRIDGE_TILE_COLOR 15
#define CITY_TILE_COLOR 16

#define COLOR_GRAY COLOR_MAGENTA

#define RET_SUCCESS 0
#define RET_BAD_ARG 1
#define RET_ADD_CONFLICT 2
#define RET_ALLOC_FAIL 3

#define PLAYER_NEUTRAL 0
#define PLAYER_1 1
#define PLAYER_2 2
#define PLAYER_3 3
#define PLAYER_4 4

#endif // DEFINES_H_