#include "defines.h"
#include "game.h"

game_t* game_new()
{
    return calloc(1, sizeof(game_t));
}


int game_init(game_t* obj, game_board_t* board, WINDOW* game_win)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    obj->board = board;
    obj->game_win = game_win;

    return RET_SUCCESS;
}