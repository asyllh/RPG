/* entityManager.h 23/08/2017 */

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <string>
#include <map>
using namespace std;

#include "entity.h"

class EntityManager{
private:
    map<string, Entity*> data;/* each entity is stored in a map, which is accessible in ways similar to an array, but instead
    of indexing each element by an integer, each element (in this case a pointer to an Entity) is indexed by a string.
    This nicely mirrors the structure of a JSON file where each unique key gives a JSON value
    Note: while abtract classes such as Entity cannot exists as objects, they can exist as pointers.
    But if we can't have any actual Entity objects, what do the pointers point to?!
    C++ has a feature where a pointer to a derived class can be stripped back and reduced to a pointer to its base class.
    This means that we can create Item or Door entities and then store pointers to them in the map, even though the
    types don't match up.
    The problem is, we won't then be able to access any member variables or functions specific to Item or Door, because an Entity
    doesn't know about those.
    Luckily, C++ allows us to convert a pointer to a case class back to a pointer to a derived class, giving us access to all those
    member variables.*/

public:
    //Load the JSON file and determine which map to save the data to, according to the type T
    template<typename T>
            void loadJson(string filename); /*function template called loadJson, which will read the JSON file "filename"
            and add all the entities described in that file to the map.
            The template argument passed to loadJson determines what kind of entity it should try and load from the file.
            loadJson won't handle any loading of individual entities, but instead will find all the keys in the JSON file
            and create a new entity by passing the corresponding value to the entity's constructor. This is where we'll be converting
            derived pointers to base pointers.*/

    //return the entity given by id
    template<typename T>
            T* getEntity(string id);/* when this function is given an entity type and an id, it'll find the entity with that
            id and return a pointer to it. This is where we'll be converting base pointers back to derived pointers.*/

    //Constructor
    EntityManager();

    //Destructor
    ~EntityManager();

};

//Convert a derived entity type to its id prefix, e.g. Item -> 'item'
template <typename T>
string entityToString(); /* this function is specialised to each possible template argument T, and given an entity type,
such as Item or Door, will return a string corresponding to that entity, such as 'item' or 'door'*/





#endif