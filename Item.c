#include<stdio.h>
#include<string.h>
#include "Item.h"
#include<stdlib.h>

void createItem(Item* item,char* name, int powItem,int size, char* description){
    item->name = name;
    item->powItem = powItem;
    item->size = size;
    item->description = description;
}