/*--------------/
ALH
door.h
24/08/2017
/--------------*/
//door is an entity, and so it inherits from the Entity class
//Areas are connected by a Door
#ifndef DOOR_H
#define DOOR_H

#include <string>
#include <utility>
using namespace std;

#include "entity.h"

class Item;
class EntityManager;

class Door : public Entity{
public:
    //Door description, e.g. large wooden door, rusted iron gate
    string description;

    /* < 0 = open
     * == 0 = unlocked but closed
     * > 0 is locked and needs key to open
     */
    int locked;

    //If the player has the required key, then they can unlock the door
    Item* key;

    pair<string, string> areas; //pair of strings which contain the ids of the Areas the Door connects

    Door(string id, string description, pair<string, string> areas, int locked, Item* key = nullptr); //nullptr if no key is required
    Door(string id, JsonBox::Value &v, EntityManager *mgr);

    void load(JsonBox::Value &v, EntityManager *mgr);


};



#endif
