#ifndef ROOM_H
#define ROOM_H
#define ROWS 6
#define COLUMN 6

typedef struct {
    char* name;
    char grid[ROWS][COLUMN];
    const char* item;
}Room;


Room* createRooms();
Room* loadRooms(int* roomCount);
void saveRooms(Room* rooms, int roomCount);
void look(char* name); 
void saveCurrentRoom(int roomNumber);
int loadSavedRoom();
void roomDungeonTxt();
void roomSilentTxt();
void poisonousRoomTxt();
void freedomParadeTxt();
#endif