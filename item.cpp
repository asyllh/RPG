/*--------------/
ALH
item.cpp
23/08/2017
/--------------*/

#include <string>
#include "JsonBox.h"
using namespace std;

#include "item.h"
#include "entity.h"
#include "entityManager.h"

Item::Item(string id, string name, string description) : Entity(id){

    this->name = name;
    this->description = description;

}
/*First constructor sets the name and description of the item according to the given arguments, and also calls the Entity
 * constructor with the given id.*/

Item::Item(string id, JsonBox::Value &v, EntityManager *mgr) : Entity(id){

    this->load(v, mgr);

}
/* Second constructor calls the Entity constructor before calling the load() function in order to load the Item from the given JSON file */

void Item::load(JsonBox::Value &v, EntityManager *mgr){
    JsonBox::Object o = v.getObject();
    this->name = o["name"].getString();
    this->description = o["description"].getString();
    return;
}
/*The JsonBox::Value will not be an entire JSON file, but instead just the value corresponding to a single key extracted
by the Entity Manager.By converting the value into a JsonBox::Object, we can access that value like an std::map and extract
 all the information we want, namely the item name and description. We then convert the returned values into strings
 (because o["name"] returns a JsonBox::Value) which are assigned to the Item.*/
//See note on Items page of tutorial for reason why we create a load function if it's only ever called by one constructor.
