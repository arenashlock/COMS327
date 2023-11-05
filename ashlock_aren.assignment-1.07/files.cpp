#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <climits>

#include "files.h"

Pokemon All_Pokemon[1092];
Moves All_Moves[844];
Pokemon_Moves All_Pokemon_Moves[528238];
Pokemon_Species All_Pokemon_Species[898];
Experience All_Experience[600];
Type_Names All_Type_Names[193];
Pokemon_Stats All_Pokemon_Stats[6552];
Stats All_Stats[8];
Pokemon_Types All_Pokemon_Types[1675];

void pokemon_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].id = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    // No need for if-else since this is a string attribute
    end = line.find(",");
    All_Pokemon[line_number - 1].identifier = line.substr(0, end);
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].species_id = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].species_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].height = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].height = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].weight = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].weight = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].base_experience = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].base_experience = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon[line_number - 1].order = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].order = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Pokemon[line_number - 1].is_default = INT_MAX;
    }
    else {
        All_Pokemon[line_number - 1].is_default = std::stoi(line);
    }
}

void moves_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    // No need for if-else since this is a string attribute
    end = line.find(",");
    All_Moves[line_number - 1].identifier = line.substr(0, end);
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].generation_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].generation_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);
    
    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].type_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].type_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].power = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].power = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].pp = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].pp = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].accuracy = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].accuracy = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].priority = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].priority = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].target_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].target_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].damage_class_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].damage_class_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].effect_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].effect_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].effect_chance = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].effect_chance = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].contest_type_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].contest_type_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Moves[line_number - 1].contest_effect_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].contest_effect_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Moves[line_number - 1].super_contest_effect_id = INT_MAX;
    }
    else {
        All_Moves[line_number - 1].super_contest_effect_id = std::stoi(line);
    }
}

void pokemon_moves_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Moves[line_number - 1].pokemon_id = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].pokemon_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Moves[line_number - 1].version_group_id = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].version_group_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Moves[line_number - 1].move_id = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].move_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Moves[line_number - 1].pokemon_move_method_id = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].pokemon_move_method_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Moves[line_number - 1].level = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].level = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Pokemon_Moves[line_number - 1].order = INT_MAX;
    }
    else {
        All_Pokemon_Moves[line_number - 1].order = std::stoi(line);
    }
}

void pokemon_species_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    // No need for if-else since this is a string attribute
    end = line.find(",");
    All_Pokemon_Species[line_number - 1].identifier = line.substr(0, end);
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].generation_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].generation_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].evolves_from_species_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].evolves_from_species_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].evolution_chain_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].evolution_chain_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].color_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].color_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].shape_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].shape_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].habitat_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].habitat_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].gender_rate = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].gender_rate = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].capture_rate = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].capture_rate = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].base_happiness = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].base_happiness = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].is_baby = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].is_baby = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].hatch_counter = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].hatch_counter = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].has_gender_differences = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].has_gender_differences = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].growth_rate_id = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].growth_rate_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].forms_switchable = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].forms_switchable = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].is_legendary = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].is_legendary = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].is_mythical = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].is_mythical = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Species[line_number - 1].order = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].order = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Pokemon_Species[line_number - 1].conquest_order = INT_MAX;
    }
    else {
        All_Pokemon_Species[line_number - 1].conquest_order = std::stoi(line);
    }
}

void experience_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Experience[line_number - 1].growth_rate_id = INT_MAX;
    }
    else {
        All_Experience[line_number - 1].growth_rate_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Experience[line_number - 1].level = INT_MAX;
    }
    else {
        All_Experience[line_number - 1].level = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Experience[line_number - 1].experience = INT_MAX;
    }
    else {
        All_Experience[line_number - 1].experience = std::stoi(line);
    }
}

void type_names_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Type_Names[line_number - 1].type_id = INT_MAX;
    }
    else {
        All_Type_Names[line_number - 1].type_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Type_Names[line_number - 1].local_language_id = INT_MAX;
    }
    else {
        All_Type_Names[line_number - 1].local_language_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    // No need for if-else since this is a string attribute
    All_Type_Names[line_number - 1].name = line;
}

