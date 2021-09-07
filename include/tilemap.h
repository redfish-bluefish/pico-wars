#ifndef TILEMAP_H_
#define TILEMAP_H_

/*
 *  This file contains structs used in representing map state and
 *  functions used initialize definitions 
 * 
 *  Can be expanded to include functions to read configuration files
 *  for custom map properties
 */

#include "uthash.h"

#include "units.h"

/* 
 *  Defining tile types and properties
 */

typedef enum terrainType {
    TER_ROAD,
    TER_PLAIN,
    TER_WOOD,
    TER_MOUNTAIN,
    TER_RIVER,
    TER_BRIDGE,
    TER_BEACH,
    TER_SEA,
    TER_REEF,
    TER_CITY,
    TER_FACTORY,
    TER_AIRPORT,
    TER_PORT,
    TER_HQ
} terrainType;


/* terrain_movement_t - key-value mapping for a specific movement type
 *     and movement cost respectively, used in the context of movement on 
 *     a specific terrain type 
 * 
 * id - The movement type 
 * cost - Cost of movement (in movement points)
 * hh - [Reserved by uthash to form hashtable structure]
 */
typedef struct terrain_movement {
    movementType id;
    unsigned int cost;
    UT_hash_handle hh;
} terrain_movement_t;


typedef struct tile_graphics {
    char icon;
    int color;
} tile_graphics_t;


/* tile_properties_t - The various immutable properties of a general tile type
 *     Can be referenced directly (for read-only) or through hashtable lookup
 *     (for read or write)
 * 
 *  These should be created ONCE on game initialization in a global table
 *  and referenced by specific tiles over the course of a game
 * 
 * id - The tile type 
 * cost_table - A hashtable containing movement costs for various types of 
 *     movement on this specific tile type
 * defense_stars - The number of defense stars this tile type has
 * icon - The character that should be drawn on the board for this type of tile
 * hh - [Reserved by uthash to form hashtable structure]
 */
typedef struct tile_properties {
    terrainType id;
    terrain_movement_t* cost_table;
    unsigned int defense_stars;
    tile_graphics_t graphics;
    UT_hash_handle hh;
} tile_properties_t;


/* tile_t - A specific tile on the game board
 *
 * properties - Pointer to the properties of this tile (FOR READ-ONLY)
 * owner - Which player owns the property on this tile (if applicable)
 * capture_progress - Capture progress of the property if applicable
 *      Ranges between 0 and 20--neutral at 0 and owned at 20
 *      Should a player own the property and it moves to 0 HP, then move to neutral
 *      Vice versa for neutral to player-owned
 * unit - Pointer to the unit on this tile (NULL if no such unit exists)
 */
typedef struct tile {
    tile_properties_t* properties;
    int owner;
    int capture_progress;
    unit_t* unit;
} tile_t;


/* tilemap_t - A rectangular grid of tiles representhing the playing field
 *
 * tiles - Pointer to a 2D array of tiles
 * width - The width of the tilemap in tiles
 * height - The height of the tilemap in tiles
 */
typedef struct tilemap {
    tile_t* tiles;
    unsigned int width;
    unsigned int height;
} tilemap_t;


/* Function Prototypes */

terrain_movement_t* terrain_movement_new();
tile_properties_t* tile_property_new();
tile_t* tile_new();
tilemap_t* tilemap_new(); 


/* struct init functions - allocates memory and initializes structures to given values
 * 
 * Any fields not passed are initialized to NULL or 0 (unless specified otherwise)
 * 
 * Returns either the successfully initialized structure, or NULL on failure
 */ 

int terrain_movement_init(terrain_movement_t* obj, movementType target_unit,
                          unsigned int cost);
int tile_property_init(tile_properties_t* obj, terrainType terrain_type, 
                       unsigned int defense_stars, char display_icon, int display_color);
int tile_init(tile_t* obj, tile_properties_t* properties, int owner, 
              int capture_progress, unit_t* unit);
int tilemap_init(tilemap_t* obj, int width, int height); 
// Also initializes width * height large tile array to NULL


char tile_get_icon(tile_t* tile);
int tile_get_color(tile_t* tile);


// UPDATE COMMENT
/* tilemap_add_tile - Add the passed tile to the tilemap at position x,y
 *
 * tilemap - The tilemap to be added to
 * tile - The tile to be added (should be initialized)
 * x,y - The position to add the tile into
 * 
 * Returns:
 * - RET_SUCCESS on success
 * - RET_BAD_ARG if tilemap or tile is NULL, or x,y are out of range
 * - RET_ADD_CONFLICT if a tile already exists at the given x,y
 */
int tilemap_add_tile(tilemap_t* tilemap, tile_properties_t* properties, int owner, 
                     int capture_progress, unit_t* unit, int x, int y);


/* tilemap_get_tile - Get the tile at position x,y if it exists
 *
 * tilemap - The tilemap pull from
 * x,y - The position to get the tile from
 * 
 * Returns:
 * - A pointer to the tile on success
 * - NULL if tilemap is NULL or x or y are bad (i.e. out of range)
 */
tile_t* tilemap_get_tile(tilemap_t* tilemap, int x, int y);


/* tilemap_property_add_movement - Add a movement cost entry to a specific tile type
 *
 * movement_entry - The movement cost entry to be added
 * tile_type - The tile type to be given the movement entry
 * 
 * Returns:
 * - RET_SUCCESS on success
 * - RET_BAD_ARG if movement_entry or tile_type is NULL
 * - RET_ADD_CONFLICT if a cost entry for the specific movement type already exists
 */
int tile_property_add_movement(terrain_movement_t* movement_entry,
                               tile_properties_t* tile_type);

#endif // TILEMAP_H_