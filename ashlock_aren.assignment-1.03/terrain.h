#include <stdint.h>

#ifndef TERRAIN_H
#define TERRAIN_H

typedef enum{
    ter_small_grass,
    ter_tall_grass,
    ter_water,
    ter_boulder,
    ter_mountain,
    ter_tree,
    ter_path,
    ter_gate,
    ter_mart,
    ter_center
} ter_char_t;

typedef struct{
    int ter_cost[21][80];

    int n;
    int s;
    int w;
    int e;

    // Not necessary, but makes it easier when printing the coordinates
    int map_row;
    int map_col;

    ter_char_t terrain[21][80];
} single_map;

void gen_base_terrain(single_map *map);
void gen_terrain(single_map *map);
void gen_gates(single_map *map, int set_n, int set_s, int set_w, int set_e);
void gen_buildings(single_map *map);

#endif