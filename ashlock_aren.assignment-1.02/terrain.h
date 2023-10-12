#ifndef TERRAIN_H
#define TERRAIN_H

struct single_map{
    int n;
    int s;
    int w;
    int e;

    // Not necessary, but makes it easier when printing the coordinates
    int map_row;
    int map_col;

    char terrain[21][80];
};

void gen_base_terrain(struct single_map *map);
void gen_terrain(struct single_map *map);
void gen_gates(struct single_map *map, int set_north_gate, int set_south_gate, int set_west_gate, int set_east_gate);
void gen_buildings(struct single_map *map);
void print_map(struct single_map *map);

#endif