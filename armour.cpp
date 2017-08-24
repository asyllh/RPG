/*--------------/
ALH
armour.cpp
23/08/2017
/--------------*/

#include <string>
#include "JsonBox.h"
using namespace std;

#include "armour.h"
#include "item.h"
#include "entityManager.h"

Armour::Armour(string id, string name, string description, int defence) : Item(id, name, description){
    this->defence = defence;
}

Armour::Armour(string id, JsonBox::Value &v, EntityManager *mgr) : Item(id, v, mgr) {
    this->load(v, mgr);
}

void Armour::load(JsonBox::Value &v, EntityManager *mgr){
    JsonBox::Object o = v.getObject();
    this->defence = o["defence"].getInteger();
    return;
}
