/* weapon.cpp 23/08/2017 */

#include <string>
#include "JsonBox.h"
using namespace std;

#include "weapon.h"
#include "item.h"
#include "entityManager.h"

Weapon::Weapon(string id, string name, string description, int damage) : Item(id, name, description) {
    this->damage = damage;
}

Weapon::Weapon(string id, JsonBox::Value& v, EntityManager* mgr) : Item(id, v, mgr) {
    this->load(v, mgr);
}

void Weapon::load(JsonBox::Value& v, EntityManager* mgr) {
    JsonBox::Object o = v.getObject();
    this->damage = o["damage"].getInteger();
    return;
}
