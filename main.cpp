#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Mario.h"
#include "Enemies.h"
#include "Loader.h"
#include "Game.h"
#include "Menus.h"
#include "Sounds.h"
#include "MapEditor.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
using namespace std;

extern LevelStats levelstats[9], customstats[9];
extern int CUSTOM_LEVEL_ITEMS;
extern char* customLevelText[10];
extern int x, y;


int main() {
	MapReaderandSetter();
	SoundInitialisation();
	drawLanguage(x, y);
	loadStats(levelstats);
	loadData(customLevelText, CUSTOM_LEVEL_ITEMS, customstats);
	//MapEditorLevels();
	//LevelLoader();
	//MarioGame();
	//GameOverMenu();
	MainMenu();
    return 0;
}