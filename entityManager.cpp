/*--------------/
ALH
entityManager.cpp
23/08/2017
/--------------*/

#include <string>
#include <map>
using namespace std;

#include "entityManager.h"
#include "item.h"
#include "weapon.h"
#include "armour.h"
#include "creature.h"
#include "area.h"
#include "door.h"

template <class T>
void EntityManager::loadJson(string filename) {

    JsonBox::Value v;
    v.loadFromFile(filename);

    JsonBox::Object o = v.getObject();
    for(auto entity : o){
        string key = entity.first;
        this->data[key] = dynamic_cast<Entity*>(new T(key, entity.second, this));
    }

}//end void EntityManager::loadJson
/* loadJson loads the JSON file as a JSON value (the entire set of data between the {} ) and then converts it into a JSON
 * object that will have keys and corresponding values.
 * A JsonBox::Object is very similar to an std::map, where each element contains not just a value, but also the key.
 * As we iterate over the object "entity" (where "entity" is the entity in the for loop condition) will contain both
 * the key and the value, so we extract the key and then create a new entity using the corresponding value (of type JsonBox::Value).
 * To create the entity, we assume that the type T (which will be some class derived from Entity, such as Item or Door) has a
 * constructor with the same arguments as Entity::load and call it, passing to it the key, value, and the EntityManager itself.
 * Because "data" (the map) contains pointers, we use the "new" keyword to allocate memory for the new entity, and then use
 * "dynamic_cast<Entity*>" to convert the resulting pointer of type T* to a pointer of type Entity*, which can then be stored in "data".
 */

template <class T>
T* EntityManager::getEntity(string id) {

    /* The id prefix should match to the type T, so take the first characters of the id up to the length of the prefix and
       compare the two */
    if(id.substr(0, entityToString<T>().size()) == entityToString<T>()){
        return dynamic_cast<T*>(this->data.at(id));
    }
    else{
        return nullptr;
    }

}//end T* EntityManager:;getEntity
/* getEntity simply gets the entity with key "id" from "data" before using "dynamic_cast<T*>" to convert it from a pointer of
 * type Entity* back to a pointer of type T*, which it then returns.
 * Before doing so, however, it used the entityToString function to check the that "id" matches up to the type T.
 * It assumes that all Items (using "Item" for example) have an "id" beginning with 'item', and if they don't, it will
 * return a nullptr instead. This still assumes that the data is named correctly (which we aren't enforcing).
 */

EntityManager::EntityManager() {} //Constructor - does nothing at all

EntityManager::~EntityManager() { // Destructor - deallocates all the memory allocated by "new" in loadJson.

    for(auto &entity : this->data){
        delete entity.second;
    }
}//end EntityManager::~EntityManager

//Template specialisations
template <> string entityToString<Item>() { return "item"; }
template <> string entityToString<Weapon>() { return "weapon"; }
template <> string entityToString<Armour>() { return "armour"; }
template <> string entityToString<Creature>() { return "creature"; }
template <> string entityToString<Area>() { return "area"; }
template <> string entityToString<Door>() { return "door"; }

//Template instantiations
template void EntityManager::loadJson<Item>(string);
template void EntityManager::loadJson<Weapon>(string);
template void EntityManager::loadJson<Armour>(string);
template void EntityManager::loadJson<Creature>(string);
template void EntityManager::loadJson<Area>(string);
template void EntityManager::loadJson<Door>(string);

template Item* EntityManager::getEntity<Item>(string);
template Weapon* EntityManager::getEntity<Weapon>(string);
template Armour* EntityManager::getEntity<Armour>(string);
template Creature* EntityManager::getEntity<Creature>(string);
template Area* EntityManager::getEntity<Area>(string);
template Door* EntityManager::getEntity<Door>(string);

/* NOTE: Whenever we add a new entity class, we must make sure to add an explcit instantiation or specialisation
 * for each of the function templates that corresponds to the new entity.
 * For example, when adding an Item class, we should add the following Specialisation or Instantiation */

//Specialisation:
/*
template <> string entityToString<Item>(){
    return "item";
}
*/

//Instatiation
/*
template void EntityManager::loadJson<Item>(string);
template Item* EntityManager::getEntity<Item>(string);
*/





























