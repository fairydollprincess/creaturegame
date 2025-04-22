//
// Created by doll on 4/21/25.
//
// Holds the pokemon class definition.
//

#ifndef POKEMON_H
#define POKEMON_H

enum PkmnType {
    FAIRY,
    NORMAL,
    FIRE,
    DRAGON,
    FIGHTING
};
string toString(PkmnType type) {
    switch (type) {
        default: return "???";
        case FAIRY: return "fairy";
        case NORMAL: return "normal";
        case FIRE: return "fire";
        case DRAGON: return "dragon";
        case FIGHTING: return "fighting";
    }
}
// compares types and makes an attack stronger if applicable: 0.5 (not very effective), 1 (normally effective),
// 2 (super effective)
float compareType(const PkmnType defendingType, const PkmnType attackingType) {
    if(defendingType == NORMAL) {
        if (attackingType == FIGHTING) {
            return 2;
        }
    } else if (defendingType == FIRE) {
        if (attackingType == FAIRY || attackingType == FIRE) {
            return 0.5;
        }
    } else if (defendingType == DRAGON) {
        if (attackingType == FIRE) {
            return 0.5;
        }
        if (attackingType == FAIRY) {
            return 2;
        }
    } else if (defendingType == FAIRY) {
        if (attackingType == DRAGON) {
            return 0;
        }
    }
    return 1;
}

/** contains description of a pokemon, its hp, and its attacks */
class Pokemon {
public:
    int hp;
    const Attack* attack1, *attack2;
    string name;
    int attackStrength;
    int defense;
    PkmnType type;
    Pokemon(const string& name, PkmnType type, int hp, int attackStrength, int defense, const Attack* attack1,
        const Attack* attack2) {
        this->name = name;
        this->type = type;
        this->hp = hp;
        this->attackStrength = attackStrength;
        this->defense = defense;
        this->attack1 = attack1;
        this->attack2 = attack2;
    }
};
#endif //POKEMON_H
