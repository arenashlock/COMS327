#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
    int pos_x;
    int pos_y;
} player_t;

void spawn_player(single_map *map, player_t *player);

#endif