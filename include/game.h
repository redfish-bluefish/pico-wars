#ifndef GAME_H_
#define GAME_H_

#include <curses.h>
#include <stdbool.h>

#include "board.h"

/* game_t - A struct holding shared global context objects for the program 
 *
 * board - Container objects representing playable game state
 * game_win - The ncurses terminal window that the program should be drawn to
 *     and contained within
 */
typedef struct game {
    game_board_t* board;
    WINDOW* game_win;
    bool resize;
} game_t;


game_t* game_new();
int game_init(game_t* obj, int win_h, int win_w, int win_y, int win_x);


#endif // GAME_H_