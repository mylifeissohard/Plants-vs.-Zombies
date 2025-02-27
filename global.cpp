#include "global.h"

/*int window_width = 800;
int window_height = 600;
int field_width = 600;
int field_height = 600;
int NumOfTower = 5;*/

int TowerRadius[] = {80, 80, 70, 110, 150};
char TowerClass[][20] = {"Arcane", "Archer", "Canon", "Poison", "Storm"};
int TowerWidth[] = {72, 66, 72, 59, 45};
int TowerHeight[] = {121, 108, 69, 98, 112};
int game_wd=2;
int window=0;
float now=0;
bool key_state[ALLEGRO_KEY_MAX] = {false};


