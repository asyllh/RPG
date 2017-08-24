/*--------------/
ALH
area.cpp
24/08/17
/--------------*/
#include <vector>
#include <string>
#include "JsonBox.h"
using namespace std;

#include "area.h"
#include "door.h"
#include "entity.h"
#include "inventory.h"
#include "creature.h"
#include "dialogue.h"
#include "entityManager.h"

Area::Area(string id, Dialogue dialogue, Inventory items, vector<Creature*> creatures) : Entity(id){
    this->dialogue = dialogue;
    this->items = items;
    for(auto creature : creatures){
        this->creatures.push_back(*creature);
    }

}

Area::Area(string id, JsonBox::Value &v, EntityManager *mgr) : Entity(id){
    this->load(v, mgr);
}

void Area::load(JsonBox::Value &v, EntityManager *mgr) {

    JsonBox::Object o = v.getObject();

    //Build the dialogue - this is an optional parameter because it will not be saved when the area is modified
    if(o.find("dialogue") != o.end()){
        this->dialogue = Dialogue(o["dialogue"]);
    }

    //Build the inventory
    this->items = Inventory(o["inventory"], mgr);

    //Build the creatures list
    this->creatures.clear();
    for(auto creature : o["creatures"].getArray()){
        //create a mew acreature instance identical to the version in the entity manager
        Creature c(*mgr->getEntity<Creature>(creature.getString()));
        this->creatures.push_back(c);
    }

    //Attach doors
    if(o.find("doors") != o.end()){
        this->doors.clear();

        for(auto door : o["doors"].getArray()){
            Door* d = nullptr;

            //Each door is either an array of the type [id, locked] or a single id string
            if(door.isString()){
                d = mgr->getEntity<Door>(door.getString());
            }
            else{
                d = mgr->getEntity<Door>(door.getArray()[0].getString());
                d->locked = door.getArray()[1].getInteger();
            }

            this->doors.push_back(d);
        }
    }

    return;

}
//saving the area (check if this is what it actually does!)
JsonBox::Object Area::getJson() {
    JsonBox::Object o;
    //We don't need to save the dialogue because it doesn't change

    //Save the inventory
    o["inventory"] = this->items.getJson();

    //Save the creatures
    JsonBox::Array a;
    for(auto creature : this->creatures){
        a.push_back(JsonBox::Value(creature.id));
    }
    o["creatures"] = a;

    //Save the doors
    a.clear();

    for(auto door : this->doors){
        JsonBox::Array d;
        d.push_back(door->id);
        d.push_back(door->locked);
        a.push_back(d);
    }
    o["doors"] = a;
    return o;
}














































































