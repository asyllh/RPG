/*--------------/
ALH
creature.cpp
24/08/17
/--------------*/
#include <string>
#include <cstdlib>
#include "JsonBox.h"
using namespace std;

#include "creature.h"
#include "entity.h"
#include "inventory.h"
#include "weapon.h"
#include "armour.h"
#include "door.h"
#include "area.h"
#include "entityManager.h"

Creature::Creature(string id, string name, int hp, int strength, int agility, double evasion, unsigned int xp) : Entity(id){
    this->name = name;
    this->hp = hp;
    this->maxHp = maxHp;
    this->strength = strength;
    this->agility = agility;
    this->evasion = evasion;
    this->equippedArmour = nullptr;
    this->equippedWeapon = nullptr;
    this->xp = xp;

}

Creature::Creature(string id, JsonBox::Value &v, EntityManager *mgr) : Creature(id, "", 0, 0, 0, 0, 0){
    this->load(v, mgr);
}

void Creature::equipWeapon(Weapon *weapon) {
    this->equippedWeapon = weapon;
    return;
}

void Creature::equipArmour(Armour *armour) {
    this->equippedArmour = armour;
    return;
}

Area* Creature::getAreaPtr(EntityManager *mgr) {
    return mgr->getEntity<Area>(this->currentArea);
}

int Creature::traverse(Door *door) {
    int flag = 2;

    //Open the door if it is shut
    if(door->locked == 0){
        door->locked = -1;
        flag = 2;
    }
    else if(door->locked > 0){
        //Unlock and open the door if the creature has the key
        if(this->inventory.count(door->key)){
            door->locked = -1;
            flag = 1;
        }
        //Creature does not have key, so door remains locked
        else{
            return 0;
        }
    }

    if(door->areas.first == this->currentArea){
        this->currentArea = door->areas.second;
    }
    else if(door->areas.second == this->currentArea){
        this->currentArea = door->areas.first;
    }

    return flag;

}

JsonBox::Object Creature::toJson() {
    JsonBox::Object o;
    o["name"] = JsonBox::Value(this->name);
    o["hp"] = JsonBox::Value(this->hp);
    o["hp_max"] = JsonBox::Value(this->maxHp);
    o["strength"] = JsonBox::Value(this-strength);
    o["agility"] = JsonBox::Value(this->agility);
    o["evasion"] = JsonBox::Value(this->evasion);
    o["xp"] = JsonBox::Value(int(this->xp));
    o["inventory"] = JsonBox::Value(this->inventory.getJson());
    o["equipped_weapon"] = JsonBox::Value(this->equippedWeapon == nullptr ? "nullptr" : this->equippedWeapon->id);
    o["equipped_armour"] = JsonBox::Value(this->equippedArmour == nullptr ? "nullptr" : this->equippedArmour->id);

    return o;
}

void Creature::load(JsonBox::Value &v, EntityManager *mgr){

    JsonBox::Object o = v.getObject();

    this->name = o["name"].getString();
    this->hp = o["hp"].getInteger();

    if(o.find("hp_max") != o.end()){
        this->maxHp = o["hp_max"].getInteger();
    }
    else{
        this->maxHp = hp;
    }

    this->strength = o["strength"].getInteger();
    this->agility = o["agility"].getInteger();
    this->evasion = o["evasion"].getDouble();
    this->xp = o["xp"].getInteger();

    if(o.find("inventory") != o.end()){
        this->inventory = Inventory(o["inventory"], mgr);
    }
    if(o.find("equipped_weapon") != o.end()){
        string equippedWeaponName = o["equipped_weapon"].getString();
        this->equippedWeapon = equippedWeaponName == "nullptr" ? nullptr : mgr->getEntity<Weapon>(equippedWeaponName);
    }
    if(o.find("equipped_armour") != o.end()){
        string equippedArmourName = o["equipped_armour"].getString();
        this->equippedArmour = equippedArmourName == "nullptr" ? nullptr : mgr->getEntity<Armour>(equippedArmourName);
    }
    return;
}

















































