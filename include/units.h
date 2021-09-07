#ifndef UNITS_H_
#define UNITS_H_
/*
 *  This file contains structs used in representing unit state and
 *  properties, along with functions used initialize definitions 
 * 
 *  Can be expanded to include functions to read configuration files
 *  for custom unit properties
 */
#include <stdbool.h>


#include "uthash.h"
#include "utlist.h"

typedef enum movementType {
    MV_INFANTRY,
    MV_MECH,
    MV_TIRES,
    MV_TREAD,
    MV_AIR,
    MV_SHIP,
    MV_SHIP_TRANSPORT
} movementType;


typedef enum unitType {
    U_INFANTRY,
    U_MECH,
    U_RECON,
    U_TANK,
    U_MED_TANK,
    U_ARTILLERY,
    U_ROCKETS,
    U_ANTI_AIR,
    U_SAM,
    U_B_COPTER,
    U_FIGHTER,
    U_BOMBER,
    U_CRUISER,
    U_SUB,
    U_BSHIP
} unitType;


/* damage_table_t - key-value mapping for the damage a specific weapon type can do
 *      to a specific unit type
 * 
 * id - The unit type this weapon damage is targeting
 * base_damage - The damage this weapon does before modifiers (between 0 and 100)
 * min_range - The minimum range in tiles of this weapon (inclusive)
 * max_range - The maximum range in tiles of this weapon (inclusive)
 * hh - [Reserved by uthash to form hashtable structure]
 */
typedef struct damage_table {
    unitType id;
    int base_damage;
    int min_range;
    int max_range;
    UT_hash_handle hh;
} damage_table_t;


/* weapon_properties_t - The various immutable properties of a general weapon type
 *     Can be referenced directly (for read-only) or through hashtable lookup
 *     (for read or write)
 * 
 *  These should be created ONCE on game initialization in a global table
 *  and referenced by specific weapons over the course of a game
 * 
 * id - A string representing the name of this weapon
 * damage_table_t - A pointer to the damage hashtable for units this weapon can target
 *      If a unit type is not in the hashtable, this weapon cannot target it
 * max_ammo - The maximum ammo capacity of this weapon (in number of shots)
 * hh - [Reserved by uthash to form hashtable structure]
 */
typedef struct weapon_properties {
    char* id;
    damage_table_t* damage_table;
    int max_ammo;
    UT_hash_handle hh;
} weapon_properties_t;


/* unit_weapon_t - A specific weapon that a specific unit has
 *      Can be referenced as a singly linked list
 * 
 * properties - A pointer to the immutable properties of this weapon
 * ammo - The current number of shots this weapon type has remaining
 * next - Pointer to the next weapon this unit has [used by utlist]
 */
typedef struct unit_weapon {
    weapon_properties_t* properties;
    int ammo;
    struct unit_weapon* next;
} unit_weapon_t;


/* unit_properties_t - The various immutable properties of a general unit type
 *     Can be referenced directly (for read-only) or through hashtable lookup
 *     (for read or write)
 *     Can be referenced as a singly linked list
 * 
 *  These should be created ONCE on game initialization in a global table/list
 *  and referenced by specific units over the course of a game
 * 
 * id - The unit type
 * weapon_list - A list of the weapons types this unit should have
 * can_transport - A pointer to a list of unit types this unit can transport
 * 
 * movement_type - The movement type this unit uses
 * base_movement - The number of movement points this unit has each turn (in tiles)
 * max_supply - The maximum number of tiles this unit can move between supplies 
 *      and spawning (in tiles)
 * vision_range - The base number of tiles this unit can see in FoW mode 
 * cost - The amount of resources this unit costs to build
 * 
 * hh - [Reserved by uthash to form hashtable structure]
 * next - Pointer to the next unit in the list [used by utlist]
 */
typedef struct unit_properties {
    unitType id;
    weapon_properties_t* weapon_list;
    unitType* can_transport;

    movementType movement_type;
    int base_movement;
    int max_supply;
    int vision_range;
    int cost;

    UT_hash_handle hh;
    struct unit_properties* next;
} unit_properties_t;


/* unit_t - A specific unit on the game board
 * 
 * properties - The immutable properties of this unit including its type
 * health - The amount of health this unit has left, ranges between 0 and 100 (0% and 100%)
 * movement_points - The amount of movement points this unit has remaining this turn
 * supply - The amount of tiles this unit can move before requiring resupply
 * being_transported - Boolean indicating whether another unit is currently transporting
 *      this unit
 * transporting - A pointer to the unit that this unit is transporting (NULL if none)
 */
typedef struct unit {
    unit_properties_t* properties;
    int health;
    int movement_points;
    int supply;
    bool being_transported;
    struct unit* transporting;
} unit_t;

#endif // UNITS_H_