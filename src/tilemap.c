/* See tilemap.h for documentation */
#include <stdlib.h>

#include "defines.h"
#include "tilemap.h"
#include "units.h"
#include "uthash.h"


terrain_movement_t* terrain_movement_new()
{
    terrain_movement_t* ret;

    ret = calloc(1, sizeof(terrain_movement_t));
    
    return ret;
}


tile_properties_t* tile_property_new()
{
    tile_properties_t* ret;

    ret = calloc(1, sizeof(tile_properties_t));
    
    return ret;
}


tile_t* tile_new()
{
    tile_t* ret;

    ret = calloc(1, sizeof(tile_t));
    
    return ret;
}


tilemap_t* tilemap_new()
{
    tilemap_t* ret;

    ret = calloc(1, sizeof(tilemap_t));
    
    return ret;
}



int terrain_movement_init(terrain_movement_t* obj, movementType target_unit,
                          unsigned int cost)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    obj->id = target_unit;
    obj->cost = cost;

    return RET_SUCCESS;
}


int tile_property_init(tile_properties_t* obj, terrainType terrain_type, 
                       unsigned int defense_stars, char display_icon, int display_color)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    obj->id = terrain_type;
    obj->cost_table = NULL;
    obj->defense_stars = defense_stars;
    obj->graphics.icon = display_icon;
    obj->graphics.color = display_color;

    return RET_SUCCESS;
}


int tile_init(tile_t* obj, tile_properties_t* properties, int owner, 
              int capture_progress, unit_t* unit)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    obj->capture_progress = 0;
    obj->owner = PLAYER_NEUTRAL;
    obj->properties = properties;
    obj->unit = unit;

    return RET_SUCCESS;
}


int tilemap_init(tilemap_t* obj, int width, int height)
{
    if(obj == NULL)
    {
        return RET_BAD_ARG;
    }

    // Init seems to be 1D array, but is really space for 2D
    obj->height = height;
    obj->width = width;
    obj->tiles = calloc(height * width, sizeof(tile_t));

    if(obj->tiles == NULL)
    {
        return RET_ALLOC_FAIL;
    }

    return RET_SUCCESS;
}


int tilemap_add_tile(tilemap_t* tilemap, tile_properties_t* properties, int owner, 
                     int capture_progress, unit_t* unit, int x, int y)
{
    if(tilemap == NULL || properties == NULL)
    {
        return RET_BAD_ARG;
    }

    // Check if x and y are within bounds of tilemap
    if(!IN_TILEMAP_RANGE(tilemap, x, y))
    {
        return RET_BAD_ARG;
    }

    if(tilemap_get_tile(tilemap, x, y) != NULL)
    {
        return RET_ADD_CONFLICT;
    }

    tile_t* tile = ARR_2D_LOOKUP(tilemap->tiles, tilemap->width, x, y);
    return tile_init(tile, properties, owner, capture_progress, unit);
}


tile_t* tilemap_get_tile(tilemap_t* tilemap, int x, int y)
{
    if(tilemap == NULL || !IN_TILEMAP_RANGE(tilemap, x, y))
    {
        return NULL;
    }

    return ARR_2D_LOOKUP(tilemap->tiles, tilemap->width, x, y);
}


char tile_get_icon(tile_t* tile)
{
    return tile->properties->graphics.icon;
}


int tile_get_color(tile_t* tile)
{
    return tile->properties->graphics.color;
}