#ifndef CHARACTER_H
# define CHARACTER_H

# include <stdint.h>

# include "poke327.h"

#define DIJKSTRA_PATH_MAX (INT_MAX / 2)

extern const char *char_type_name[num_character_types];

extern int32_t move_cost[num_character_types][num_terrain_types];

/* character is defined in poke327.h to allow an instance of character
 * in world without including character.h in poke327.h                 */

int32_t cmp_char_turns(const void *key, const void *with);
void delete_character(void *v);
void pathfind(map *m);

extern void (*move_func[num_movement_types])(character *, pair_t);

int pc_move(char);

#endif
