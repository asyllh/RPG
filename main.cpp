/*--------------/
ALH
main.cpp
23/08/2017
/--------------*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <map>
#include "JsonBox.h"
using namespace std;

#include "item.h"
#include "weapon.h"
#include "armour.h"
#include "inventory.h"
#include "creature.h"
#include "player.h"
#include "dialogue.h"
#include "area.h"
#include "door.h"
#include "battle.h"
#include "entityManager.h"

//Keeps track of items, weapons, creatures etc.
EntityManager entityManager;

int main (){

    //Load the entities
    entityManager.loadJson<Item>("items.json");
    entityManager.loadJson<Weapon>("weapons.json");
    entityManager.loadJson<Armour>("armour.json");
    entityManager.loadJson<Creature>("creatures.json");
    entityManager.loadJson<Door>("doors.json");
    entityManager.loadJson<Area>("areas.json");

    //Seed the random number generator with the system time, so the random numbers produced by rand() will be different each time
    srand(time(nullptr));

}
