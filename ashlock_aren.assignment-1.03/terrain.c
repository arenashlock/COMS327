#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "terrain.h"

void gen_base_terrain(single_map *map){
    int r, c;

    for(r = 0; r < 21; r++){
        for(c = 0; c < 80; c++){
            // If on the edge of the map, assign the boulder terrain type
            if((c % 79) == 0 || (r % 20) == 0){
                map->terrain[r][c] = ter_boulder;
            }

            // If inside the map, assign the clearing terrain type
            else{
                map->terrain[r][c] = ter_small_grass;
            }
        }
    }
}

void fill_terrain_quad(single_map *map, int t_x, int t_y, int quad_x_mult, int quad_y_mult, ter_char_t ter_char){
    int r, c;

    // Minimum height of 3 and max height of 6
    int t_height = rand() % 4 + 3;
    // Minimum width of 5 and max width of 9
    int t_width = rand() % 5 + 5;

    // Essentially the matrix generation that we all love and know with a couple extra things...
    for(r = 0; r < t_height; r++){
        // Check if the matrix position is a border. If so, don't change it!
        if(!((t_y + (r * quad_y_mult)) <= 0 || (t_y + (r * quad_y_mult)) >= 20)){
            for(c = 0; c < t_width; c++){
                if(!((t_x + (c * quad_x_mult)) <= 0 || (t_x + (c * quad_x_mult)) >= 79)){
                    // Adding a multiplier so we can essentially generate 4 different sized quadrants to avoid square terrain patches
                    map->terrain[t_y + (r * quad_y_mult)][t_x + (c * quad_x_mult)] = ter_char;
                }
            }
        }
    }
}

void gen_terrain(single_map *map){
    int r, c;
    // Counter for the type of terrain
    int t_type;

    for(t_type = 1; t_type < 8; t_type++){
        // Can generate within 1-78, 0 and 79 are off limits (borders)
        int t_x = rand() % 78 + 1;
        // Can generate within 1-19, 0 and 20 are off limits (borders)
        int t_y = rand() % 19 + 1;
        // Character for the terrain type to be generated
        ter_char_t ter_char = ter_small_grass;

        // Generate a total of 4 regions of tall grass
        if((t_type % 4 == 1) || (t_type % 4 == 2)){
            ter_char = ter_tall_grass;
        }

        // Generate a total of 2 regions of water
        else if(t_type % 4 == 3){
            ter_char = ter_water;
        }

        // Generate a total of 1 region of boulders (mountain)
        else{
            ter_char = ter_mountain;
        }

        // The idea here is to have a middle point and treat it as the 4 different corners of a square, but each of the squares are different sizes, so it avoids making a square (most likely)

        // Fill in Quadrant 1
        fill_terrain_quad(map, t_x, t_y, -1, -1, ter_char);
        // Fill in Quadrant 2
        fill_terrain_quad(map, t_x, t_y, 1, -1, ter_char);
        // Fill in Quadrant 3
        fill_terrain_quad(map, t_x, t_y, -1, 1, ter_char);
        // Fill in Quadrant 4
        fill_terrain_quad(map, t_x, t_y, 1, 1, ter_char);
    }

    for(r = 1; r < 20; r++){
        for(c = 1; c < 79; c++){
            int tree_or_boulder_prob = rand() % 50;

            // 2% chance for a tree to spawn in a square
            if(tree_or_boulder_prob == 0){
                map->terrain[r][c] = ter_tree;
            }

            // 2% chance for a RANDOM boulder to spawn in a square
            if(tree_or_boulder_prob == 1){
                map->terrain[r][c] = ter_boulder;
            }
        }
    }
}

void gen_N_to_S(single_map *map){
    int r, c, smaller_gate_val, bigger_gate_val;
    // Want a little space between the path and the border for a potential Pokemon Center and Pokemart
    int path_correction = rand() % 15 + 3;

    if(map->n < map->s){
        smaller_gate_val = map->n;
        bigger_gate_val = map->s;
    }

    else{
        smaller_gate_val = map->s;
        bigger_gate_val = map->n;
    }

    map->terrain[0][map->n] = ter_gate;

    for(r = 1; r < path_correction; r++){
        map->terrain[r][map->n] = ter_path;
    }

    for(c = smaller_gate_val; c <= bigger_gate_val; c++){
        map->terrain[path_correction][c] = ter_path;
    }

    for(r = path_correction; r < 20; r++){
        map->terrain[r][map->s] = ter_path;
    }

    map->terrain[20][map->s] = ter_gate;
}

