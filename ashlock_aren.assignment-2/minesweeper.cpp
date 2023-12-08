#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include <queue>

#define NOT_REVEALED_BLOCK  1
#define REVEALED_BLOCK      2
#define SELECTED_BLOCK      3
#define MINE                4
#define BOUNDARY            5

#define MIN_X               1
#define MAX_X               78
#define MIN_Y               1
#define MAX_Y               19

#define mine_map            0
#define revealed_tracker    1

int game_map[MAX_Y][MAX_X][2];

int spaces_remaining;

int player_row;
int player_col;

bool player_done = false;

// JUST FOR DEBUGGING DURING DEVELOPMENT!
void print_board() {
    int row, col;

    for(row = 0; row < MAX_Y; row++) {
        for(col = 0; col < MAX_X; col++) {
            if(game_map[row][col][mine_map] == -1) {
                std::cout << 'X';
            }
            else {
                std::cout << game_map[row][col][mine_map];
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void init_board() {
    int row, col;

    for(row = 0; row < MAX_Y; row++) {
        for(col = 0; col < MAX_X; col++) {
            // Initialize all spots to be non-mines
            game_map[row][col][mine_map] = 0;
            // Everything starts off not-revealed
            game_map[row][col][revealed_tracker] = 1;
        }
    }

    // Random number of mines 185-260
    int total_mines = (std::rand() % 76) + 185;
    // Remove the mine spaces from the total spaces
    spaces_remaining -= total_mines;

    while(total_mines > 0) {
        int mine_row = std::rand() % MAX_Y;
        int mine_col = std::rand() % MAX_X;

        if(game_map[mine_row][mine_col][mine_map] >= 0) {
            game_map[mine_row][mine_col][mine_map] = -1;

            // UPDATE THE SURROUNDING BLOCKS! (the >= 0 is to make sure we are only updating non-mine blocks!)
            if(mine_col > 0) {
                // Top left block
                if((mine_row > 0) && (game_map[mine_row - 1][mine_col - 1][mine_map] >= 0)) {
                    game_map[mine_row - 1][mine_col - 1][mine_map] += 1;
                }
                // Middle left block
                if(game_map[mine_row][mine_col - 1][mine_map] >= 0) {
                    game_map[mine_row][mine_col - 1][mine_map] += 1;
                }
                // Bottom left block
                if((mine_row < (MAX_Y - 1)) && (game_map[mine_row + 1][mine_col - 1][mine_map] >= 0)) {
                    game_map[mine_row + 1][mine_col - 1][mine_map] += 1;
                }
            }

            // Top middle block
            if((mine_row > 0) && (game_map[mine_row - 1][mine_col][mine_map] >= 0)) {
                game_map[mine_row - 1][mine_col][mine_map] += 1;
            }
            // Bottom middle block
            if((mine_row < (MAX_Y - 1)) && (game_map[mine_row + 1][mine_col][mine_map] >= 0)) {
                game_map[mine_row + 1][mine_col][mine_map] += 1;
            }

            if(mine_col < (MAX_X - 1)) {
                // Top right block
                if((mine_row > 0) && (game_map[mine_row - 1][mine_col + 1][mine_map] >= 0)) {
                    game_map[mine_row - 1][mine_col + 1][mine_map] += 1;
                }
                // Middle right block
                if(game_map[mine_row][mine_col + 1][mine_map] >= 0){
                    game_map[mine_row][mine_col + 1][mine_map] += 1;
                }
                // Bottom right block
                if((mine_row < (MAX_Y - 1)) && (game_map[mine_row + 1][mine_col + 1][mine_map] >= 0)) {
                    game_map[mine_row + 1][mine_col + 1][mine_map] += 1;
                }
            }

            total_mines--;
        }
    }
}

void new_game() {
    // Set the number of spaces left to be the max possible
    spaces_remaining = MAX_Y * MAX_X;

    // Reset the player position to the middle
    player_row = MAX_Y / 2;
    player_col = MAX_X / 2;

    // Generate a new gameboard
    init_board();
}

void init_curses() {
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(NOT_REVEALED_BLOCK, COLOR_BLACK, COLOR_BLACK);
    init_pair(REVEALED_BLOCK, COLOR_BLACK, COLOR_GREEN);
    init_pair(SELECTED_BLOCK, COLOR_CYAN, COLOR_CYAN);
    init_pair(MINE, COLOR_WHITE, COLOR_RED);
    init_pair(BOUNDARY, COLOR_WHITE, COLOR_WHITE);
}

void win_game() {
    bool invalid_input = true;

    clear();

    mvprintw(7, 18, "__   _____  _   _  __        _____ _   _ _ ");
    mvprintw(8, 18, "\\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | | |");
    mvprintw(9, 18, " \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| | |");
    mvprintw(10, 18, "  | || |_| | |_| |   \\ V  V /  | || |\\  |_|");
    mvprintw(11, 18, "  |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_(_)");
    mvprintw(13, 28, "[n] New game   [q] Quit");

    while(invalid_input) {
        switch(getch()) {
            case 'n':
                new_game();
                invalid_input = false;
                break;
            case 'q':
                player_done = true;
                invalid_input = false;
                break;
            default:
                break;
        }
    }
}

void lose_game() {
    bool invalid_input = true;

    clear();

    mvprintw(7, 15, "__   _____  _   _   _     ___  ____  _____      __");
    mvprintw(8, 15, "\\ \\ / / _ \\| | | | | |   / _ \\/ ___|| ____|  _ / /");
    mvprintw(9, 15, " \\ V / | | | | | | | |  | | | \\___ \\|  _|   (_) | ");
    mvprintw(10, 15, "  | || |_| | |_| | | |__| |_| |___) | |___   _| | ");
    mvprintw(11, 15, "  |_| \\___/ \\___/  |_____\\___/|____/|_____| (_) | ");
    mvprintw(12, 15, "                                               \\_\\");
    mvprintw(14, 28, "[n] New game   [q] Quit");

    while(invalid_input) {
        switch(getch()) {
            case 'n':
                new_game();
                invalid_input = false;
                break;
            case 'q':
                player_done = true;
                invalid_input = false;
                break;
            default:
                break;
        }
    }
}

void draw_screen(bool cheat_mode) {
    int row, col;

    clear();

    // INSTRUCTIONS FOR USER
    mvprintw(21, 71, "[q] Quit");
    mvprintw(21, 1, "Letter keys:  [w] Up, [a] Left, [s] Down, [d] Right");
    mvprintw(22, 1, "Arrow keys:   [^] Up, [<] Left, [V] Down, [>] Right");
    mvprintw(23, 1, "Playing keys: [r] Reveal block, [f] Place flag");

    // Map
    for(row = 0; row <= MAX_Y + 1; row++) {
        for(col = 0; col <= MAX_X + 1; col++) {
            if(row == MIN_Y - 1 || row == MAX_Y + 1 || col == MIN_X - 1 || col == MAX_X + 1) {
                attron(COLOR_PAIR(BOUNDARY));
                mvaddch(row, col, '_');
                attroff(COLOR_PAIR(BOUNDARY));
            }

            else if(row == player_row && col == player_col) {
                attron(COLOR_PAIR(SELECTED_BLOCK));
                mvaddch(player_row, player_col, '_');
                attroff(COLOR_PAIR(SELECTED_BLOCK));
            }

            else {
                if(cheat_mode && (game_map[row - 1][col - 1][mine_map] == -1)) {
                    attron(COLOR_PAIR(MINE));
                    mvaddch(row, col, 'X');
                    attroff(COLOR_PAIR(MINE));
                }

                else if(game_map[row - 1][col - 1][revealed_tracker] == 0) {
                    attron(COLOR_PAIR(REVEALED_BLOCK));
                    mvaddch(row, col, game_map[row - 1][col - 1][mine_map] + '0');
                    attroff(COLOR_PAIR(REVEALED_BLOCK));
                }

                else if(game_map[row - 1][col - 1][revealed_tracker] == -1) {
                    attron(COLOR_PAIR(MINE));
                    mvaddch(row, col, 'X');
                    attroff(COLOR_PAIR(MINE));
                }

                else{
                    attron(COLOR_PAIR(NOT_REVEALED_BLOCK));
                    mvaddch(row , col, '?');
                    attroff(COLOR_PAIR(NOT_REVEALED_BLOCK));
                }
            }
        }
    }
}

// Queue for revealing all the blocks that we should
// Note: clicking on a 0 block reveals it's neighbors recursively until none of the neighbors are 0!
void reveal_blocks(std::pair<int, int> user_revealed_block) {
    std::queue<std::pair<int, int>> revealed_blocks;
    revealed_blocks.push(user_revealed_block);

    while(!revealed_blocks.empty()) {
        std::pair<int, int> block_to_be_revealed = revealed_blocks.front();
        int block_row = block_to_be_revealed.first;
        int block_col = block_to_be_revealed.second;

        if(game_map[block_row][block_col][revealed_tracker] != 0) {
            game_map[block_row][block_col][revealed_tracker] = 0;
            spaces_remaining--;
        }

        // UPDATE THE SURROUNDING BLOCKS IF WE CLICK A 0 BLOCK!
        if(game_map[block_row][block_col][mine_map] == 0){
            if(block_col > 0) {
                // Top left block      // NOT A MINE                                             // NOT REVEALED
                if((block_row > 0) && (game_map[block_row - 1][block_col - 1][mine_map] >= 0) && (game_map[block_row - 1][block_col - 1][revealed_tracker] != 0)) {
                    game_map[block_row - 1][block_col - 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row - 1][block_col - 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row - 1, block_col - 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
                // Middle left block
                if((game_map[block_row][block_col - 1][mine_map] >= 0) && (game_map[block_row][block_col - 1][revealed_tracker] != 0)) {
                    game_map[block_row][block_col - 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row][block_col - 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row, block_col - 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
                // Bottom left block
                if((block_row < (MAX_Y - 1)) && (game_map[block_row + 1][block_col - 1][mine_map] >= 0) && (game_map[block_row + 1][block_col - 1][revealed_tracker] != 0)) {
                    game_map[block_row + 1][block_col - 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row + 1][block_col - 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row + 1, block_col - 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
            }

            // Top middle block
            if((block_row > 0) && (game_map[block_row - 1][block_col][mine_map] >= 0) && (game_map[block_row - 1][block_col][revealed_tracker] != 0)) {
                game_map[block_row - 1][block_col][revealed_tracker] = 0;
                spaces_remaining--;

                if(game_map[block_row - 1][block_col][mine_map] == 0) {
                    std::pair<int, int> neighbor_zero(block_row - 1, block_col);
                    revealed_blocks.push(neighbor_zero);
                }
            }
            // Bottom middle block
            if((block_row < (MAX_Y - 1)) && (game_map[block_row + 1][block_col][mine_map] >= 0) && (game_map[block_row + 1][block_col][revealed_tracker] != 0)) {
                game_map[block_row + 1][block_col][revealed_tracker] = 0;
                spaces_remaining--;

                if(game_map[block_row + 1][block_col][mine_map] == 0) {
                    std::pair<int, int> neighbor_zero(block_row + 1, block_col);
                    revealed_blocks.push(neighbor_zero);
                }
            }

            if(block_col < (MAX_X - 1)) {
                // Top right block
                if((block_row > 0) && (game_map[block_row - 1][block_col + 1][mine_map] >= 0) && (game_map[block_row - 1][block_col + 1][revealed_tracker] != 0)) {
                    game_map[block_row - 1][block_col + 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row - 1][block_col + 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row - 1, block_col + 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
                // Middle right block
                if((game_map[block_row][block_col + 1][mine_map] >= 0) && (game_map[block_row][block_col + 1][revealed_tracker] != 0)){
                    game_map[block_row][block_col + 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row][block_col + 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row, block_col + 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
                // Bottom right block
                if((block_row < (MAX_Y - 1)) && (game_map[block_row + 1][block_col + 1][mine_map] >= 0) && (game_map[block_row + 1][block_col + 1][revealed_tracker] != 0)) {
                    game_map[block_row + 1][block_col + 1][revealed_tracker] = 0;
                    spaces_remaining--;

                    if(game_map[block_row + 1][block_col + 1][mine_map] == 0) {
                        std::pair<int, int> neighbor_zero(block_row + 1, block_col + 1);
                        revealed_blocks.push(neighbor_zero);
                    }
                }
            }
        }

        revealed_blocks.pop();
    }
}

void game_loop(bool cheat_mode) {
    do {
        draw_screen(cheat_mode);

        switch(getch()) {
            case 'w':
            case KEY_UP:
                if(player_row > MIN_Y) {
                    player_row--;
                }
                break;
            case 'a':
            case KEY_LEFT:
                if(player_col > MIN_X) {
                    player_col--;
                }
                break;
            case 's':
            case KEY_DOWN:
                if(player_row < MAX_Y) {
                    player_row++;
                }
                break;
            case 'd':
            case KEY_RIGHT:
                if(player_col < MAX_X) {
                    player_col++;
                }
                break;
            case 'r':
                // Revealed a mine
                if(game_map[player_row - 1][player_col - 1][mine_map] == -1) {
                    lose_game();
                }

                else if(game_map[player_row - 1][player_col - 1][revealed_tracker] != 0) {
                    std::pair<int, int> user_revealed_block(player_row - 1, player_col - 1);
                    reveal_blocks(user_revealed_block);

                    if(spaces_remaining == 0) {
                        win_game();
                    }
                }
                break;
            case 'f':
                if(game_map[player_row - 1][player_col - 1][revealed_tracker] != 0) {
                    game_map[player_row - 1][player_col - 1][revealed_tracker] *= -1;
                }
                break;
            case 'q':
                player_done = true;
                break;
            default:
                break;
        }
    } while(!player_done);
}

int main(int argc, char *argv[]) {
    bool cheat_mode = false;
    if(argc > 1) {
        if(strcmp(argv[1], "cheat") == 0) {
            cheat_mode = true;
        }
    }

    srand(time(NULL));
    init_curses();
    
    new_game();
    game_loop(cheat_mode);

    endwin();
    std::cout << "\nThank you so much for playing! I hope you enjoyed :)\n- Aren Ashlock\n(COM S 327, Fall 2023)\n" << std::endl;

    // Calling the debugging print statement (not necessary aside from development)
    // print_board();

    return 0;
}