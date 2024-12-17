#ifndef CREATURE_H
#define CREATURE_H

typedef struct{
    const char* name;
    int health;
    int damage;
}Creature;

void createCreature(Creature* creature, char* name, int health, int damage);
void creatureStats(Creature* creature);

#endif