void gen_W_to_E(single_map *map){
    int r, c, smaller_gate_val, bigger_gate_val;
    // Want a little space between the path and the border for a potential Pokemon Center and Pokemart
    int path_correction = rand() % 74 + 3;

    if(map->w < map->e){
        smaller_gate_val = map->w;
        bigger_gate_val = map->e;
    }

    else{
        smaller_gate_val = map->e;
        bigger_gate_val = map->w;
    }

    map->terrain[map->w][0] = ter_gate;

    for(c = 1; c < path_correction; c++){
        map->terrain[map->w][c] = ter_path;
    }

    for(r = smaller_gate_val; r <= bigger_gate_val; r++){
        map->terrain[r][path_correction] = ter_path;
    }

    for(c = path_correction; c < 79; c++){
        map->terrain[map->e][c] = ter_path;
    }

    map->terrain[map->e][79] = ter_gate;
}

// Change this in the future so gates CANNOT exist no matter what

void gen_gates(single_map *map, int set_n, int set_s, int set_w, int set_e){
    // Can generate within 3-76. I am trying to space out so a Pokemon Center and Pokemart could fit
    if(set_n < 0){
        map->n = rand() % 74 + 3;
    }
    else{
        map->n = set_n;
    }

    if(set_s < 0){
        map->s = rand() % 74 + 3;
    }
    else{
        map->s = set_s;
    }

    gen_N_to_S(map);

    if(map->map_row == -200){
        map->terrain[0][map->n] = ter_boulder;
    }

    if(map->map_row == 200){
        map->terrain[20][map->s] = ter_boulder;
    }

    // Can generate within 3-17. I am trying to space out so a Pokemon Center and Pokemart could fit
    if(set_w < 0){
        map->w = rand() % 15 + 3;
    }
    else{
        map->w = set_w;
    }

    if(set_e < 0){
        map->e = rand() % 15 + 3;
    }
    else{
        map->e = set_e;
    }

    gen_W_to_E(map);

    if(map->map_col == -200){
        map->terrain[map->w][0] = ter_boulder;
    }

    if(map->map_col == 200){
        map->terrain[map->e][79] = ter_boulder;
    }
}

bool can_spawn_vert(single_map *map, int spawn_x, int spawn_y){
    int r;
    bool can = true;

    for(r = 1; r <= 2; r++){
        // If the 2 spots to the top or bottom is a road, return false (can't spawn a building there)
        if((map->terrain[spawn_y - r][spawn_x] == ter_path) || (map->terrain[spawn_y + r][spawn_x] == ter_path)){
            can = false;
            break;
        }

        // If the 2 spots to the top or bottom of the square to the right is a road, return false (can't spawn a building there)
        if((map->terrain[spawn_y - r][spawn_x + 1] == ter_path) || (map->terrain[spawn_y + r][spawn_x + 1] == ter_path)){
            can = false;
            break;
        }
    }

    return can;
}

bool can_spawn_hor(single_map *map, int spawn_x, int spawn_y){
    int c;
    bool can = true;

    for(c = 1; c <= 2; c++){
        // If the 2 spots to the left or right is a road, return false (can't spawn a building there)
        if((map->terrain[spawn_y][spawn_x - c] == ter_path) || (map->terrain[spawn_y][spawn_x + c] == ter_path)){
            can = false;
            break;
        }

        // If the 2 spots to the left or right of the square below is a road, return false (can't spawn a building there)
        if((map->terrain[spawn_y + 1][spawn_x - c] == ter_path) || (map->terrain[spawn_y + 1][spawn_x + c] == ter_path)){
            can = false;
            break;
        }
    }

    return can;
}

void gen_buildings(single_map *map){
    int r, c;
    // Can generate within 3-76
    int spawn_x = rand() % 74 + 3;
    // Can generate within 3-17
    int spawn_y = rand() % 15 + 3;

    // If the randomly selected map piece isn't a road, reselect
    if(map->terrain[spawn_y][spawn_x] != ter_path){
        gen_buildings(map);
    }

    else if(can_spawn_vert(map, spawn_x, spawn_y) == true){
        for(r = 1; r <= 2; r++){
            for(c = 0; c <= 1; c++){
                map->terrain[spawn_y + r][spawn_x + c] = ter_mart;
                map->terrain[spawn_y - r][spawn_x + c] = ter_center;
            }
        }
    }

    else if(can_spawn_hor(map, spawn_x, spawn_y) == true){
        for(r = 0; r <= 1; r++){
            for(c = 1; c <= 2; c++){
                map->terrain[spawn_y + r][spawn_x + c] = ter_mart;
                map->terrain[spawn_y + r][spawn_x - c] = ter_center;
            }
        }
    }

    else{
        gen_buildings(map);
    }
}