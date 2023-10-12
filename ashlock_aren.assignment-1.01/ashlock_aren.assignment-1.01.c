#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void generate_map_base(char map[21][80]){
    int r, c;

    for(r = 0; r < 21; r++){
        for(c = 0; c < 80; c++){
            // If on the edge of the map, assign the boulder terrain type
            if((c % 79) == 0 || (r % 20) == 0){
                map[r][c] = '%';
            }

            // If inside the map, assign the clearing terrain type
            else{
                map[r][c] = '.';
            }
        }
    }
}

void fill_terrain_quadrant(char map[21][80], int terrain_x, int terrain_y, int quad_x_mult, int quad_y_mult, char terrain_char){
    int r, c;

    // Minimum height of 3 and max height of 6
    int terrain_height = rand() % 4 + 3;
    // Minimum width of 5 and max width of 9
    int terrain_width = rand() % 5 + 5;

    // Essentially the matrix generation that we all love and know with a couple extra things...
    for(r = 0; r < terrain_height; r++){
        // Check if the matrix position is a border. If so, don't change it!
        if(!((terrain_y + (r * quad_y_mult)) <= 0 || (terrain_y + (r * quad_y_mult)) >= 20)){
            for(c = 0; c < terrain_width; c++){
                if(!((terrain_x + (c * quad_x_mult)) <= 0 || (terrain_x + (c * quad_x_mult)) >= 79)){
                    // Adding a multiplier so we can essentially generate 4 different sized quadrants to avoid square terrain patches
                    map[terrain_y + (r * quad_y_mult)][terrain_x + (c * quad_x_mult)] = terrain_char;
                }
            }
        }
    }
}

void generate_terrain(char map[21][80]){
    int r, c;
    // Counter for the type of terrain
    int type_of_terrain;

    for(type_of_terrain = 1; type_of_terrain < 8; type_of_terrain++){
        // Can generate within 1-78, 0 and 79 are off limits (borders)
        int terrain_x = rand() % 78 + 1;
        // Can generate within 1-19, 0 and 20 are off limits (borders)
        int terrain_y = rand() % 19 + 1;
        // Character for the terrain type to be generated
        char terrain_char = '.';

        // Generate a total of 4 regions of tall grass
        if((type_of_terrain % 4 == 1) || (type_of_terrain % 4 == 2)){
            terrain_char = ':';
        }

        // Generate a total of 2 regions of water
        else if(type_of_terrain % 4 == 3){
            terrain_char = '~';
        }

        // Generate a total of 1 region of boulders
        else{
            terrain_char = '%';
        }

        // The idea here is to have a middle point and treat it as the 4 different corners of a square, but each of the squares are different sizes, so it avoids making a square (most likely)

        // Fill in Quadrant 1
        fill_terrain_quadrant(map, terrain_x, terrain_y, -1, -1, terrain_char);
        // Fill in Quadrant 2
        fill_terrain_quadrant(map, terrain_x, terrain_y, 1, -1, terrain_char);
        // Fill in Quadrant 3
        fill_terrain_quadrant(map, terrain_x, terrain_y, -1, 1, terrain_char);
        // Fill in Quadrant 4
        fill_terrain_quadrant(map, terrain_x, terrain_y, 1, 1, terrain_char);
    }

    for(r = 1; r < 20; r++){
        for(c = 1; c < 79; c++){
            int chance_for_tree_or_boulder = rand() % 50;

            // 2% chance for a tree to spawn in a square
            if(chance_for_tree_or_boulder == 0){
                map[r][c] = '^';
            }

            // 2% chance for a RANDOM boulder to spawn in a square
            if(chance_for_tree_or_boulder == 1){
                map[r][c] = '%';
            }
        }
    }
}

void generate_N_to_S_path(char map[21][80], int N_entrance, int S_entrance){
    int r, c, smaller_gate_val, bigger_gate_val;
    // Want a little space between the path and the border for a potential Pokemon Center and Pokemart
    int path_correction = rand() % 15 + 3;

    if(N_entrance < S_entrance){
        smaller_gate_val = N_entrance;
        bigger_gate_val = S_entrance;
    }

    else{
        smaller_gate_val = S_entrance;
        bigger_gate_val = N_entrance;
    }

    for(r = 0; r < path_correction; r++){
        map[r][smaller_gate_val] = '#';
    }

    for(c = smaller_gate_val; c <= bigger_gate_val; c++){
        map[path_correction][c] = '#';
    }

    for(r = path_correction; r < 21; r++){
        map[r][bigger_gate_val] = '#';
    }
}

