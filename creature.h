/*--------------/
ALH
creature.h
24/08/17
/--------------*/

#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <cstdlib>
#include "JsonBox.h"
using namespace std;

#include "entity.h"
#include "inventory.h"

class Area;
class EntityManager;
class Weapon;
class Armour;
class Door;

class Creature : public Entity{
public:

    // Name of the creature
    string name;

    //Creature stats
    int hp;
    int maxHp;
    int strength;
    int agility;
    double evasion;
    unsigned int xp;

    //Items that the creature possesses
    Inventory inventory;

    //Currently equipped weapon. Used as a pointer to an atlas entry, but not necessary. nullprt denotes that no weapon is equipped.
    Weapon* equippedWeapon;

    //Currently equipped armour
    Armour* equippedArmour;

    //Area the creature resides in. Used for player motion but also could be used for enemy AI
    string currentArea;

    //Constructors
    Creature(string id, string name, int hp, int strength, int agility, double evasion, unsigned int xp);
    Creature(string id, JsonBox::Value &v, EntityManager *mgr);

    /*Equip a weapon by setting the equipped weapon pointer. Currently a pointless function (simple enough
    to be rewritten each time) but handy if dual wielding is ever added, or shields etc.*/
    void equipWeapon(Weapon* weapon);

    //Equip the armour into its correct slot
    void equipArmour(Armour* armour);

    //Convert internal area id into a pointer
    Area* getAreaPtr(EntityManager* mgr);

    //attack the target creature, reducing their health if necessary
    int attack(Creature* target);

    /*Go through a door:
     * 0 = door is locked
     * 1 = door is unlocked using key
     * 2 = door is open */
    int traverse(Door* door);

    //Create a JSON object containing the creature data
    virtual JsonBox::Object toJson();

    //Attempt to load all data from the JSON value
    virtual void load(JsonBox::Value &v, EntityManager *mgr);

};


#endif
