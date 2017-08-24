/*--------------/
ALH
door.cpp
24/08/17
/--------------*/
#include <string>
#include <utility>
using namespace std;

#include "door.h"
#include "item.h"
#include "entity.h"
#include "entityManager.h"

Door::Door(string id, string description, pair<string, string> areas, int locked, Item* key) : Entity(id){
    this->description = description;
    this->areas = areas;
    this->locked = locked;
    this->key = key;

}

Door::Door(string id, JsonBox::Value &v, EntityManager *mgr) : Entity(id) {
    this->load(v, mgr);
}

void Door::load(JsonBox::Value &v, EntityManager *mgr) {
    JsonBox::Object o = v.getObject();
    this->description = o["description"].getString();
    this->locked = o["locked"].getInteger();
    if(o.find("key") != o.end()){
        this->key = mgr->getEntity<Item>(o["key"].getString());
    }
    JsonBox::Array a = o["areas"].getArray();
    if(a.size() == 2){
        this->areas.first = a[0].getString();
        this->areas.second = a[1].getString();
    }
    return;

}

