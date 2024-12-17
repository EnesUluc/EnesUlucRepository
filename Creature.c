#include<stdio.h>
#include "Creature.h"

void createCreature(Creature* creature, char* name, int health, int damage){
    creature->name = name;
    creature->health = health;
    creature->damage = damage;
};
void creatureStats(Creature* creature){
    printf("\nName:%s\n",creature->name);
    printf("Healht:%d\n",creature->health);
    printf("Damage:%d",creature->damage);
    
}