void pokemon_stats_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Stats[line_number - 1].pokemon_id = INT_MAX;
    }
    else {
        All_Pokemon_Stats[line_number - 1].pokemon_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Stats[line_number - 1].stat_id = INT_MAX;
    }
    else {
        All_Pokemon_Stats[line_number - 1].stat_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Stats[line_number - 1].base_stat = INT_MAX;
    }
    else {
        All_Pokemon_Stats[line_number - 1].base_stat = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Pokemon_Stats[line_number - 1].effort = INT_MAX;
    }
    else {
        All_Pokemon_Stats[line_number - 1].effort = std::stoi(line);
    }
}

void stats_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Stats[line_number - 1].id = INT_MAX;
    }
    else {
        All_Stats[line_number - 1].id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Stats[line_number - 1].damage_class_id = INT_MAX;
    }
    else {
        All_Stats[line_number - 1].damage_class_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    // No need for if-else since this is a string attribute
    end = line.find(",");
    All_Stats[line_number - 1].identifier = line.substr(0, end);
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Stats[line_number - 1].is_battle_only = INT_MAX;
    }
    else {
        All_Stats[line_number - 1].is_battle_only = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Stats[line_number - 1].game_index = INT_MAX;
    }
    else {
        All_Stats[line_number - 1].game_index = std::stoi(line);
    }
}

void pokemon_types_line_parse(std::string line, int line_number) {
    int end;
    
    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Types[line_number - 1].pokemon_id = INT_MAX;
    }
    else {
        All_Pokemon_Types[line_number - 1].pokemon_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    end = line.find(",");
    if(end == 0) {
        All_Pokemon_Types[line_number - 1].type_id = INT_MAX;
    }
    else {
        All_Pokemon_Types[line_number - 1].type_id = std::stoi(line.substr(0, end));
    }
    line.erase(0, end + 1);

    if(line.size() == 0) {
        All_Pokemon_Types[line_number - 1].slot = INT_MAX;
    }
    else {
        All_Pokemon_Types[line_number - 1].slot = std::stoi(line);
    }
}

