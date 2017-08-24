/* armor.cpp 23/08/2017 */

#include <string>
#include "JsonBox.h"
using namespace std;

#include "armor.h"
#include "item.h"
#include "entityManager.h"

Armor::Armor(string id, string name, string description, int defence) : Item(id, name, description){
    this->defence = defence;
}

Armor::Armor(string id, JsonBox::Value& v, EntityManager* mgr) : Item(id, v, mgr) {
    this->load(v, mgr);
}

void Armor::load(JsonBox::Value& v, EntityManager* mgr){
    JsonBox::Object o = v.getObject();
    this->defence = o["defence"].getInteger();
    return;
}
