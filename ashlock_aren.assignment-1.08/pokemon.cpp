#include <math.h>

#include "pokemon.h"
#include "db_parse.h"

#include <unistd.h>
#include <ncurses.h>
#include <cctype>
#include <cstdlib>
#include <climits>

Pokemon::Pokemon(int level) : level(level){
  int i;
  int move_1_index, move_2_index;

  // 898 Pokemon, but it starts at index 1
  pokemon_index = (rand() % 898) + 1;

  // MOVES...
  do {
    move_1_index = (rand() % 528238) + 1;

    poke_moves[0] = pokemon_moves[move_1_index].move_id;
  }
  while(!((pokemon_moves[move_1_index].pokemon_id == pokemon[pokemon_index].species_id) &&
          (pokemon_moves[move_1_index].pokemon_move_method_id == 1)));

  do {
    move_2_index = (rand() % 528238) + 1;

    poke_moves[1] = pokemon_moves[move_2_index].move_id;
  }
  while(!((pokemon_moves[move_2_index].pokemon_id == pokemon[pokemon_index].species_id) &&
          (pokemon_moves[move_2_index].pokemon_move_method_id == 1)) ||
          (move_1_index == move_2_index));

  // Calculate both the random IV value and the stat value for each of the Pokemon's stats
  for(i = 0; i < 6; i++) {
    poke_iv[i] = rand() % 16;

    if(i == 0) {
      poke_stats[i] = (((((pokemon_stats[1 + (pokemon_index - 1) * 6].base_stat + poke_iv[i]) * 2) * level) / 100) + level + 10);
    }
    else {
      poke_stats[i] = (((((pokemon_stats[1 + (pokemon_index - 1) * 6].base_stat + poke_iv[i]) * 2) * level) / 100) + 5);
    }
  }

  // Determine the gender
  if((rand() % 2) == 0) {
    poke_gender = male;
  }
  else {
    poke_gender = female;
  }

  // Is the Pokemon shiny?
  if((rand() % 8192) == 0) {
    is_shiny = true;
  }
}

const char *Pokemon::get_species() const {
  return species[pokemon_index].identifier;
}

int Pokemon::get_level() const {
  return level;
}

int Pokemon::get_hp() const {
  return poke_stats[hp];
}

int Pokemon::get_attack() const {
  return poke_stats[attack];
}

int Pokemon::get_defense() const {
  return poke_stats[defense];
}

int Pokemon::get_special_attack() const {
  return poke_stats[special_attack];
}

int Pokemon::get_special_defense() const {
  return poke_stats[special_defense];
}

int Pokemon::get_speed() const {
  return poke_stats[speed];
}

const char *Pokemon::get_move(int i) const {
  return moves[poke_moves[i]].identifier;
}