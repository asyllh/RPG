/*--------------/
ALH
entity.h
23/08/2017
/--------------*/

#ifndef ENTITY_H
#define ENTITY_H

#include "JsonBox.h"
#include <string>
using namespace std;

class EntityManager; /*foward declaration of the EntityManager - necessary because whilst the EntityManager needs to know about the
Entity class, each Entity may also need access to the EntityManager! Because two files cannot #include each other, we use a forward
declaration to tell the compiler that EntityManager will exist, even it it doesn't yet.*/

class Entity{
public:
    string id;/*the id member variable is a string that helps identify the object, and will be used as the entity's key in the JSON
    file as well as internally when getting an entity from the EntityManager.*/

    Entity(string id){ //constructor
        this->id = id;
    }

    //Destructor must be made virtual as all derived classes are treated as Entity in the EntityManager

    virtual ~Entity(){} //virtual destructor

    //Pure virtual function stops Entity from being instantiated and forces it to be implemented in all derived types
    virtual void load(JsonBox::Value &v, EntityManager *mgr) = 0;
    /* pure virutal function called "load" which every entity derived from Entity must implement.
     * By making it virtual, we're alllowing it to be overridden in the derived classes, and by
     * making it pure (the "=0" part) we turn Entity into an "abstract class"
     * Abstract classes cannot have any objects, so whilst the Item, Area, Creature etc. entities we
     * define in the future will all be a kind of Entity, we can't create an Entity by itself.
     * One of the arguments is a JsonBox::Value, which is a representation of the entity being
     * loaded into JSON form.
     */

};

#endif


