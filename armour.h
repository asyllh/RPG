/*--------------/
ALH
armour.h
23/08/2017
/--------------*/
#ifndef ARMOUR_H
#define ARMOUR_H

#include <string>
#include "JsonBox.h"
using namespace std;

#include "item.h"

class EntityManager;

class Armour : public Item {
public:
    int defence;

    //Constructors
    Armour(string id, string name, string description, int defence);
    Armour(string id, JsonBox::Value &v, EntityManager *mgr);

    //Load the armour from the Json value
    void load(JsonBox::Value &v, EntityManager *mgr);

};


#endif
