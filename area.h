/*--------------/
ALH
area.h
24/08/2017
/--------------*/
#ifndef AREA_H
#define AREA_H

#include <vector>
#include <string>
#include "JsonBox.h"
using namespace std;

#include "entity.h"
#include "inventory.h"
#include "creature.h"
#include "dialogue.h"

class EntityManager;
class Door;

/* Movement is achieved through the use of areas, which are contained units of space consisting of an inventory, a list of
creatures, and a dialogue */

class Area : public Entity{
public:
    //Dialogue in run whenever the area is entered
    Dialogue dialogue;

    //Items contained within the area. Not split into individual containers for simplicity
    Inventory items;

    //Links between rooms. Every door should have this as one of its area pointers.
    vector<Door*> doors;

    //Creatures contained within the area. Not pointers because we want unique instances of the creatures
    vector<Creature> creatures;

    //Constructors
    Area(string id, Dialogue dialogue, Inventory items, vector<Creature*> creatures);
    Area(string id, JsonBox::Value &v, EntityManager *mgr);

    //Load the area from the given JSON value
    void load(JsonBox::Value &v, EntityManager *mgr);

    //Return a JSON object representing the area
    JsonBox::Object getJson();

};


#endif

















































