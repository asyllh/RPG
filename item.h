/* item.h 23/08/2017 */
/* Item class - will be used for anything the player can pick up and collect in their adventure through the dungeon.
 * Item class will also be used as a base class for Weapon and Armor - the Item class will define just the attributes they share,
 * specifically a name and a description.
 */
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "JsonBox.h"
using namespace std;

#include "entity.h"

class EntityManager; //Foward declaration of the EntityManager class, because we need to know of its existence.
/*Although Item isn't used directly by EntityManager, it is used in a template instantiation, so one of the files has to forward declare
instead of #include */

class Item : public Entity {
public:
    //Name and description of the item
    string name;
    string description;

    //Constructors
    /* Item inherits from the Entity base class and so shares the load function as well as taking an id variable in its constructor
     * arguments. The second constructor takes the same arguments as load, and is required by the EntityManager (as previously discussed).
     * We will not be using the first constructor, because all Items will be defined in JSON files, but it is useful if we want to hardcode
     * an Item into the game, hence it is included.
     */
    Item(string id, string name, string description);
    Item(string id, JsonBox::Value& v, EntityManager* mgr); //main constructor

    //Load the item information from the JSON value
    virtual void load(JsonBox::Value& v, EntityManager* mgr);

};



#endif
