/*--------------/
ALH
player.h
24/08/17
/--------------*/
#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_set>
#include <string>
#include "JsonBox.h"
using namespace std;

#include "creature.h"

class EntityManager;

class Player : public Creature {
public:

    //Name of the player's class. Class may be Fighter, Rogue etc
    string className; //not a C++ class, but a game class/team/group, i.e Fighter or Rogue

    //Level of the player
    unsigned int level;

    //Ids of areas viisted by the player
    unordered_set<string> visitedAreas;

    //Constructors
    Player(string name, int hp, int strength, int agility, double evasion, unsigned int xp, unsigned int level, string className);
    Player();
    Player(JsonBox::Value &saveData, JsonBox::Value &areaData, EntityManager *mgr);

    //Calculates the total experience required to reach a certain level
    unsigned int xpToLevel(unsigned int level);

    //Level the player to the next level if it has enough experience to do so, returning true id it could level up, false otherwise
    bool levelUp();

    //Create a JSON object representation of the player
    JsonBox::Object toJson();

    //Save the player to a file named after them
    void save(EntityManager *mgr);

    //Attempt to load all data from the JSON value
    void load(JsonBox::Value &saveData, EntityManager *mgr);
    void loadArea(JsonBox::Value &areaData, EntityManager *mgr);


};


#endif
