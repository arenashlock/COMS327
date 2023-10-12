#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#include "terrain.h"
#include "heap.h"
#include "player.h"

typedef enum{
    npc_hiker,
    npc_rival
} npc_t;

typedef struct{
  heap_node_t *hn;
  int pos_x;
  int pos_y;
  int cost;
} npc_path;

static int32_t npc_cost_cmp(const void *key, const void *with){
  return ((npc_path *) key)->cost - ((npc_path *) with)->cost;
}

static void dijkstra_npc_path(single_map *map, int player_spawn_x, int player_spawn_y, npc_t npc){
    npc_path npc_cost_path[21][80], *npc_c_p;
    heap_t h;
    int r = 0, c = 0;

    // For the different types of NPCs, make a map of the terrain cost for reference when calculating the short path using Dijkstra's algorithm
    if (npc == npc_hiker){
        for (r = 0; r < 21; r++){
            for (c = 0; c < 80; c++){
                switch (map->terrain[r][c]){
                    case ter_small_grass:
                    case ter_path:
                        map->ter_cost[r][c] = 10;
                        break;
                    case ter_tall_grass:
                    case ter_mountain:
                        map->ter_cost[r][c] = 15;
                        break;
                    case ter_mart:
                    case ter_center:
                        map->ter_cost[r][c] = 50;
                        break;
                    default:
                        map->ter_cost[r][c] = INT_MAX;
                }
            }
        }
    }

    else if (npc == npc_rival){
        for (r = 0; r < 21; r++){
            for (c = 0; c < 80; c++){
                switch (map->terrain[r][c]){
                    case ter_small_grass:
                    case ter_path:
                        map->ter_cost[r][c] = 10;
                        break;
                    case ter_tall_grass:
                        map->ter_cost[r][c] = 20;
                        break;
                    case ter_mart:
                    case ter_center:
                        map->ter_cost[r][c] = 50;
                        break;
                    default:
                        map->ter_cost[r][c] = INT_MAX;
                }
            }
        }
    }
  
    // Initialize all the attributes of the cost path
    for (r = 0; r < 21; r++){
        for (c = 0; c < 80; c++){
            npc_cost_path[r][c].hn = NULL;
            npc_cost_path[r][c].pos_y = r;
            npc_cost_path[r][c].pos_x = c;
            npc_cost_path[r][c].cost = INT_MAX;
        }
    }

    // Initialize the block that the player is spawned at to equal 0
    npc_cost_path[player_spawn_y][player_spawn_x].cost = 0;

    heap_init(&h, npc_cost_cmp, NULL);

    // Only need 1-19 since the top and bottom edge (containig boulders and gates) always has a cost of infinity
    for(r = 1; r < 20; r++){
        // Only need 1-78 since the left and right edge (containig boulders and gates) always has a cost of infinity
        for(c = 1; c < 79; c++){
            // We only care about calculating the cost for each block that is reachable (so ignore the terrain that costs infinity)
            if(map->ter_cost[r][c] != INT_MAX){
                npc_cost_path[r][c].hn = heap_insert(&h, &npc_cost_path[r][c]);
            }
        }
    }

    while ((npc_c_p = heap_remove_min(&h))){
        npc_c_p->hn = NULL;
        int r, c;

        // Go through a 3x3 matrix centered around the current minimum of the heap
        for(r = -1; r <= 1; r++){
            for(c = -1; c <= 1; c++){
                // Ignore the center of the 3x3 matrix since we already assigned the cost to it
                if (!(r == 0 && c == 0) &&
                    (npc_cost_path[npc_c_p->pos_y + r][npc_c_p->pos_x + c].hn) &&
                    (npc_cost_path[npc_c_p->pos_y + r][npc_c_p->pos_x + c].cost > ((npc_c_p->cost + map->ter_cost[npc_c_p->pos_y][npc_c_p->pos_x])))){
                        npc_cost_path[npc_c_p->pos_y + r][npc_c_p->pos_x + c].cost = ((npc_c_p->cost + map->ter_cost[npc_c_p->pos_y][npc_c_p->pos_x]));
                        heap_decrease_key_no_replace(&h, npc_cost_path[npc_c_p->pos_y + r][npc_c_p->pos_x + c].hn);
                }
            }
        }
    }

    // Print the cost for each spot in Dijkstra's matrix
    for (r = 0; r < 21; r++){
        for (c = 0; c < 80; c++){
            // We don't want to print the infinity costs
            if(npc_cost_path[r][c].cost == INT_MAX){
                printf("   ");
            }

            else{
                printf("%02d ", npc_cost_path[r][c].cost % 100);
            }
        }
        printf("\n");
    }
}

void gen_map(single_map *world[401][401], int world_r, int world_c){
    // Allocate memory for the new map
    world[world_r][world_c] = malloc(sizeof(single_map));
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
        int building_odds = manhattan_distance > 200 ? 5 : ((-45 * manhattan_distance) / 200 + 50);
        if((rand() % 100) < building_odds){
            gen_buildings(world[world_r][world_c]);
        }
    }
}

void print_map(single_map *map, player_t *player){
    int r, c;

    for(r = 0; r < 21; r++){
        for(c = 0; c < 80; c++){
            // Print the player character
            /*
                I did it this way to avoid overwriting the ter_char within the map 
                (idk if that's an issue that COULD occur or not, but may as well avoid it)
            */
            if(r == player->pos_y && c == player->pos_x){
                printf("@");
            }

            else{
                switch (map->terrain[r][c]){
                    case ter_tall_grass:
                        printf(":");
                        break;
                    case ter_small_grass:
                        printf(".");
                        break;
                    case ter_water:
                        printf("~");
                        break;
                    case ter_boulder:
                    case ter_mountain:
                        printf("%%");
                        break;
                    case ter_tree:
                        printf("^");
                        break;
                    case ter_path:
                    case ter_gate:
                        printf("#");
                        break;
                    case ter_mart:
                        printf("M");
                        break;
                    case ter_center:
                        printf("C");
                        break;
                }
            }
        }

        printf("\n");
    }

    printf("Map coordinates: (%d, %d) ", map->map_col, map->map_row);
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int r, c;
    char input;

    // Construct a 401x401 array of maps called "world"
    single_map *world[401][401];

    // Initialize a player
    player_t *player = malloc(sizeof(player_t));

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
        // ------------------------------- MOVE OUT OF THE WHILE LOOP IN THE FUTURE! -------------------------------
        // Spawn a player
        spawn_player(world[world_r][world_c], player);

        // Print the map
        print_map(world[world_r][world_c], player);
        // ------------------------------- DELETE WHEN WE NO LONGER PRINT DIJKSTRA MAPS -------------------------------
        printf("\n");

        dijkstra_npc_path(world[world_r][world_c], player->pos_x, player->pos_y, npc_hiker);
        dijkstra_npc_path(world[world_r][world_c], player->pos_x, player->pos_y, npc_rival);

        // Prompt the user for a command
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