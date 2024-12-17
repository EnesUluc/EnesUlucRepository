#ifndef PLAYER_H
#define PLAYER_H

#include<stdio.h>
#include "Room.h"
#include "Item.h"
#include "Creature.h"

#define ROWS 6
#define COLUMN 6

typedef struct{
    int health;
    int strenght;
    int inventoryCapacity;
    Room* cuurentRoom;
    char* name;
}Player;

Player startDefaultPlayer();
void playerStats(Player* player);
void pickUp(Item* item,Player* player);
void attack(Player* player,Creature* c);
void move(char room[ROWS][COLUMN],int* playerRCoordinate,int* playerCCoordinate, Player* p,Creature* c,char command);
void savePlayerPosition(int playerRCoordinate,int playerCCoordinate);
int loadPlayerPosition(int* playerRCoordinate, int* playerCCoordinate);
void savePlayerState(Player* player);
int loadPlayerState(Player* player);

#endif