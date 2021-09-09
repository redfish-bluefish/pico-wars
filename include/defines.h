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