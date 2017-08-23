/* main.cpp 23/08/2017 */

#include <cstdlib>
#include <ctime>
#include "JsonBox.h"
using namespace std;

#include "item.h"
#include "weapon.h"
#include "armor.h"
#include "entityManager.h"

//Keeps track of items, weapons, creatures etc.
EntityManager entityManager;

int main (){

    //Load the entities
    entityManager.loadJson<Item>("item.json");
    entityManager.loadJson<Weapon>("weapon.json");
    entityManager.loadJson<Armor>("armor.json");

    //Seed the random number generator with the system time, so the random numbers produced by rand() will be different each time
    srand(time(nullptr));

}
