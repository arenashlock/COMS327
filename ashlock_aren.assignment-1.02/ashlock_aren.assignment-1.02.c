#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "terrain.h"

void gen_map(struct single_map *world[401][401], int world_r, int world_c){
    // Allocate memory for the new map
    world[world_r][world_c] = malloc(sizeof(struct single_map));
    // The row and col of the map needs to be fixed since the middle is (200, 200) to us, but it's (0, 0) to the player
    world[world_r][world_c]->map_row = world_r - 200;
    world[world_r][world_c]->map_col = world_c - 200;

    // Generate the terrain for the map
    gen_base_terrain(world[world_r][world_c]);
    gen_terrain(world[world_r][world_c]);

    // Generate the gates (-1 means we should randomly generate the gate)
    int set_n = -1;
    int set_s = -1;
    int set_w = -1;
    int set_e = -1;

    // If the user isn't at the top of the world
    if(world_r > 0){
        // Check for an already existing south gate from the map above (will be the new map's north gate)
        if(world[world_r - 1][world_c] != NULL){
            // If there exists a map to the left, pass in the map's east value to the new map's west value
            set_n = world[world_r - 1][world_c]->s;
        }
    }

    // If the user isn't at the bottom of the world
    if(world_r < 400){
        // Check for an already existing north gate from the map below (will be the new map's south gate)
        if(world[world_r + 1][world_c] != NULL){
            // If there exists a map to the left, pass in the map's east value to the new map's west value
            set_s = world[world_r + 1][world_c]->n;
        }
    }

    // If the user isn't at the far left of the world
    if(world_c > 0){
        // Check for an already existing east gate from the map to the left (will be the new map's west gate)
        if(world[world_r][world_c - 1] != NULL){
            // If there exists a map to the left, pass in the map's east value to the new map's west value
            set_w = world[world_r][world_c - 1]->e;
        }
    }

    // If the user isn't at the far right of the world
    if(world_c < 400){
        // Check for an already existing west gate from the map to the right (will be the new map's east gate)
        if(world[world_r][world_c + 1] != NULL){
            // If there exists a map to the left, pass in the map's east value to the new map's west value
            set_e = world[world_r][world_c + 1]->w;
        }
    }

    gen_gates(world[world_r][world_c], set_n, set_s, set_w, set_e);
    
    // I want to guarantee the buildings on the starting map
    if(world_r == 200 && world_c == 200){
        gen_buildings(world[world_r][world_c]);
    }

    // Otherwise, generate using the given probability
    else{
        // Distance variable for the probability of generating each building equation from assignment-1.02
        int manhattan_distance = abs(world[world_r][world_c]->map_col) + abs(world[world_r][world_c]->map_row);

        // Probability of generating each building equation from assignment-1.02
        if((rand() % 100) < ((-45 * manhattan_distance) / 200 + 50)){
            gen_buildings(world[world_r][world_c]);
        }
    }
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int r, c;

    // Construct a 401x401 array of maps called "world"
    struct single_map *world[401][401];

    // Initialize to something that isn't q so we enter the while loop for user input
    char input = 'y';

    // Initialize to coordinates (200, 200) since that'll be out first map
    int world_r = 200;
    int world_c = 200;
    int fly_r = 0;
    int fly_c = 0;

    // Initialize all maps to be NULL (issues with checking non-initialized maps)
    for(r = 0; r < 401; r++){
        for(c = 0; c < 401; c++){
            world[r][c] = NULL;
        }
    }

    // Generate the starting map at (200, 200)
    gen_map(world, world_r, world_c);
    
    // While user doesn't want to quit
    while(input != 'q'){
        // Print the map and prompt the user for a command
        print_map(world[world_r][world_c]);
        printf("Enter a command: ");
        // The space before %c means to ignore whitespaces in the input (fixes scanning newline issue)
        scanf(" %c", &input);

        // User wants to move north
        if(input == 'n'){
            // If the user isn't at the top of the world
            if(world_r > 0){
                // Move up a row
                world_r -= 1;
                
                // If the spot in the array they moved to is null, generate a new map
                if(world[world_r][world_c] == NULL){
                    gen_map(world, world_r, world_c);
                }
            }
        }

        // User wants to move south
        else if(input == 's'){
            // If the user isn't at the bottom of the world
            if(world_r < 400){
                // Move down a row
                world_r += 1;
                
                // If the spot in the array they moved to is null, generate a new map
                if(world[world_r][world_c] == NULL){
                    gen_map(world, world_r, world_c);
                }
            }
        }

        // User wants to move west
        else if(input == 'w'){
            // If the user isn't at the far left of the world
            if(world_c > 0){
                // Move a row to the left
                world_c -= 1;
                
                // If the spot in the array they moved to is null, generate a new map
                if(world[world_r][world_c] == NULL){
                    gen_map(world, world_r, world_c);
                }
            }
        }

        // User wants to move east
        else if(input == 'e'){
            // If the user isn't at the far right of the world
            if(world_c < 400){
                // Move a row to the right
                world_c += 1;
                
                // If the spot in the array they moved to is null, generate a new map
                if(world[world_r][world_c] == NULL){
                    gen_map(world, world_r, world_c);
                }
            }
        }

        // If user wants to fly to a map, scan for the x and y coordinates
        else if(input == 'f'){
            // Get the coordinates from the user in the fashion of "f x y"
            scanf(" %d %d", &fly_c, &fly_r);
            // Have to adjust the user's values since they think the starting map is (0, 0) when it is actually (200, 200)
            world_r = fly_r + 200;
            world_c = fly_c + 200;

            if(world[world_r][world_c] == NULL){
                    gen_map(world, world_r, world_c);
            }
        }
    }

    // Free the memory for all maps we generated (since the maps we generated were allocated memory)
    for(r = 0; r < 401; r++){
        for(c = 0; c < 401; c++){
            if(world[r][c] != NULL){
                free(world[r][c]);
            }
        }
    }

    printf("Thanks for playing!\n");

    return 0;
}