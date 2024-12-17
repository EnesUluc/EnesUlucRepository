#ifndef ITEM_H
#define ITEM_H
#include<stdbool.h>
#include<stdio.h>

typedef struct{
    char* name;
    int powItem,size;
    char* description;
    bool isPickedUp;

}Item;

void createItem(Item* item,char* name, int powItem,int size, char* description);

#endif