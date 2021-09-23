/* See draw.h for documentation */
#include <curses.h>

#include "defines.h"
#include "draw.h"
#include "game.h"
#include "log.h"

void get_offset(WINDOW* d_win, vec_2d_t* camera, vec_2d_t* tile_pos, int* y, int* x)
{
    int max_y, max_x;
    getmaxyx(d_win, max_y, max_x);

    // Current tile position
    int y_tile = tile_pos->y;
    int x_tile = tile_pos->x;

    // Find offset by getting tile delta then multiplying by tile height and width
    int y_offset = TILE_HEIGHT * (y_tile - camera->y);
    int x_offset = TILE_WIDTH * (x_tile - camera->x);

    y_offset += (max_y - TILE_HEIGHT) / 2;
    x_offset += (max_x - TILE_WIDTH) / 2;

    *y = y_offset;
    *x = x_offset;
}



void draw_tile(WINDOW* d_win, tile_t* tile, vec_2d_t* tile_pos, vec_2d_t* tilemap_camera)
{
    int y_draw, x_draw;
    int y_offset, x_offset;
    int max_y, max_x;

    getmaxyx(d_win, max_y, max_x);
    get_offset(d_win, tilemap_camera, tile_pos, &y_offset, &x_offset);

    // Move offsets to the middle of the screen

    for(int i = 0; i < TILE_WIDTH; i++)
    {
        for(int j = 0; j < TILE_HEIGHT; j++)
        {
            y_draw = j + y_offset;
            x_draw = i + x_offset;
            if(y_draw > max_y || y_draw < 0 || x_draw > max_x || x_draw < 0)
            {
                continue;
            }
            else
            {
                wattron(d_win, COLOR_PAIR(tile_get_color(tile)));
                mvwaddch(d_win, y_draw, x_draw, tile_get_icon(tile));
                wattroff(d_win, COLOR_PAIR(tile_get_color(tile)));
            }
        }
    }

    // Draw tile corners

    wattron(d_win, COLOR_PAIR(tile_get_color(tile)));
    // Top left
    mvwaddch(d_win, y_offset, x_offset, ACS_ULCORNER);
    // Top right
    mvwaddch(d_win, y_offset, x_offset + TILE_WIDTH - 1, ACS_URCORNER);
    // Bottom left
    mvwaddch(d_win, y_offset + TILE_HEIGHT - 1, x_offset, ACS_LLCORNER);
    // Bottom right
    mvwaddch(d_win, y_offset + TILE_HEIGHT - 1, x_offset + TILE_WIDTH - 1, ACS_LRCORNER);
    wattroff(d_win, COLOR_PAIR(tile_get_color(tile)));
}


void draw_board(game_t* game)
{
    game_board_t* board = game->board;
    tilemap_t* tilemap = board->tilemap;
    WINDOW* win = board->board_win;

    // Draw tilemap
    for(int i = 0; i < tilemap->width; i++)
    {
        for(int j = 0; j < tilemap->height; j++)
        {
            log_trace("Drawing board tile at (%d, %d)", i, j);
            vec_2d_t tile_pos;
            tile_pos.x = i;
            tile_pos.y = j;
            draw_tile(win, ARR_2D_LOOKUP(tilemap->tiles, tilemap->width, i, j), 
                      &tile_pos, &board->tilemap_camera);
        }
    }

    // Draw player cursor
    int y_offset, x_offset;
    get_offset(win, &game->board->tilemap_camera, &board->selected_tile, &y_offset, &x_offset);

    wattron(win, COLOR_PAIR(CURSOR_SELECT_COLOR));
    // Top left
    mvwaddch(win, y_offset, x_offset, ACS_ULCORNER);
    // Top right
    mvwaddch(win, y_offset, x_offset + TILE_WIDTH - 1, ACS_URCORNER);
    // Bottom left
    mvwaddch(win, y_offset + TILE_HEIGHT - 1, x_offset, ACS_LLCORNER);
    // Bottom right
    mvwaddch(win, y_offset + TILE_HEIGHT - 1, x_offset + TILE_WIDTH - 1, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(CURSOR_SELECT_COLOR));


    wnoutrefresh(win);
}