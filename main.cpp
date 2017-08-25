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

//New character menu
Player startGame(); //function is defined after int main

//Character information menu, displays the items the player has, their current stats etc
void dialogueMenu(Player& player); //function is defined after int main

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

    Player player = startGame();

    //set the current area to be the first area in the atlas, placing the player there upon game start
    player.currentArea = "area_01";

    //play the game until a function breaks the loop and closes it
    while(1){

        //Mark the current player as visited
        player.visitedAreas.insert(player.currentArea);

        //pointer to the current area for convenience
        Area* areaPtr = player.getAreaPtr(&entityManager);

        //autosave the game
        player.save(&entityManager);

        //If the area has any creatures in it, start a battle with them
        if(areaPtr->creatures.size() > 0){
            //Create a vector of pointers to the creatures in the area
            vector<Creature*> combatants;
            cout << "You are attacked by ";
            for(int i = 0; i < areaPtr->creatures.size(); ++i){
                Creature* c = &(areaPtr->creatures[i]);
                combatants.push_back(c);
                cout << c->name << (i == areaPtr->creatures.size() - 1 ? "!\n" : ", ");
            }

            //Add the player to the combatant vector
            combatants.push_back(&player);

            //Run the battle

            Battle battle(combatants);
            battle.run();

            //If the player is still alive, grant them some experience, assuming that every creature was killed
            if(player.hp > 0){

                //Or use std::accumulate, but it requires an additional header
                unsigned int xp = 0;
                for(auto creature : areaPtr->creatures){
                    xp += creature.xp;
                }
                cout << "You gained " << xp << " experience!\n";
                player.xp += xp;

                //Remove the creatures from the area
                areaPtr->creatures.clear();

                //Restart the loop to force a save, then the game will carry on as usual
                continue;
            }
            //Otherwise the player is dead, so end the program
            else{
                cout << "\t------YOU DIED-------\nGame over.\n";
            }

        }//end if


        //Add the search and movement options to the dialogue
        Dialogue roomOptions = areaPtr->dialogue;
        for(auto door : areaPtr->doors){
            roomOptions.addChoice("Go through the " + door->description);
        }
        roomOptions.addChoice("Search");

        //Activate the current area's dialogue
        int result = roomOptions.activate();

        if(result == 0){
            dialogueMenu(player);
        }
        else if(result <= areaPtr->dialogue.size()){
            //Add more events here
        }
        else if(result < roomOptions.size()){

            Door* door = areaPtr->doors.at(result-areaPtr->dialogue.size() -1);
            int flag = player.traverse(door);

            switch(flag){
                default:
                case 0:
                    cout << "The " << door->description << " is locked.\n";
                    break;

                case 1:
                    cout << "You unlock the " << door->description << " and go through it.\n";
                    break;

                case 2:
                    cout << "You go through the " << door->description << ".\n";
                    break;

            }
        }
        else{
            cout << "You find:\n";
            areaPtr->items.print();
            player.inventory.merge(&(areaPtr->items));
            areaPtr->items.clear();
        }

    }

    return 0;

}

//create a new character or load an existing one
Player startGame(){

    /*Ask for a name and class
     * Name does not use a dialogue since dialogues only request options, not string input
     * could be generalised into its own text input class, but not really necessary
     */
    cout << "What's your name?\n";
    string name;
    cin >> name;

    //Check for existence, then open using JsonBox if it exists
    ifstream f((name + ".json").c_str());
    if(f.good()){

        f.close();

        //load the player
        JsonBox::Value saveData;
        JsonBox::Value areaData;
        saveData.loadFromFile(name + ".json");
        areaData.loadFromFile(name + ".json");
        Player player = Player(saveData, areaData, &entityManager);

        //Return the player
        return player;
    }
    else{

        f.close();

        int result = Dialogue("Choose your class", {"Fighter", "Rogue"}).activate();

        switch(result){

            //Fighter class favours strength
            case 1:
                return Player(name, 15, 5, 4, 1.0/64.0, 0, 1, "Fighter");

            //Rogue class favours agility
            case 2:
                return Player(name, 15, 4, 5, 1.0/64.0, 0, 1, "Rogue");

            //Default case that should never happen, but write it for completeness
            default:
                return Player(name, 15, 4, 4, 1.0/64.0, 0, 1, "Adventurer");
        }

    }

}


void dialogueMenu(Player& player){

    //output the menu
    int result = Dialogue("Menu\n-----\n", {"Items", "Equipment", "Character"}).activate();

    switch(result){

        //print the items that the player owns
        case 1:
            cout << "Items\n-------\n";
            player.inventory.print();
            cout << "--------------\n";
            break;

        //Print the equipment the player is wearing (if any), then ask if they want to equip a weapon or some armour
        case 2:
        {
            cout << "Equipment\n-------------\n";
            cout << "Armour: " << (player.equippedArmour != nullptr ? player.equippedArmour->name : "Nothing") << endl;
            cout << "Weapon: " << (player.equippedWeapon != nullptr ? player.equippedWeapon->name : "Nothing") << endl;

            int result2 = Dialogue("", {"Equip Armour", "Equip Weapon", "Close"}).activate();

            //Equipping Armour
            if(result2 == 1){
                int userInput = 0;

                //cannot equip armour if they do not have any, print a list of the armour and get the amount of armour in one go
                int numItems = player.inventory.print<Armour>(true);
                if(numItems == 0){
                    break;
                }

                while(!userInput){
                    //choose a piece of armour to equip
                    cout << "Equip which item?\n";
                    cin >> userInput;
                    //Equipment is numbered but is stored ina lst, so the number must be converted into a list element
                    if(userInput >= 1 && userInput <= numItems) {
                        player.equipArmour(player.inventory.get<Armour>(userInput - 1));
                    }
                }
            }

            //equip a weapon using the same algorithm as for armour
            else if(result2 == 2){
                int userInput = 0;
                int numItems = player.inventory.print<Weapon>(true);

                if(numItems == 0){
                    break;
                }

                while(!userInput){
                    cout << "Equip which item?\n";
                    cin >> userInput;

                    if(userInput >= 1 && userInput <= numItems){
                        player.equipWeapon(player.inventory.get<Weapon>(userInput-1));
                    }
                }
            }
            cout << "--------------------\n";
            break;

        }//end of case 2

        //output the character information, inc name, class (if they have one) stats, level and experience
        case 3:
            cout << "Character\n--------------\n";
            cout << player.name;
            if(player.className != ""){
                cout << " the " << player.className;
            }
            cout << endl;

            cout << "Health: " << player.hp << " / " << player.maxHp << endl;
            cout << "Strength: " << player.strength << endl;
            cout << "Agility: " << player.agility << endl;
            cout << "Level: " << player.level <<" (" << player.xp;
            cout << " / " << player.xpToLevel(player.level+1) << ")\n";
            cout << "\n-----------------\n";
            break;

        default:
            break;

    }

    return;

}






















































