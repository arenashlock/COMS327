#include <stdio.h>
#include <stdlib.h>

#include "terrain.h"
#include "player.h"

void spawn_player(single_map *map, player_t *player){
    // Can generate within 1-78
    int spawn_x = rand() % 78 + 1;
    // Can generate within 1-19
    int spawn_y = rand() % 19 + 1;

    // If the randomly selected map piece isn't a road, reselect
    if(map->terrain[spawn_y][spawn_x] != ter_path){
        spawn_player(map, player);
    }

    // The randomly selected map piece IS a road, so "spawn" the player there
    else{
        player->pos_x = spawn_x;
        player->pos_y = spawn_y;
    }
}