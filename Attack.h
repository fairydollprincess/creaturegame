//
// Created by doll on 4/21/25.
//
// Holds information about pokemon attacks.
//

#ifndef ATTACK_H
#define ATTACK_H

// contains description of an attack and its damage
class Attack {
public:
    string attackName;
    int power;
    PkmnType type;
    Attack(string attackName, int damage, PkmnType type) {
        this->attackName = attackName;
        this->power = damage;
        this->type = type;
    }

    // uses an attack
    virtual void use(Pokemon * source, Pokemon * target) const {
        float typeMultiplier = compareType(target->type, type);
        // calculate damage based on pokemon attack and defense and types
        int damage = ((power * source->attackStrength) / target->defense) * typeMultiplier;
        // base case to keep damage positive so it doesn't heal the pokemon HP
        if (damage <= 0) {
            damage = 1;
        }
        int chanceOfAttack = rand() % 3;
        switch (chanceOfAttack) {
            default: target->hp -= damage;
            cout << source->name << " used " << attackName << endl;
            if (typeMultiplier < 1) {
                cout << "It was not very effective" << endl;
            }
            if (typeMultiplier > 1) {
                cout << "It was super effective" << endl;
            }
            break;
            case 0: cout << source->name << "'s attack missed" << endl;
            break;
            case 1: target->hp -= damage * 2;
            cout << source->name << " used " << attackName << endl;
            cout << source->name << " did a critical hit" << endl;
            break;
        }
    }
};
// lowers the enemies defense (implements leer)
class LowerDefense : public Attack {
public:
    LowerDefense(const string& attackName, int damage, PkmnType type): Attack(attackName, damage, type) {};
     void use(Pokemon * source, Pokemon * target) const override {
         cout << source->name << " used " << attackName << endl;
         target->defense -= power;
         if (target->defense <= 0) {
             target->defense = 1;
             cout << target->name << " defense can't drop any lower" << endl;
         }
         else {
             cout << target->name << " defense dropped" << endl;
         }
    }
};

// lowers the enemies attack (implements growl)
class LowerAttack : public Attack {
public:
    LowerAttack(const string& attackName, int damage, PkmnType type): Attack(attackName, damage, type){};
    void use(Pokemon * source, Pokemon * target) const override {
        cout << source->name << " used " << attackName << endl;
        target->attackStrength -= power;
        if (target->attackStrength <= 0) {
            target->attackStrength = 1;
            cout << target->name << " attack can't drop any lower" << endl;
        }
        else {
            cout << target->name << " attack dropped to " << target->attackStrength << endl;
        }
    }
};

const Attack TACKLE("tackle", 5, NORMAL);
const LowerAttack GROWL("growl", 2, NORMAL);
const Attack POUND("pound", 6, NORMAL);
const LowerDefense LEER("leer", 2, NORMAL);
const Attack TWISTER("twister", 5, DRAGON);
const Attack EMBER("ember", 5, FIRE);
const Attack FAIRYWIND("fairy wind", 3, FAIRY);

#endif //ATTACK_H