void generate_W_to_E_path(char map[21][80], int W_entrance, int E_entrance){
    int r, c, smaller_gate_val, bigger_gate_val;
    // Want a little space between the path and the border for a potential Pokemon Center and Pokemart
    int path_correction = rand() % 74 + 3;

    if(W_entrance < E_entrance){
        smaller_gate_val = W_entrance;
        bigger_gate_val = E_entrance;
    }

    else{
        smaller_gate_val = E_entrance;
        bigger_gate_val = W_entrance;
    }

    for(c = 0; c < path_correction; c++){
        map[smaller_gate_val][c] = '#';
    }

    for(r = smaller_gate_val; r <= bigger_gate_val; r++){
        map[r][path_correction] = '#';
    }

    for(c = path_correction; c < 80; c++){
        map[bigger_gate_val][c] = '#';
    }
}

void generate_gates(char map[21][80]){
    // Can generate within 3-76. I am trying to space out so a Pokemon Center and Pokemart could fit
    int N_entrance = rand() % 74 + 3;
    int S_entrance = rand() % 74 + 3;
    // Can generate within 4-17. I am trying to space out so a Pokemon Center and Pokemart could fit
    int W_entrance = rand() % 15 + 3;
    int E_entrance = rand() % 15 + 3;

    // I personally don't want the gates to be in-line with each other (avoiding straight paths)
    while(N_entrance == S_entrance){
        N_entrance = rand() % 74 + 3;
        S_entrance = rand() % 74 + 3;
    }

    generate_N_to_S_path(map, N_entrance, S_entrance);

    // I personally don't want the gates to be in-line with each other (avoiding straight paths)
    while(W_entrance == E_entrance){
        W_entrance = rand() % 15 + 3;
        E_entrance = rand() % 15 + 3;
    }

    generate_W_to_E_path(map, W_entrance, E_entrance);
}

bool able_to_spawn_buildings_vertically(char map[21][80], int building_spawn_x, int building_spawn_y){
    int r;
    bool able_to_conditional = true;

    for(r = 1; r <= 2; r++){
        // If the 2 spots to the top or bottom is a road, return false (can't spawn a building there)
        if((map[building_spawn_y - r][building_spawn_x] == '#') || (map[building_spawn_y + r][building_spawn_x] == '#')){
            able_to_conditional = false;
            break;
        }

        // If the 2 spots to the top or bottom of the square to the right is a road, return false (can't spawn a building there)
        if((map[building_spawn_y - r][building_spawn_x + 1] == '#') || (map[building_spawn_y + r][building_spawn_x + 1] == '#')){
            able_to_conditional = false;
            break;
        }
    }

    return able_to_conditional;
}

bool able_to_spawn_buildings_horizontally(char map[21][80], int building_spawn_x, int building_spawn_y){
    int c;
    bool able_to_conditional = true;

    for(c = 1; c <= 2; c++){
        // If the 2 spots to the left or right is a road, return false (can't spawn a building there)
        if((map[building_spawn_y][building_spawn_x - c] == '#') || (map[building_spawn_y][building_spawn_x + c] == '#')){
            able_to_conditional = false;
            break;
        }

        // If the 2 spots to the left or right of the square below is a road, return false (can't spawn a building there)
        if((map[building_spawn_y + 1][building_spawn_x - c] == '#') || (map[building_spawn_y + 1][building_spawn_x + c] == '#')){
            able_to_conditional = false;
            break;
        }
    }

    return able_to_conditional;
}

void generate_buildings(char map[21][80]){
    int r, c;
    // Can generate within 3-76
    int building_spawn_x = rand() % 74 + 3;
    // Can generate within 3-17
    int building_spawn_y = rand() % 15 + 3;

    // If the randomly selected map piece isn't a road, reselect
    if(map[building_spawn_y][building_spawn_x] != '#'){
        generate_buildings(map);
    }

    else if(able_to_spawn_buildings_vertically(map, building_spawn_x, building_spawn_y) == true){
        for(r = 1; r <= 2; r++){
            for(c = 0; c <= 1; c++){
                map[building_spawn_y + r][building_spawn_x + c] = 'M';
                map[building_spawn_y - r][building_spawn_x + c] = 'C';
            }
        }
    }

    else if(able_to_spawn_buildings_horizontally(map, building_spawn_x, building_spawn_y) == true){
        for(r = 0; r <= 1; r++){
            for(c = 1; c <= 2; c++){
                map[building_spawn_y + r][building_spawn_x + c] = 'M';
                map[building_spawn_y + r][building_spawn_x - c] = 'C';
            }
        }
    }

    else{
        generate_buildings(map);
    }
}

void print_map(char map[21][80]){
    int r, c;

    for(r = 0; r < 21; r++){
        for(c = 0; c < 80; c++){
            printf("%c", map[r][c]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    char map[21][80];
    srand(time(NULL));

    generate_map_base(map);
    generate_terrain(map);
    generate_gates(map);
    generate_buildings(map);
    print_map(map);

    return 0;
}