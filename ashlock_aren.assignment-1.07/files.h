#ifndef FILES_H
#define FILES_H

class Pokemon {
public:
    int id;
    std::string identifier;
    int species_id;
    int height;
    int weight;
    int base_experience;
    int order;
    int is_default;
};

class Moves {
public:
    int id;
    std::string identifier;
    int generation_id;
    int type_id;
    int power;
    int pp;
    int accuracy;
    int priority;
    int target_id;
    int damage_class_id;
    int effect_id;
    int effect_chance;
    int contest_type_id;
    int contest_effect_id;
    int super_contest_effect_id;
};

class Pokemon_Moves {
public:
    int pokemon_id;
    int version_group_id;
    int move_id;
    int pokemon_move_method_id;
    int level;
    int order;
};

class Pokemon_Species {
public:
    int id;
    std::string identifier;
    int generation_id;
    int evolves_from_species_id;
    int evolution_chain_id;
    int color_id;
    int shape_id;
    int habitat_id;
    int gender_rate;
    int capture_rate;
    int base_happiness;
    int is_baby;
    int hatch_counter;
    int has_gender_differences;
    int growth_rate_id;
    int forms_switchable;
    int is_legendary;
    int is_mythical;
    int order;
    int conquest_order;
};

class Experience {
public:
    int growth_rate_id;
    int level;
    int experience;
};

// Only lines with local_language_id == 9 has the "name" field in English (still fully parsing, but just a note for possible future considerations)
class Type_Names {
public:
    int type_id;
    int local_language_id;
    std::string name;
};

class Pokemon_Stats {
public:
    int pokemon_id;
    int stat_id;
    int base_stat;
    int effort;
};

class Stats {
public:
    int id;
    int damage_class_id;
    std::string identifier;
    int is_battle_only;
    int game_index;
};

class Pokemon_Types {
public:
    int pokemon_id;
    int type_id;
    int slot;
};

// extern keyword makes it global
extern Pokemon All_Pokemon[1092];
extern Moves All_Moves[844];
extern Pokemon_Moves All_Pokemon_Moves[528238];
extern Pokemon_Species All_Pokemon_Species[898];
extern Experience All_Experience[600];
extern Type_Names All_Type_Names[193];
extern Pokemon_Stats All_Pokemon_Stats[6552];
extern Stats All_Stats[8];
extern Pokemon_Types All_Pokemon_Types[1675];

void read_file(std::string filename);

#endif