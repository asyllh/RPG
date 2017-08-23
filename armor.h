/* armor.h 23/08/2017 */
#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include "JsonBox.h"
using namespace std;

#include "item.h"

class EntityManager;

class Armor : public Item {
public:
    int defence;

    //Constructors
    Armor(string id, string name, string description, int defence);
    Armor(string id, JsonBox::Value& v, EntityManager* mgr);

    //Load the armor from the Json value
    void load(JsonBox::Value& v, EntityManager* mgr);

};


#endif
