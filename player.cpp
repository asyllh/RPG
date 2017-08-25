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

Player::Player() : Player::Player("", 0, 0, 0, 0.0, 0, 1, "nullid")
{
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

//Attempt to load all data from the JSON value
void Player::load(JsonBox::Value &saveData, EntityManager *mgr){

    //Load data shared with Creature
    Creature::load(saveData, mgr);

    //Load optional variables
    JsonBox::Object o = saveData.getObject();

    this->className = o["className"].getString();
    this->level = o["level"].getInteger();

    return;
}

void Player::loadArea(JsonBox::Value &areaData, EntityManager *mgr) {

    //Load the area
    JsonBox::Object o = areaData.getObject();
    for(auto area : o){
        string key = area.first;
        mgr->getEntity<Area>(key)->load(area.second, mgr);
        this->visitedAreas.insert(key);
    }

    return;
}

//Calculate the total experience required to reach a certain level
unsigned int Player::xpToLevel(unsigned int level) {
    return (unsigned int)(1.5 * pow(this->level, 3));
}

//Level the player up to the next level if it has enough experience, returning true if player can level up, false otherwise
bool Player::levelUp() {

    //Can't level up if there's not enough experience
    if(this->xp < xpToLevel(this->level + 1)){
        return false;
    }

    //advance to the next level
    ++level;

    /*Variables to keep track of stat changes and their associated multipliers, which depends on the class.
     * The multiplier affects how much that stat increases in level, and is higher if the class specialises
     * in that stat [hp, agility, strength]*/
    unsigned int statIncreases[3] = {0, 0, 0};
    float statMultipliers[3] = {0, 0, 0};
    statMultipliers[0] = 13.0;
    statMultipliers[1] = this->className == "Fighter" ? 8.0 : 6.0;
    statMultipliers[2] = this->className == "Rogue" ? 8.0 : 6.0;

    //Compute the stat increases for each stat
    for(int i = 0; i < 3; ++i){
        float base = tanh(this->level / 30.0) * ((this-> level % 2) + 1);
        statIncreases[i] += int(1 + statMultipliers[1] * base);
    }

    //Adjust all of the stats accordingly
    this->hp += statIncreases[0];
    this->maxHp += statIncreases[0];
    this->strength += statIncreases[1];
    this->agility += statIncreases[2];

    //Tell user that they grew a level, what the increases were, and what their stats are now.
    cout << this->name << " grew to level " << level << "!\n";
    cout << "Health +" << statIncreases[0] << " -> " << this->maxHp << endl;
    cout << "Strength +" << statIncreases[1] << " -> " << this->strength << endl;
    cout << "Agility +" << statIncreases[2] << " -> " << this->agility << endl;
    cout << "--------------------------\n";

    return true;

}






















































