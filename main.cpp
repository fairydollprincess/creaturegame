#include <iostream>
#include <cstdlib>
using namespace std;

class Attack; // this is here because Pokemon class uses stuff from Attack class (further down)
#include "Pokemon.h"
#include "Attack.h"

// lets player (main or enemy) choose their pokemon
// takes in a team of pokemon and dispays it, asks user what pokemon they want to use, has user input desired pokemon
Pokemon* choosePokemon(Pokemon team[], int teamSize) {
    cout << "Choose a pokemnon!" << endl;
    for (int i = 0; i < teamSize; i++) {
        cout << i << " - " << team[i].name << endl;
    }
    int pokemonSelection;
    cin >> pokemonSelection;
    // make sure selection is within the team size
    while (pokemonSelection < 0 || pokemonSelection >= teamSize) {
        cout << "Choose a pokemon in your team's range" << endl;
        cin >> pokemonSelection;
    }
    return &(team[pokemonSelection]);
}

// take in a team of pokemon and check if any of them are alive
bool remainingPokemon(Pokemon team[], int teamSize) {
    for (int i = 0; i < teamSize; i++) {
        if (team[i].hp > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(time(0)) ; // used to make random # generator work

    int teamSize = 3;
    Pokemon team[] = {Pokemon("Skitty", NORMAL, 25, 3, 5, &TACKLE, &GROWL),
        Pokemon("Jigglypuff", FAIRY, 30, 3, 2, &GROWL, &FAIRYWIND),
        Pokemon("Dratini", DRAGON, 20, 6, 4, &LEER, &TWISTER)};
    Pokemon enemyTeam[] = {Pokemon("Torchick", FIRE, 20, 5, 3, &GROWL, &EMBER),
        Pokemon("Wigglytuff", FAIRY, 25, 3, 2, &FAIRYWIND, &POUND),
        Pokemon("Evee", NORMAL, 30, 2, 4, &TACKLE, &GROWL)};

    // main player chooses their pokemon
    Pokemon* mainPokemon = choosePokemon(team, 3);

    // enemy player chooses their pokemon
    Pokemon* enemyPokemon = choosePokemon(enemyTeam, 3);

    // announce main pokemon
    cout << "Go " << mainPokemon->name << "!" << endl;

    // check if any pokemon are alive for main and enemy, continue fight until one side doesn't have any pokemon
    while (remainingPokemon(team, 3) && remainingPokemon(enemyTeam, 3)) {
        // continue fight while current pokemon are live
        while (mainPokemon->hp > 0 && enemyPokemon->hp > 0) {
            cout << endl << mainPokemon->name << " HP: " << mainPokemon->hp << endl;
            cout << enemyPokemon->name << " HP: " << enemyPokemon->hp << endl << endl;

            // asks if main pokemon wants to attack or if they want to switch out their pokemon
            cout << "Do you want to fight (1) or switch out your pokemon (2)?" << endl;
            int response;
            cin >> response;
            if (response == 1) {
                cout << mainPokemon->attack1->attackName << " (1) or " << mainPokemon->attack2->attackName << " (2)? " ;
                int attackSelection;
                cin >> attackSelection;
                cout << endl;
                // main pokemon uses tackle or growl and decrease enemy's HP accordingly. growl weakens enemies attack
                if (attackSelection == 1) {
                    mainPokemon->attack1->use(mainPokemon, enemyPokemon);
                }
                if (attackSelection == 2) {
                    mainPokemon->attack2->use(mainPokemon, enemyPokemon);
                }
            }
            if (response == 2) {
                mainPokemon = choosePokemon(team, 3);
            }

            // enemy pokemon uses tackle or growl and decrease enemy's HP accordingly
            if (rand() & 1) {
                enemyPokemon->attack1->use(enemyPokemon, mainPokemon);
            }
            else{
                enemyPokemon->attack2->use(enemyPokemon, mainPokemon);
            }
        }

        /** 1) switch to new pokemon after one is defeated 2) keep switching out until no pokemon are left
         * 3) the player with the remaining pokemon wins **/

        /** if main pokemon dies, check if there are remaining pokemon, then have user switch to a new pokemon
        if there's no remaining pokemon, say they lost **/
        if (mainPokemon->hp <= 0) {
            cout << mainPokemon->name << " got knocked out" << endl;
            if (remainingPokemon(team, 3)) {
                mainPokemon = choosePokemon(team, 3);
            }
        }

        if (enemyPokemon->hp <= 0) {
            cout << enemyPokemon->name << " got knocked out" << endl;
            if (remainingPokemon(enemyTeam, 3)) {
                enemyPokemon = choosePokemon(enemyTeam, 3);
            }
        }
    }

    // announce winner
    if (enemyPokemon->hp <= 0) {
        cout << mainPokemon->name << " wins!" << endl;
    }
    if (mainPokemon->hp <= 0) {
        cout << enemyPokemon->name << " wins!" << endl;
    }
    return 0;
}