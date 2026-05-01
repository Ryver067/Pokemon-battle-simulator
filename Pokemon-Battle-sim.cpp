#include <iostream>
#include <fstream> // for file reading
#include <vector>
#include <string>
#include "json.hpp" // for JSON library

//using a namespace for convenience
using json = nlohmann::json;

int get_pokemon_total_stats (const json& pokedex, std::string name) {
    //we loop through the pokedex to find the pokemon with the given name
    for (const auto& pokemon : pokedex) {
       // to access nested data
       if (pokemon["name"]["english"]==name) {
        int hp = pokemon["base"]["HP"];
        int attack = pokemon["base"]["Attack"];
        int defense = pokemon["base"]["Defense"];
        int sp_attack = pokemon["base"]["Sp. Attack"];
        int sp_defense = pokemon["base"]["Sp. Defense"];
        int speed = pokemon["base"]["Speed"];
        return hp + attack + defense + sp_attack + sp_defense + speed; // Return the total stats
       }   
     }
    return 0; // Return 0 if pokemon not found
}

int main(){
    //THE SETUP 
    //Hardcoding the teams for simplicity
    std::vector<std::string> team1 = {"Garchomp", "Rotom-Wash", "Scizor", "Infernape", "Blissey", "Gliscor"};
    std::vector<std::string> team2 = {"Salamence", "Gengar", "Tyranitar", "Excadrill", "Starmie", "Breloom"};

      //THE DATAT
      // ifstream stands for "Input File Stream". It opens the file for reading.
    std::ifstream file("pokedex.json");
   
    if (!file.is_open()) {
        std::cerr << "Error: Could not find pokedex.json!" << std::endl;
        return 1;
    }
    json pokedex;
    file >> pokedex; // Read the JSON data from the file into the pokedex variable
    file.close(); // Close the file after reading

    //The Logic 
    int WinsA = 0;
    int WinsB = 0;

    std::cout << "-----Pokemond Battle Simulator-----" <<std::endl;

    for (int i =0; i < 6; i++) {
        int statsA = get_pokemon_total_stats(pokedex, team1[i]);
        int statsB = get_pokemon_total_stats(pokedex, team2[i]);
    
        std::cout << "Round " << (i + 1) << ": " << team1[i] << " vs " << team2[i] << " -> ";
        if (statsA >statsB){
            std::cout << team1[i] << " Wins!" << std::endl;
            WinsA++;
        }
        else if (statsB > statsA) {
            std::cout << team2[i] << " Wins!" << std::endl;
            WinsB++;
        }else{
            std::cout << "It's a tie!" << std::endl;
        }
        
    }

//FINAL--RESULTS
std::cout << "\n--- Final Results --- " << std::endl;
 if(WinsA > WinsB) {
    std::cout << "TEAM A IS THE CHAMPION!" << std::endl;
 }else if(WinsB > WinsA) {
    std::cout << "TEAM B IS THE CHAMPION!" << std::endl;
 }else{
    std::cout << "It's a tie!" << std::endl;
 }
}