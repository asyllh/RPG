/*--------------/
ALH
inventory.h
24/08/2017
/--------------*/
/*items here refers to items, weapons and armor */
#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <utility> //for pairs
#include "JsonBox.h"
using namespace std;

#include "entityManager.h"

class Item;
class Weapon;
class Armour;

class Inventory{
private:
    /* We use a similar method here to in EntityManager, where we store a list of base pointers
     * WE use a list and not a vector as inventories are highly mutable.
     * This way they can also be efficiently sorted.
     * The first element of the pair stores a pointer to the item in the EntityManager, and the
     * second element stores the quantity of the item.
     */
    list<pair<Item*, int> > items;

    /*Given the Json value v which contains a list of items, weapons or armor of type T
     * load the T's into the storage list (either items, weapons or armor)
     */
    template <typename T>
            void load(JsonBox::Value &v, EntityManager *mgr);

    //Return a JSON representation of all the items of the type T
    template <typename T>
            JsonBox::Array jsonArray();

public:

    //Add an item to the inventory
    void add(Item *item, int count);

    //Remove the specific number of items from the inventory
    void remove(Item *item, int count);

    //Returns the count of the specified item
    int count(Item *item);
    template <typename T>
            int count(unsigned int n);

    //Return the nth item in the storage list
    template <typename T>
            T* get(unsigned int n);

    //Output a list of the items onto stdout, formatted nicely and numbered if required
    template <typename T>
            int print(bool label = false);

    //Remove all items from the inventory
    void clear();

    /*Merge the specified inventory with the current one, adding item quantities toegther if they already exist and adding the item
    into a new slot if they do not.*/
    void merge(Inventory *inventory);

    //Load the inventory from a JSON value
    Inventory(JsonBox::Value &v, EntityManager *mgr);
    Inventory() {}

    //Print the entire inventory; items, then weapons, then armor, but if inventory is empty, then output "Nothing"
    int print(bool label = false);

    //Get a JSON object representation of the inventory
    JsonBox::Object getJson();


};





#endif
