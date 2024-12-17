#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Player.h"
#include "Item.h"
#include "Creature.h"

Player startDefaultPlayer(){
    Player p;
    p.name = "Prince";
    p.health = 20;
    p.inventoryCapacity = 50;
    p.strenght = 10;

    return p;
};
void playerStats(Player* player){
    printf("Name: %s\n",player->name);
    printf("Health: %d\n",player->health);
    printf("Strenght: %d\n",player->strenght);
    printf("Inventory Capacity: %d\n",player->inventoryCapacity);

};

void pickUp(Item* item,Player* player){       
    char choice;
    
        printf("Dou you want to item? (Y/N): ");
        scanf(" %c",&choice);
        if(choice == 'Y'){
        player->strenght += item->powItem;
        player->inventoryCapacity -= item->size;
        return;
    }
   
    
    return;   
    
};

void attack(Player* player,Creature* c){
    
    printf("There is a %s . Health = %d  Damage: %d\n",c->name,c->health,c->damage);
    char option;
    printf("Fight or Escape (F/E):");
    scanf(" %c",&option);
    if(option == 'F'){
        while(c->health >= 0 && player->health >= 0){
            c->health -= player->strenght;
            
            if(c->health <= 0) {
                c->health = 0;
                printf("\nYou shot.%s Health:%d",c->name,c->health);
                printf("\nYou won the fight.\n");
                break;
            }
            printf("\nYou shot.%s Health:%d",c->name,c->health);
            
            player->health -= c->damage;
            if(player->health <= 0) {
                player->health = 0;
                printf("\n%s shot you.Player Health:%d\n",c->name,player->health);
                printf("\nYou lost the fight.\n");
                break;
            }
            printf("\n%s shot you.Player Health:%d\n",c->name,player->health);
            
           

        }
    
    }
};

void move(char room[ROWS][COLUMN], int* playerRCoordinate, int* playerCCoordinate, Player* p, Creature* c, char command) { 
    Item sword;
    Item arrow;
    createItem(&sword, "Sword", 25, 10, "A sharp sword. Power of sword is 25. Sword size is 10.\n");
    createItem(&arrow, "Arrow", 15, 15, "An arrow. Power of arrow is 15. Arrow size is 8.\n");
    
    char currentPosition = room[*playerRCoordinate][*playerCCoordinate];
    
    // Movement commands
    if (command == 'D' && *playerCCoordinate < COLUMN - 1) {
        room[*playerRCoordinate][*playerCCoordinate] = ' ';
        (*playerCCoordinate)++; 
    } 
    else if (command == 'A' && *playerCCoordinate > 0) {
        room[*playerRCoordinate][*playerCCoordinate] = ' '; 
        (*playerCCoordinate)--; 
    } 
    else if (command == 'W' && *playerRCoordinate > 0) {
        room[*playerRCoordinate][*playerCCoordinate] = ' ';      
        (*playerRCoordinate)--; 
    } 
    else if (command == 'S' && *playerRCoordinate < ROWS - 1) {
        room[*playerRCoordinate][*playerCCoordinate] = ' '; 
        (*playerRCoordinate)++; 
    } 
    else if (command == 'E') {
        return;
    } 
    else {
        room[*playerRCoordinate][*playerCCoordinate] = currentPosition;
        return; 
    }

    // Update new position with 'P' (Player)
    room[*playerRCoordinate][*playerCCoordinate] = 'P';

    // Handling creature-specific actions
    if (strcmp(c->name, "Zombie") == 0) {
        if (*playerRCoordinate == 0 && *playerCCoordinate == 4) {
            pickUp(&sword, p);
        }
        if (*playerRCoordinate == 5 && *playerCCoordinate == 0) {
            attack(p, c);
        }
    } 
    else if (strcmp(c->name, "Skeletor") == 0) {
        if (*playerRCoordinate == 1 && *playerCCoordinate == 4) {
            pickUp(&arrow, p);
        }
        if (*playerRCoordinate == 0 && *playerCCoordinate == 0) {
            p->health += 1;
        }
        if (*playerRCoordinate == 5 && *playerCCoordinate == 5) {
            attack(p, c);
        }
    } 
    else if (strcmp(c->name, "Snake") == 0) {
        if (*playerRCoordinate == 0 && *playerCCoordinate == 5) {
            p->health += 30;
        }
        if (*playerRCoordinate == 5 && *playerCCoordinate == 0) {
            attack(p, c);
        }
    } 
    else if (strcmp(c->name, "BOSS") == 0) {
        if (*playerRCoordinate == 2 && *playerCCoordinate == 4) {
            attack(p, c);
        }
        if (*playerRCoordinate == 0 && *playerCCoordinate == 0) { 
            p->strenght += 50;
        }
    }
}

void savePlayerPosition(int playerRCoordinate, int playerCCoordinate) {
    FILE *file = fopen("player_position.txt", "w");  
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%d %d\n", playerRCoordinate, playerCCoordinate); 
    fclose(file); 
};

int loadPlayerPosition(int *playerRCoordinate, int *playerCCoordinate) {
    FILE *file = fopen("player_position.txt", "r"); 
    if (file == NULL) {
        return 0; 
    }
    fscanf(file, "%d %d", playerRCoordinate, playerCCoordinate); 
    fclose(file);
    return 1;
};

void savePlayerState(Player* player){
    FILE *file = fopen("PlayerState.txt", "w");  
    if (file == NULL) {
        printf("File write error.\n");
        return;
    }

    fprintf(file, "%d %d %d\n",player->health, player->strenght, player->inventoryCapacity);
    fclose(file); 
}
int loadPlayerState(Player* player){
    FILE *file = fopen("PlayerState.txt", "r"); 
    if (file == NULL) {
        return 0;  
    }
    
   
    fscanf(file, "%d %d %d" ,&player->health, &player->strenght, &player->inventoryCapacity); 
    fclose(file);
    return 1;
}