void read_file(std::string filename){
    std::fstream specified_file;

    // First, try opening in the share folder in pyrite
    specified_file.open("/share/cs327/pokedex/pokedex/data/csv/" + filename + ".csv", std::fstream::in);

    // If the file can be found, search the specified file
    if(specified_file.is_open()){
        int i;
        int line_number = 1;
        std::string file_line;

        // Throw out the first line with the names of the parameters
        std::getline(specified_file, file_line);

        if(!(filename.compare("pokemon"))){
            while (std::getline(specified_file, file_line)) {
                pokemon_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 1092; i++) {
                if(All_Pokemon[i].id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].id << ",";
                }

                // No need to check since strings won't have INT_MAX
                std::cout << All_Pokemon[i].identifier << ",";

                if(All_Pokemon[i].species_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].species_id << ",";
                }
                
                if(All_Pokemon[i].height == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].height << ",";
                }
                
                if(All_Pokemon[i].weight == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].weight << ",";
                }

                if(All_Pokemon[i].base_experience == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].base_experience << ",";
                }
                
                if(All_Pokemon[i].order == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon[i].order << ",";
                }
                
                if(All_Pokemon[i].is_default == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Pokemon[i].is_default << std::endl;
                }
            }
        }

        else if(!(filename.compare("moves"))){
            while (std::getline(specified_file, file_line)) {
                moves_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 844; i++) {
                if(All_Moves[i].id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].id << ",";
                }

                // No need to check since strings won't have INT_MAX
                std::cout << All_Moves[i].identifier << ",";

                if(All_Moves[i].generation_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].generation_id << ",";
                }
                
                if(All_Moves[i].type_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].type_id << ",";
                }
                
                if(All_Moves[i].power == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].power << ",";
                }

                if(All_Moves[i].pp == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].pp << ",";
                }
                
                if(All_Moves[i].accuracy == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].accuracy << ",";
                }
                
                if(All_Moves[i].priority == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].priority << ",";
                }

                if(All_Moves[i].target_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].target_id << ",";
                }
                
                if(All_Moves[i].damage_class_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].damage_class_id << ",";
                }
                
                if(All_Moves[i].effect_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].effect_id << ",";
                }

                if(All_Moves[i].effect_chance == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].effect_chance << ",";
                }
                
                if(All_Moves[i].contest_type_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].contest_type_id << ",";
                }
                
                if(All_Moves[i].contest_effect_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Moves[i].contest_effect_id << ",";
                }
                
                if(All_Moves[i].super_contest_effect_id == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Moves[i].super_contest_effect_id << std::endl;
                }
            }
        }

        else if(!(filename.compare("pokemon_moves"))){
            while (std::getline(specified_file, file_line)) {
                pokemon_moves_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 528238; i++) {
                if(All_Pokemon_Moves[i].pokemon_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Moves[i].pokemon_id << ",";
                }

                if(All_Pokemon_Moves[i].version_group_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Moves[i].version_group_id << ",";
                }

                if(All_Pokemon_Moves[i].move_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Moves[i].move_id << ",";
                }

                if(All_Pokemon_Moves[i].pokemon_move_method_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Moves[i].pokemon_move_method_id << ",";
                }

                if(All_Pokemon_Moves[i].level == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Moves[i].level << ",";
                }

                if(All_Pokemon_Moves[i].order == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Pokemon_Moves[i].order << std::endl;
                }
            }
        }

        else if(!(filename.compare("pokemon_species"))){
            while (std::getline(specified_file, file_line)) {
                pokemon_species_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 898; i++) {
                if(All_Pokemon_Species[i].id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].id << ",";
                }

                // No need to check since strings won't have INT_MAX
                std::cout << All_Pokemon_Species[i].identifier << ",";

                if(All_Pokemon_Species[i].generation_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].generation_id << ",";
                }
                
                if(All_Pokemon_Species[i].evolves_from_species_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].evolves_from_species_id << ",";
                }
                
                if(All_Pokemon_Species[i].evolution_chain_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].evolution_chain_id << ",";
                }

                if(All_Pokemon_Species[i].color_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].color_id << ",";
                }
                
                if(All_Pokemon_Species[i].shape_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].shape_id << ",";
                }
                
                if(All_Pokemon_Species[i].habitat_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].habitat_id << ",";
                }

                if(All_Pokemon_Species[i].gender_rate == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].gender_rate << ",";
                }
                
                if(All_Pokemon_Species[i].capture_rate == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].capture_rate << ",";
                }
                
                if(All_Pokemon_Species[i].base_happiness == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].base_happiness << ",";
                }

                if(All_Pokemon_Species[i].is_baby == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].is_baby << ",";
                }
                
                if(All_Pokemon_Species[i].hatch_counter == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].hatch_counter << ",";
                }
                
                if(All_Pokemon_Species[i].has_gender_differences == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].has_gender_differences << ",";
                }

                if(All_Pokemon_Species[i].growth_rate_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].growth_rate_id << ",";
                }
                
                if(All_Pokemon_Species[i].forms_switchable == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].forms_switchable << ",";
                }
                
                if(All_Pokemon_Species[i].is_legendary == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].is_legendary << ",";
                }

                if(All_Pokemon_Species[i].is_mythical == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].is_mythical << ",";
                }
                
                if(All_Pokemon_Species[i].order == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Species[i].order << ",";
                }
                
                if(All_Pokemon_Species[i].conquest_order == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Pokemon_Species[i].conquest_order << std::endl;
                }
            }
        }

        else if(!(filename.compare("experience"))){
            while (std::getline(specified_file, file_line)) {
                experience_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 600; i++) {
                if(All_Experience[i].growth_rate_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Experience[i].growth_rate_id << ",";
                }

                if(All_Experience[i].level == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Experience[i].level << ",";
                }

                if(All_Experience[i].experience == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Experience[i].experience << std::endl;
                }
            }
        }

        else if(!(filename.compare("type_names"))){
            while (std::getline(specified_file, file_line)) {
                type_names_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 193; i++) {
                if(All_Type_Names[i].type_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Type_Names[i].type_id << ",";
                    }


                    if(All_Type_Names[i].local_language_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Type_Names[i].local_language_id << ",";
                    }

                    // No need to check since strings won't have INT_MAX
                    std::cout << All_Type_Names[i].name << std::endl;
            }
        }

        else if(!(filename.compare("pokemon_stats"))){
            while (std::getline(specified_file, file_line)) {
                pokemon_stats_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 6552; i++) {
                if(All_Pokemon_Stats[i].pokemon_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Stats[i].pokemon_id << ",";
                }

                if(All_Pokemon_Stats[i].stat_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Stats[i].stat_id << ",";
                }

                if(All_Pokemon_Stats[i].base_stat == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Stats[i].base_stat << ",";
                }

                if(All_Pokemon_Stats[i].effort == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Pokemon_Stats[i].effort << std::endl;
                }
            }
        }

        else if(!(filename.compare("stats"))){
            while (std::getline(specified_file, file_line)) {
                stats_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 8; i++) {
                    if(All_Stats[i].id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Stats[i].id << ",";
                    }

                    if(All_Stats[i].damage_class_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Stats[i].damage_class_id << ",";
                    }

                    // No need to check since strings won't have INT_MAX
                    std::cout << All_Stats[i].identifier << ",";
                    
                    if(All_Stats[i].is_battle_only == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Stats[i].is_battle_only << ",";
                    }
                    
                    if(All_Stats[i].game_index == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Stats[i].game_index << std::endl;
                    }
            }
        }

        else if(!(filename.compare("pokemon_types"))){
            while (std::getline(specified_file, file_line)) {
                pokemon_types_line_parse(file_line, line_number);
                line_number++;
            }

            for(i = 0; i < 1675; i++) {
                if(All_Pokemon_Types[i].pokemon_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Types[i].pokemon_id << ",";
                }

                if(All_Pokemon_Types[i].type_id == INT_MAX) {
                    std::cout << ",";
                }
                else {
                    std::cout << All_Pokemon_Types[i].type_id << ",";
                }

                if(All_Pokemon_Types[i].slot == INT_MAX) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << All_Pokemon_Types[i].slot << std::endl;
                }
            }
        }

        // We aren't required to scan in EVERY file, so write a nice message explaining that
        else{
            std::cout << "File is not handled" << std::endl;
        }

        specified_file.close();
    }

    // If not in the share folder in pyrite, search using the $HOME environment
    else {
        std::string path = strcat(std::getenv("HOME"), "/.poke327/pokedex/pokedex/data/csv/");

        specified_file.open(path + filename + ".csv", std::fstream::in);

        // If the file can be found, search the specified file
        if(specified_file.is_open()){
            int i;
            int line_number = 1;
            std::string file_line;

            // Throw out the first line with the names of the parameters
            std::getline(specified_file, file_line);

            if(!(filename.compare("pokemon"))){
                while (std::getline(specified_file, file_line)) {
                    pokemon_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 1092; i++) {
                    if(All_Pokemon[i].id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].id << ",";
                    }

                    // No need to check since strings won't have INT_MAX
                    std::cout << All_Pokemon[i].identifier << ",";

                    if(All_Pokemon[i].species_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].species_id << ",";
                    }
                    
                    if(All_Pokemon[i].height == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].height << ",";
                    }
                    
                    if(All_Pokemon[i].weight == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].weight << ",";
                    }

                    if(All_Pokemon[i].base_experience == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].base_experience << ",";
                    }
                    
                    if(All_Pokemon[i].order == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon[i].order << ",";
                    }
                    
                    if(All_Pokemon[i].is_default == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Pokemon[i].is_default << std::endl;
                    }
                }
            }

            else if(!(filename.compare("moves"))){
                while (std::getline(specified_file, file_line)) {
                    moves_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 844; i++) {
                    if(All_Moves[i].id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].id << ",";
                    }

                    // No need to check since strings won't have INT_MAX
                    std::cout << All_Moves[i].identifier << ",";

                    if(All_Moves[i].generation_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].generation_id << ",";
                    }
                    
                    if(All_Moves[i].type_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].type_id << ",";
                    }
                    
                    if(All_Moves[i].power == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].power << ",";
                    }

                    if(All_Moves[i].pp == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].pp << ",";
                    }
                    
                    if(All_Moves[i].accuracy == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].accuracy << ",";
                    }
                    
                    if(All_Moves[i].priority == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].priority << ",";
                    }

                    if(All_Moves[i].target_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].target_id << ",";
                    }
                    
                    if(All_Moves[i].damage_class_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].damage_class_id << ",";
                    }
                    
                    if(All_Moves[i].effect_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].effect_id << ",";
                    }

                    if(All_Moves[i].effect_chance == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].effect_chance << ",";
                    }
                    
                    if(All_Moves[i].contest_type_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].contest_type_id << ",";
                    }
                    
                    if(All_Moves[i].contest_effect_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Moves[i].contest_effect_id << ",";
                    }
                    
                    if(All_Moves[i].super_contest_effect_id == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Moves[i].super_contest_effect_id << std::endl;
                    }
                }
            }

            else if(!(filename.compare("pokemon_moves"))){
                while (std::getline(specified_file, file_line)) {
                    pokemon_moves_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 528238; i++) {
                    if(All_Pokemon_Moves[i].pokemon_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].pokemon_id << ",";
                    }

                    if(All_Pokemon_Moves[i].version_group_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].version_group_id << ",";
                    }

                    if(All_Pokemon_Moves[i].move_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].move_id << ",";
                    }

                    if(All_Pokemon_Moves[i].pokemon_move_method_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].pokemon_move_method_id << ",";
                    }

                    if(All_Pokemon_Moves[i].level == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].level << ",";
                    }

                    if(All_Pokemon_Moves[i].order == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Pokemon_Moves[i].order << std::endl;
                    }
                }
            }

            else if(!(filename.compare("pokemon_species"))){
                while (std::getline(specified_file, file_line)) {
                    pokemon_species_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 898; i++) {
                    if(All_Pokemon_Species[i].id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].id << ",";
                    }

                    // No need to check since strings won't have INT_MAX
                    std::cout << All_Pokemon_Species[i].identifier << ",";

                    if(All_Pokemon_Species[i].generation_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].generation_id << ",";
                    }
                    
                    if(All_Pokemon_Species[i].evolves_from_species_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].evolves_from_species_id << ",";
                    }
                    
                    if(All_Pokemon_Species[i].evolution_chain_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].evolution_chain_id << ",";
                    }

                    if(All_Pokemon_Species[i].color_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].color_id << ",";
                    }
                    
                    if(All_Pokemon_Species[i].shape_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].shape_id << ",";
                    }
                    
                    if(All_Pokemon_Species[i].habitat_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].habitat_id << ",";
                    }

                    if(All_Pokemon_Species[i].gender_rate == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].gender_rate << ",";
                    }
                    
                    if(All_Pokemon_Species[i].capture_rate == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].capture_rate << ",";
                    }
                    
                    if(All_Pokemon_Species[i].base_happiness == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].base_happiness << ",";
                    }

                    if(All_Pokemon_Species[i].is_baby == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].is_baby << ",";
                    }
                    
                    if(All_Pokemon_Species[i].hatch_counter == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].hatch_counter << ",";
                    }
                    
                    if(All_Pokemon_Species[i].has_gender_differences == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].has_gender_differences << ",";
                    }

                    if(All_Pokemon_Species[i].growth_rate_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].growth_rate_id << ",";
                    }
                    
                    if(All_Pokemon_Species[i].forms_switchable == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].forms_switchable << ",";
                    }
                    
                    if(All_Pokemon_Species[i].is_legendary == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].is_legendary << ",";
                    }

                    if(All_Pokemon_Species[i].is_mythical == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].is_mythical << ",";
                    }
                    
                    if(All_Pokemon_Species[i].order == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].order << ",";
                    }
                    
                    if(All_Pokemon_Species[i].conquest_order == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Pokemon_Species[i].conquest_order << std::endl;
                    }
                }
            }

            else if(!(filename.compare("experience"))){
                while (std::getline(specified_file, file_line)) {
                    experience_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 600; i++) {
                    if(All_Experience[i].growth_rate_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Experience[i].growth_rate_id << ",";
                    }

                    if(All_Experience[i].level == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Experience[i].level << ",";
                    }

                    if(All_Experience[i].experience == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Experience[i].experience << std::endl;
                    }
                }
            }

            else if(!(filename.compare("type_names"))){
                while (std::getline(specified_file, file_line)) {
                    type_names_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 193; i++) {
                    if(All_Type_Names[i].type_id == INT_MAX) {
                            std::cout << ",";
                        }
                        else {
                            std::cout << All_Type_Names[i].type_id << ",";
                        }


                        if(All_Type_Names[i].local_language_id == INT_MAX) {
                            std::cout << ",";
                        }
                        else {
                            std::cout << All_Type_Names[i].local_language_id << ",";
                        }

                        // No need to check since strings won't have INT_MAX
                        std::cout << All_Type_Names[i].name << std::endl;
                }
            }

            else if(!(filename.compare("pokemon_stats"))){
                while (std::getline(specified_file, file_line)) {
                    pokemon_stats_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 6552; i++) {
                    if(All_Pokemon_Stats[i].pokemon_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Stats[i].pokemon_id << ",";
                    }

                    if(All_Pokemon_Stats[i].stat_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Stats[i].stat_id << ",";
                    }

                    if(All_Pokemon_Stats[i].base_stat == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Stats[i].base_stat << ",";
                    }

                    if(All_Pokemon_Stats[i].effort == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Pokemon_Stats[i].effort << std::endl;
                    }
                }
            }

            else if(!(filename.compare("stats"))){
                while (std::getline(specified_file, file_line)) {
                    stats_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 8; i++) {
                        if(All_Stats[i].id == INT_MAX) {
                            std::cout << ",";
                        }
                        else {
                            std::cout << All_Stats[i].id << ",";
                        }

                        if(All_Stats[i].damage_class_id == INT_MAX) {
                            std::cout << ",";
                        }
                        else {
                            std::cout << All_Stats[i].damage_class_id << ",";
                        }

                        // No need to check since strings won't have INT_MAX
                        std::cout << All_Stats[i].identifier << ",";
                        
                        if(All_Stats[i].is_battle_only == INT_MAX) {
                            std::cout << ",";
                        }
                        else {
                            std::cout << All_Stats[i].is_battle_only << ",";
                        }
                        
                        if(All_Stats[i].game_index == INT_MAX) {
                            std::cout << std::endl;
                        }
                        else {
                            std::cout << All_Stats[i].game_index << std::endl;
                        }
                }
            }

            else if(!(filename.compare("pokemon_types"))){
                while (std::getline(specified_file, file_line)) {
                    pokemon_types_line_parse(file_line, line_number);
                    line_number++;
                }

                for(i = 0; i < 1675; i++) {
                    if(All_Pokemon_Types[i].pokemon_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Types[i].pokemon_id << ",";
                    }

                    if(All_Pokemon_Types[i].type_id == INT_MAX) {
                        std::cout << ",";
                    }
                    else {
                        std::cout << All_Pokemon_Types[i].type_id << ",";
                    }

                    if(All_Pokemon_Types[i].slot == INT_MAX) {
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << All_Pokemon_Types[i].slot << std::endl;
                    }
                }
            }

            // We aren't required to scan in EVERY file, so write a nice message explaining that
            else{
                std::cout << "File is not handled" << std::endl;
            }

            specified_file.close();
        }

        // Neither of our 2 required filepaths have the specified file, so give an error message
        else{
            std::cout << "File not found: Run the program again with a valid filename" << std::endl << "(Remember to omit the .csv and the path!)" << std::endl;
        }
    }
}