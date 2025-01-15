#pragma once

struct LevelStats {
	char* name;
	char* disname;
	int score;
	int coins;
	int enemies;
	int time;
};

void AssetLoader();
int randnumb(int a, int b);

void LevelLoader();
void AssetLoaderMap();
void MapReseter();
void saveData(char* strArray[], int intValue, LevelStats LvlSts[]);
void loadData(char* strArray[], int& intValue, LevelStats LvlSts[]);
void saveStats(LevelStats LvlSts[]);
void loadStats(LevelStats LvlSts[]);
void loadStatsCustom(LevelStats LvlSts[]);