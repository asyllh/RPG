/*--------------/
ALH
player.cpp
24/08/17
/--------------*/
#include <unordered_set>
#include <cmath>
#include "JsonBox.h"
using namespace std;

#include "area.h"
#include "player.h"
#include "creature.h"
#include "entityManager.h"

Player::Player(string name, int hp, int strength, int agility, double evasion, unsigned int xp, unsigned int level,
               string className) : Creature("player", name, hp, strength, agility, evasion, xp){

    this->level = level;
    this->className = className;
}

Player::Player(JsonBox::Value &saveData, JsonBox::Value &areaData, EntityManager *mgr) : Player::Player() {
    this->load(saveData, mgr);
    this->loadArea(areaData, mgr);
}

JsonBox::Object Player::toJson(){
    JsonBox::Object o = Creature::toJson();

    o["classname"] = JsonBox::Value(this->className);
    o["level"] = JsonBox::Value(int(this->level));

    return o;
}

void Player::save(EntityManager *mgr) {

    //Construct JSON representation of the player and save it to a file
    JsonBox::Value v(this->toJson());
    v.writeToFile(this->name + ".json");

    //Construct a JSON object containing the areas the player has visited
    JsonBox::Object o;
    for(auto area : this->visitedAreas){
        o[area] = mgr->getEntity<Area>(area)->getJson();
    }

    JsonBox::Value v2(o);

    //Write the object to a file similar to the player data
    v2.writeToFile(this->name + "_areas.json");

    return;

}





















































