/*--------------/
ALH
weapon.h
23/08/2017
/--------------*/
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "JsonBox.h"
using namespace std;

#include "item.h"

class EntityManager;

class Weapon : public Item {
public:
    int damage;

    //Constructors
    Weapon(string id, string name, string description, int damage);
    Weapon(string id, JsonBox::Value &v, EntityManager *mgr);

    void load(JsonBox::Value &v, EntityManager *mgr);
};

#endif
