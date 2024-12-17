#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Creature.h"

Room* createRooms(){
    Room* rooms = (Room*)malloc(4 * sizeof(Room));
    if (!rooms) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < 4; k++) {
        char roomName[20];
        if(k == 0){sprintf(roomName, "Dungeon");}
        else if(k == 1){sprintf(roomName, "Silent Temple");}
        else if(k == 2){sprintf(roomName, "Poisonous Cave");}
        else if(k ==3){sprintf(roomName, "Freedom Parade");}
        else if(k ==4){sprintf(roomName, "ICE CONFINEMENT");}
        else if(k ==5){sprintf(roomName, "HAPPY ENDING");}
        
        
        rooms[k].name = strdup(roomName);

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMN; j++) {
                rooms[k].grid[i][j] = ' ';
            }
        }
    }
    return rooms;
};

void saveRooms(Room* rooms, int roomCount){
    FILE* file = fopen("Rooms.txt", "w");
    if (!file) {
        printf("Error: Could not save Rooms.\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        fprintf(file, "%s\n", rooms[i].name);
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMN; c++) {
                fprintf(file, "%c", rooms[i].grid[r][c]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("Rooms saved successfully.\n");
    
}

Room* loadRooms(int* roomCount) {
    FILE* file = fopen("Rooms.txt", "r");
    if (!file) {
        printf("Error: No saved rooms found. Returning default rooms.\n");
        *roomCount = 4;
        return createRooms(*roomCount);
    }

    int capacity = 4;
    Room* rooms = (Room*)malloc(capacity * sizeof(Room));
    if (!rooms) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (1) {
        char roomName[20];
        if (fscanf(file, "%19s", roomName) != 1) break;

        if (count >= capacity) {
            capacity *= 2;
            rooms = (Room*)realloc(rooms, capacity * sizeof(Room));
        }

        rooms[count].name = strdup(roomName);
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMN; c++) {
                fscanf(file, " %c", &rooms[count].grid[r][c]);
            }
        }
        count++;
    }

    fclose(file);
    *roomCount = count;
    return rooms;
}
    
void look(char* name){
    if(name == "DUNGEON ROOM"){
        roomDungeonTxt();
    }
    else if(name =="SILENT TEMPLE"){
        roomSilentTxt();
    }
    else if(name =="POISONOUS ROOM"){
        poisonousRoomTxt();
    }
    else if(name =="FREEDOM PARADE"){
        freedomParadeTxt();
    }
};
void roomDungeonTxt(){
    
    const char* fileName = "Dungeon.txt";
    FILE* file = fopen(fileName,"r");
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        printf("%s",buffer);
    }
    printf("\n\n");
    fclose(file);
};
void roomSilentTxt(){
    const char* fileName = "./SilentRoom.txt";
    FILE* file = fopen(fileName,"r");
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        printf("%s",buffer);
    }
    printf("\n\n");
    fclose(file);
};
void poisonousRoomTxt(){
    const char* fileName = "./PoisonousRoom.txt";
    FILE* file = fopen(fileName,"r");
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        printf("%s",buffer);
    }
    printf("\n\n");
    fclose(file);
}
void freedomParadeTxt(){
    const char* fileName = "./FreedomParade.txt";
    FILE* file = fopen(fileName,"r");
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        printf("%s",buffer);
    }
    printf("\n\n");
    fclose(file);
}

void saveCurrentRoom(int roomNumber){
    FILE *file = fopen("SavedRoomNumber.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to save game state.\n");
        return;
    }
    fprintf(file, "%d\n", roomNumber); // Save the room number for saved game
    fclose(file);
}

int loadSavedRoom(){
    FILE *file = fopen("SavedRoomNumber.txt", "r");
    if (file == NULL) {
        printf("No saved game found. Starting a new game.\n");
        return 1; 
    }
    int roomNumber;
    fscanf(file, "%d", &roomNumber);
    fclose(file);
    return roomNumber;
}

