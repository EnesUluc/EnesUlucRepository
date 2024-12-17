# EnesUlucRepository

***When all c and h files are included in the main, the application runs when you make a run code, main.exe is created.***

Description

The game starts in a dungeon where a prince is imprisoned and we have four rooms.
We move on to the next room by killing the enemies in the room in order.
We succeed in the game when the last character dies.
We will start the game with the default features of our prince character.
There are items in the rooms. These items are created from item classes. When we collect the item, we gain extra power.

Requirements
-C Compiler (GCC, MinGW)

Files
main.c: The main game loop and room navigation.
Player.c and Player.h: Contains the player's information and functionality (e.g., starting the player, saving and loading player states).
Creature.c and Creature.h: Defines the creature class (e.g., zombie, snake, etc.) and their stats.
Room.c and Room.h: Defines the rooms, including room grid and room-specific logic.
Item.c and Item.h: Handles the creation and interaction with items in the game.
saveData.c: Handles saving and loading game states.

***Compilation***
gcc main.c Player.c Room.c Creature.c Item.c -o main
.\main

GamePlay
Start New Game: The player starts in the first room. They will be able to move around using the WASD keys (W for up, A for left, S for down, D for right). The objective is to explore rooms and defeat enemies.
Load Saved Game: If you have previously saved your game, you can load the saved state to continue from where you left off.
Battle Mechanics: Each room contains a creature that must be defeated. The player will need to strategize their moves and make use of items to win the battle.
Victory: If you manage to defeat the final boss and rescue the princess, you win the game.
Death: If the player's health reaches zero, the game ends.

Commands
D : Move Right
A : Move Left
S : Move Down
W : Move Up
E : Exit The Game 

Txt Files
-Dungeon.txt : Infos about dungeon
-FreedomParade.txt : Infos about Freedom room
-PoisonousRomm.txt : Infos about this room
-SilentRoom.txt : Infos about this room
-Rooms.txt : It includes dynamic allocated rooms.
-SavedRoomNumber : To continue current room when play saved game
-player_position.txt : Save the player coordinates and use it when you play saved game

-- > Texts will be taken from these txts for each room.
