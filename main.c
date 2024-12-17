#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Player.h"
#include "Player.c"
#include "Room.h"
#include "Room.c"
#include "Creature.h"
#include "Creature.c"
#include "Item.c"
#include "Item.h"


void displayRoom(char room[ROWS][COLUMN],Player* p);
void roomDungeon();


void room1(Player* player);
void room2(Player* player);
void room3(Player* player);
void room4(Player* p);
void death();
void victory();

int main(){
    Player p = startDefaultPlayer();
    int choice;
    char name[20];
    printf("\nWELCOME TO THE GAME!!!\n");
    printf("1-New Game\n2-Saved Game\n0-Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    printf("\n");
    if(choice !=0){
        int currentRoom = 1;
        if(choice == 2){
            currentRoom = loadSavedRoom();
            loadPlayerState(&p);
        }
        switch(currentRoom){
            case 1:
                room1(&p);
                break;
            case 2:
                room2(&p);
                break;
            case 3:
                room3(&p);
                break;
            case 4:
                room4(&p);
                break;
            default:
                printf("Error: Invalid room number in save filed.\n");
                break;
        }
    }
    else{ printf("\nThe game failed to start:) Have a nice day.");}
    if(p.health == 0){death();}
   
    
    return 0;

}

void room1(Player* p){
    Creature c;
    createCreature(&c,"Zombie",20,25);
    int roomCount = 4;
    saveCurrentRoom(1);

    Room* rooms = createRooms();
    Room* loadedRooms = loadRooms(&roomCount);
    look("DUNGEON ROOM");
    rooms[0].grid[0][4] = '?';
    rooms[0].grid[5][0] = 'X';

    int playerRCoordinate = 1;
    int playerCCoordinate = 1;
    loadPlayerPosition(&playerRCoordinate,&playerCCoordinate);
    for (int i = 0; i < ROWS; i++)
     {
         for (int j = 0; j < COLUMN; j++)
         {
            
            if(rooms[0].grid[i][j] == rooms[0].grid[playerRCoordinate][playerCCoordinate]){
             rooms[0].grid[1][1] = ' ';
             rooms[0].grid[playerRCoordinate][playerCCoordinate] = 'P';
             
            }
         }
        
     }
     
    loadPlayerPosition(&playerRCoordinate,&playerCCoordinate);
    displayRoom(rooms[0].grid,p);

    char command;
    while(p->health >0){
        savePlayerPosition(playerRCoordinate,playerCCoordinate);
        printf("\nEnter command(D= Right, A=Left, W = Up, S = Down  E=EXIT): ");
        scanf(" %c",&command);
        if(command == 'E'){
            savePlayerState(p);
            printf("Is it that easy to give up?\nSo you really didn't love the princess...YOUR PRINCESS!!!\n");
            printf("\nGame exits, data is saved...\n");
            saveRooms(rooms, roomCount);
            for (int i = 0; i < roomCount; i++) {
                free(rooms[i].name);
                free(loadedRooms[i].name);
            }
            free(rooms);
            free(loadedRooms);
            break;
        }
        move(rooms[0].grid,&playerRCoordinate,&playerCCoordinate,p,&c,command);
        savePlayerState(p);
        if(c.health <=0){room2(p);}
        if(p->health == 0){ break;}
        displayRoom(rooms[0].grid,p);
    }
    saveRooms(rooms, roomCount);
    
    
    for (int i = 0; i < roomCount; i++) {
        free(rooms[i].name);
        free(loadedRooms[i].name);
    }
    
    free(rooms);
    free(loadedRooms);
}

void room2(Player* p){
    Creature c;
    createCreature(&c, "Skeletor", 50, 30);  // Creature
    saveCurrentRoom(2);
    int roomCount = 4;
    Room* rooms = createRooms();
    Room* loadedRooms = loadRooms(&roomCount);
    look("SILENT TEMPLE");

    rooms[1].grid[1][4] = '?';  
    rooms[1].grid[5][5] = 'X';  
    rooms[1].grid[0][0] = '+';

    int playerRCoordinate = 1;
    int playerCCoordinate = 1;

    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);

    // Update the coordinate of player
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (rooms[1].grid[i][j] == rooms[1].grid[playerRCoordinate][playerCCoordinate]) {
                rooms[1].grid[1][1] = ' ';  
                rooms[1].grid[playerRCoordinate][playerCCoordinate] = 'P';  // Placed the player inside the room
            }
        }
    }

    // Last Location
    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);
    displayRoom(rooms[1].grid, p);  
    char command;

    // Fight loop
    while(p->health >0){
        savePlayerPosition(playerRCoordinate,playerCCoordinate);
        printf("\nEnter command(D= Right, A=Left, W = Up, S = Down  E=EXIT): ");
        scanf(" %c",&command);
        if(command == 'E'){
            savePlayerState(p);
            printf("\nYou shouldn't give up while you've come this far.\nRemember, the princess loves you very much...\n");
            printf("\nGame exits, data is saved...\n");
            saveRooms(rooms, roomCount);
            for (int i = 0; i < roomCount; i++) {
                free(rooms[i].name);
                free(loadedRooms[i].name);
            }
            free(rooms);
            free(loadedRooms);
            break;
        }
        move(rooms[1].grid, &playerRCoordinate, &playerCCoordinate, p, &c,command); 
        savePlayerState(p);
        if(c.health <= 0){room3(p);}
        if (p->health == 0) {
            break;  
        }
        displayRoom(rooms[1].grid, p); 
    }

    // Save the data of rooms
    saveRooms(rooms, roomCount);

    // Free
    for (int i = 0; i < roomCount; i++) {
        free(rooms[i].name);
        free(loadedRooms[i].name);
    }

    free(rooms);
    free(loadedRooms);
}
void room3(Player* p){

    Creature c;
    createCreature(&c, "Snake", 60, 50);  // Enemy
    saveCurrentRoom(3);
    int roomCount = 4;
    Room* rooms = createRooms();
    Room* loadedRooms = loadRooms(&roomCount);
    look("POISONOUS ROOM");

    // Add item and creature
    rooms[2].grid[0][5] = '+'; 
    rooms[2].grid[5][0] = 'X';  

    int playerRCoordinate = 1;
    int playerCCoordinate = 1;

    // Load the coordinates
    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);
    // Oda üzerinde oyuncu koordinatlarını güncelle
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (rooms[2].grid[i][j] == rooms[2].grid[playerRCoordinate][playerCCoordinate]) {
                rooms[2].grid[1][1] = ' ';  
                rooms[2].grid[playerRCoordinate][playerCCoordinate] = 'P'; 
            }
        }
    }

   
    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);
    displayRoom(rooms[2].grid, p);

    char command;
    // start the fight
    while(p->health >0){
        savePlayerPosition(playerRCoordinate,playerCCoordinate);
        printf("\nEnter command(D= Right, A=Left, W = Up, S = Down  E=EXIT): ");
        scanf(" %c",&command);
        if(command == 'E'){
            savePlayerState(p);
            printf("\nNo, it can't be, you're about to reach the princess, don't go!\n");
            printf("\nGame exits, data is saved...\n");
            saveRooms(rooms, roomCount);
            for (int i = 0; i < roomCount; i++) {
                free(rooms[i].name);
                free(loadedRooms[i].name);
            }
            free(rooms);
            free(loadedRooms);
            break;
        }
        move(rooms[2].grid, &playerRCoordinate, &playerCCoordinate, p, &c,command); 
        savePlayerState(p);
        if(c.health <= 0){room4(p);}
        if (p->health == 0) {
            break; 
        }
        displayRoom(rooms[2].grid, p); 
    }

 
    saveRooms(rooms, roomCount);

  
    for (int i = 0; i < roomCount; i++) {
        free(rooms[i].name);
        free(loadedRooms[i].name);
    }

    free(rooms);
    free(loadedRooms);
}
void room4(Player* p){
    printf("\nNEXT LEVEL\n\n");
    Creature c;
    createCreature(&c, "BOSS", 60, 50);  // Hard Level
    saveCurrentRoom(4);
    int roomCount = 4;
    Room* rooms = createRooms();
    Room* loadedRooms = loadRooms(&roomCount);
    look("FREEDOM PARADE");

    
    rooms[3].grid[2][4] = 'X';

    int playerRCoordinate = 1;
    int playerCCoordinate = 1;

   
    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);

    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (rooms[3].grid[i][j] == rooms[3].grid[playerRCoordinate][playerCCoordinate]) {
                rooms[3].grid[1][1] = ' ';  
                rooms[3].grid[playerRCoordinate][playerCCoordinate] = 'P';  
            }
        }
    }

    
    loadPlayerPosition(&playerRCoordinate, &playerCCoordinate);
    displayRoom(rooms[3].grid, p); 
    char command;
  
     while (p->health > 0) {
        savePlayerPosition(playerRCoordinate, playerCCoordinate);
        printf("\nEnter command(D= Right, A=Left, W = Up, S = Down  E=EXIT): ");
        scanf(" %c", &command);
        if (command == 'E') {
            savePlayerState(p);
            printf("\nHey, who's there? Can you hear me?\nI'm the princess!!!\n");
            printf("\nGame exits, data is saved...\n");
            saveRooms(rooms, roomCount);
            // Free allocated memory
            for (int i = 0; i < roomCount; i++) {
                free(rooms[i].name);
                free(loadedRooms[i].name);
            }
            free(rooms);
            free(loadedRooms);
            break;
        }
        move(rooms[3].grid, &playerRCoordinate, &playerCCoordinate, p, &c, command); 
        if (p->health > 0 && c.health > 0) {
            displayRoom(rooms[3].grid, p); 
        }
        savePlayerState(p);
        if (p->health == 0) {
            break; 
        }
        if (c.health <= 0) {
            victory();  
            break;
        }
    }
    saveRooms(rooms, roomCount);

    for (int i = 0; i < roomCount; i++) {
        free(rooms[i].name);
        free(loadedRooms[i].name);
    }

    free(rooms);
    free(loadedRooms);
}
void displayRoom(char room[ROWS][COLUMN],Player* p){
         printf("--------------------\n");
         for (int i = 0; i < ROWS; i++)
        {  
            printf("|");
            for (int j = 0; j < COLUMN; j++)
            {
                printf(" %c ",room[i][j]);
            }
         
            printf("|\n");
            
        }
        printf("--------------------\n");
        playerStats(p);
}
void death(){
    printf("\nTHE FALL OF A BRAVE SOUL...\nAs your last breath leaves your body, the dungeon falls silent.\n");
    printf("As the dungeon falls into cold silence, this moment remains like an elegy carrying the pain of the hero's loss.\nBut perhaps, one day, a stronger spirit will rise again...\n\n");
}
void victory(){
    printf("\nTHE SWEET BURDEN of VICTORY...\n");
    printf("When the prince opened the last dark door of the dungeon, a bright light caught his eyes.\n");
    printf("In front of him, the princess was waiting for him with a delicate smile.\n");
    printf("The Beginning of the End...\n");
}