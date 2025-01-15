#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Sounds.h"
#include "miniaudio.h"
#include "Game.h"
#include "MapEditor.h"
#include <limits>
using namespace std;

#define MAX1 30
#define MAX2 1000


extern ma_engine engine;
extern LevelStats levelstats[9], customstats[9];
extern ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, DeathEffect, BackGroundMusic, StageClear, PauseEffect, StarTheme, MenuMusic, MapEditorMusic, CreditMusic;
extern clock_t start;
extern colectible coins[100], life[100];
extern goompa gompav[100];
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * mario_main_screen, * mario_levels_menu,
* mario_custom_screen;
extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000];
extern int time1, okesc, n, SplitMenuItems, coinono, gdead, pdead, score1;
extern string direct, levelselect, cht;
int textH, menustate = 0;
extern double time_spent;
float volume = 1.0f;    
bool isMuted = false;    


void MainMenu();
void LevelsMenu();
void ScoreLevel();
void SettingsMenu();
void CustomMenu();
void CustomLevelsMenu();
void StatsMenu();
void ControlMenu();
void CustomControlMenu();
void StatsMenuCustom();
void Credits();

const int GAME_CONTROLS_ITEMS = 1;
char* gamecontrolsTextRO[GAME_CONTROLS_ITEMS] = { "INAPOI" };
char* gamecontrolsTextEN[GAME_CONTROLS_ITEMS] = { "BACK" };

const int MENU_ITEMS = 6;
char* menuTextEN[MENU_ITEMS] = { "START", "CUSTOM LEVELS", "CONTROLS", "SETTINGS", "CREDITS", "EXIT" };
char* menuTextRO[MENU_ITEMS] = { "START", "NIVELE CUSTOM", "CONTROALE", "SETARI", "CREDITE", "EXIT" };

const int GAMEOVER_ITEMS = 3;
char* gameOverTextEN[GAMEOVER_ITEMS] = { "RESTART", "LEVELS", "MAIN MENU" };
char* gameOverTextRO[GAMEOVER_ITEMS] = { "REINCEPE", "NIVELE", "MENIU PRINCIPAL" };

const int PAUSE_ITEMS = 3;
char* PauseTextEN[PAUSE_ITEMS] = { "RESUME", "LEVELS", "MAIN MENU" };
char* PauseTextRO[PAUSE_ITEMS] = { "RESUME", "NIVELE", "MENIU PRINCIPAL" };

const int LEVEL_ITEMS = 9;
char* levelTextEN[LEVEL_ITEMS] = { "LEVEL 1", "LEVEL 2", "LEVEL 3", "LEVEL 4", "LEVEL 5", "LEVEL 6", "LEVEL 7", "LEVEL 8", "INAPOI" };
char* levelTextRO[LEVEL_ITEMS] = { "NIVELUL 1", "NIVELUL 2", "NIVELUL 3", "NIVELUL 4", "NIVELUL 5", "NIVELUL 6", "NIVELUL 7", "NIVELUL 8", "INAPOI" };

const int CUSTOM_ITEMS = 4;
char* customTextEN[CUSTOM_ITEMS] = { "PLAY", "MAP EDITOR", "CONTROLS", "BACK" };
char* customTextRO[CUSTOM_ITEMS] = { "PLAY", "MAP EDITOR", "CONTROALE", "INAPOI" };

int CUSTOM_LEVEL_ITEMS;
char* customLevelText[10];

const int BUTTON_MENU_ITEMS = 3;
char* levelclearedTextEN[BUTTON_MENU_ITEMS] = { "REPLAY", "LEVELS", "MAIN MENU" };
char* levelclearedTextRO[BUTTON_MENU_ITEMS] = { "REINCEPE", "NIVELE", "MENIU PRINCIPAL" };

const int BUTTON_STATS_ITEMS = 3;
char* statsTextEN[BUTTON_MENU_ITEMS] = { "PLAY", "MAIN MENU", "BACK" };
char* statsTextRO[BUTTON_MENU_ITEMS] = { "JOACA", "MENIU PRINCIPAL", "INAPOI" };

const int SETTINGS_ITEMS = 4;
char* settingsTextEN[SETTINGS_ITEMS] = { "INCREASE VOLUME", "DECREASE VOLUME", "MUTE SOUND", "BACK" };
char* settingsTextRO[SETTINGS_ITEMS] = { "CRESTE VOLUMUL", "SCADE VOLUMUL", "OPRESTE SUNETUL", "INAPOI" };


int selectedOption = 0;
int hoveredButton = -1;
int clickedButton = -1; 


void drawLanguage(int screenWidth, int screenHeight) {
	cleardevice();
	int selectedImage = 0;
	
	int imageWidth = screenWidth / 3;
	int imageHeight = screenHeight / 3;

	
	int x1 = (screenWidth - imageWidth) / 4;
	int y1 = (screenHeight - imageHeight) / 2;      

	int x2 = (screenWidth - imageWidth) / 4 + imageWidth + imageWidth / 30;
	int y2 = (screenHeight - imageHeight) / 2;

	
	readimagefile("ROFLAG.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
	readimagefile("ENFLAG.jpg", x2, y2, x2 + imageWidth, y2 + imageHeight);

	
	setcolor(WHITE);
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
	outtextxy((x2 - x1), y1 + imageHeight + imageHeight / 20, "SELECT THE LANGUAGE");
	outtextxy((x2 - x1 / 1.25), y1 + imageHeight + imageHeight / 5, "SELECTEAZA LIMBA");

	
	while (true) {
		
		int mouseX = mousex();
		int mouseY = mousey();

		
		if (mouseX >= x1 && mouseX <= x1 + imageWidth && mouseY >= y1 && mouseY <= y1 + imageHeight) {
			setcolor(LIGHTBLUE);
			for (int i = 0;i < 4;i++) {
				rectangle(x1 + i, y1 + i, x1 + imageWidth + i, y1 + imageHeight + i);
			}
		}
		else {
			setcolor(BLACK);
			for (int i = 0;i < 4;i++) {
				rectangle(x1 + i, y1 + i, x1 + imageWidth + i, y1 + imageHeight + i);
			}
		}
		if (mouseX >= x2 && mouseX <= x2 + imageWidth && mouseY >= y2 && mouseY <= y2 + imageHeight) {
			setcolor(LIGHTBLUE);
			for (int i = 0;i < 4;i++) {
				rectangle(x2 + i, y2 + i, x2 + imageWidth + i, y2 + imageHeight + i);
			}
		}
		else {
			setcolor(BLACK);
			for (int i = 0;i < 4;i++) {
				rectangle(x2 + i, y2 + i, x2 + imageWidth + i, y2 + imageHeight + i);
			}
		}

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN); 

			
			if (mouseX >= x1 && mouseX <= x1 + imageWidth && mouseY >= y1 && mouseY <= y1 + imageHeight) {
				selectedImage = 1;  
				setcolor(GREEN);
				outtextxy(screenWidth / 2 - 70, screenHeight - 50, "Left image selected!");
				SplitMenuItems = 1;
				break; 
			}
			else if (mouseX >= x2 && mouseX <= x2 + imageWidth && mouseY >= y2 && mouseY <= y2 + imageHeight) {
				selectedImage = 2; 
				setcolor(GREEN);
				outtextxy(screenWidth / 2 - 70, screenHeight - 50, "Right image selected!");
				SplitMenuItems = 0;
				break;
			}
		}

		delay(20);
	}
}

// Function to Draw a Button
void drawButton(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;  // Highlight hovered button
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	// Draw text
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, height /150);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);

	// Reset background color
	setbkcolor(button_color);
}

// Function to Detect Which Button the Mouse is Hovering Over
int detectMouseHover(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 9;
	int marginY = screenHeight / 9;

	for (int i = 0; i < MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);

		
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;
}

// Draw Menu
void drawMenu(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 9;
	int marginY = screenHeight / 9;

	putimage(0, 0, mario_main_screen, COPY_PUT);

	settextjustify(LEFT_TEXT, TOP_TEXT);

	for (int i = 0; i < MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButton(x, y, buttonWidth, buttonHeight, menuTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButton(x, y, buttonWidth, buttonHeight, menuTextEN[i], WHITE, BLACK, isHovered);
	}
	int imageWidth = screenWidth / 3; 
	int imageX = (screenWidth - imageWidth) / 2;  
	int imageY = marginY - (x / 3 * 612) / x - screenHeight / 20;


}

void MainMenu() {
	ma_sound_stop(&MapEditorMusic);
	ma_sound_seek_to_pcm_frame(&MapEditorMusic, 0);
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);

	menustate = 0;
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		
		int mouseX = mousex();
		int mouseY = mousey();

		
		hoveredButton = detectMouseHover(mouseX, mouseY, screenWidth, screenHeight);

		
		drawMenu(screenWidth, screenHeight);

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					LevelsMenu();
					break;
				case 1:
					CustomMenu();
					break;
				case 2:
					ControlMenu();
					break;
				case 3:
					SettingsMenu();
					break;
				case 4:
					Credits();
					return;
				case 5:
					saveStats(levelstats);
					saveData(customLevelText, CUSTOM_LEVEL_ITEMS, customstats);
					running = false;
					break;
				}
			}
		}

		page = 1 - page;
		delay(50);  
	}

	exit(0);
}


void drawButtonLevels(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;
	setcolor(10);
	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);
	setbkcolor(button_color);
}


int detectMouseHoverLevels(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4; 
	int cellHeight = screenHeight / 6; 
	int marginX = (screenWidth - (3 * cellWidth)) / 4; 
	int marginY = (screenHeight - (3 * cellHeight)) / 4; 

	for (int i = 0; i < LEVEL_ITEMS; i++) {
		int column = i % 3; 
		int row = i / 3;   

		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		
		if (mouseX >= x && mouseX <= x + cellWidth && mouseY >= y && mouseY <= y + cellHeight) {
			return i;
		}
	}
	return -1; 
}

// Draw Levels Menu
void drawLevelsMenu(int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4;  
	int cellHeight = screenHeight / 6; 
	int marginX = (screenWidth - (3 * cellWidth)) / 4; 
	int marginY = (screenHeight - (3 * cellHeight)) / 4; 

	for (int i = 0; i < LEVEL_ITEMS; i++) {
		int column = i % 3;
		int row = i / 3;    

		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButtonLevels(x, y, cellWidth, cellHeight, levelTextRO[i], WHITE, BLUE, isHovered);
		else
			drawButtonLevels(x, y, cellWidth, cellHeight, levelTextEN[i], WHITE, BLUE, isHovered);
	}
}

void LevelsMenu() {
	ma_sound_stop(&MapEditorMusic);
	ma_sound_seek_to_pcm_frame(&MapEditorMusic, 0);
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	menustate = 0;
	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		
		int mouseX = mousex();
		int mouseY = mousey();

		
		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		
		drawLevelsMenu(screenWidth, screenHeight);

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				switch (clickedButton) {
				case 0:
					cht = "level1.txt";
					StatsMenu();
					break;
				case 1:
					cht = "level2.txt";
					StatsMenu();
					break;
				case 2: cht = "level3.txt";
					StatsMenu();
					break;
				case 3: cht = "level4.txt";
					StatsMenu();
					break;
				case 4: cht = "level5.txt";
					StatsMenu();
					break;
				case 5: cht = "level6.txt";
					StatsMenu();
					break;
				case 6: cht = "level7.txt";
					StatsMenu();
					break;
				case 7: cht = "level8.txt";
					StatsMenu();
					break;
				case 8:
					MainMenu();
					break;
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	
	exit(0);
}

int detectMouseHoverCustom(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 9;
	int marginY = screenHeight / 4.5;

	for (int i = 0; i < CUSTOM_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);

		
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;
}


void drawCustomMenu(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 9;
	int marginY = screenHeight / 4.5;

	putimage(0, 0, mario_custom_screen, COPY_PUT);

	settextjustify(LEFT_TEXT, TOP_TEXT);

	for (int i = 0; i < CUSTOM_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20); 

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButton(x, y, buttonWidth, buttonHeight, customTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButton(x, y, buttonWidth, buttonHeight, customTextEN[i], WHITE, BLACK, isHovered);
	}
	int imageWidth = screenWidth / 3;  
	int imageX = (screenWidth - imageWidth) / 2; 
	int imageY = marginY - (x / 3 * 612) / x - screenHeight / 20; 


}

void CustomMenu() {
	ma_sound_stop(&MapEditorMusic);
	ma_sound_seek_to_pcm_frame(&MapEditorMusic, 0);
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	menustate = 1;
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	menustate = 1;
	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();

		
		int mouseX = mousex();
		int mouseY = mousey();

		
		hoveredButton = detectMouseHoverCustom(mouseX, mouseY, screenWidth, screenHeight);

		
		drawCustomMenu(screenWidth, screenHeight);

		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					CustomLevelsMenu();
					break;
				case 1:
					MapEditorLevels();
					break;
				case 2:
					CustomControlMenu();
					break;
				case 3:
					MainMenu();
				}
			}
		}

		page = 1 - page;
		delay(50);  
	}

	
	exit(0);
}


void drawCustomLevelsMenu(int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4;  
	int cellHeight = screenHeight / 6; 
	int marginX = (screenWidth - (3 * cellWidth)) / 4; 
	int marginY = (screenHeight - (3 * cellHeight)) / 4; 
	for (int i = 0; i < CUSTOM_LEVEL_ITEMS; i++) {
		int column = i % 3; 
		int row = i / 3;    
		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		bool isHovered = (i == hoveredButton);
		if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 0) {
			drawButtonLevels(x, y, cellWidth, cellHeight, "BACK", WHITE, BLUE, isHovered);
		}
		else {
			if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 1) {
				drawButtonLevels(x, y, cellWidth, cellHeight, "INAPOI", WHITE, BLUE, isHovered);
			}
			else {
				drawButtonLevels(x, y, cellWidth, cellHeight, customLevelText[i], WHITE, BLUE, isHovered);
			}
		}
	}
}

void CustomLevelsMenu() {
	ma_sound_stop(&MapEditorMusic);
	ma_sound_seek_to_pcm_frame(&MapEditorMusic, 0);
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	menustate = 1;
	while (running) {

		if (!ma_sound_is_playing(&MenuMusic)) {
			ma_sound_start(&MenuMusic);
		}
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		
		int mouseX = mousex();
		int mouseY = mousey();

		
		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		
		drawCustomLevelsMenu(screenWidth, screenHeight);

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				if (strcmp(customLevelText[clickedButton], "BACK") == 0) {
					CustomMenu();
				}
				else {
					char path[50];
					strcpy(path, customLevelText[clickedButton]);
					strcat(path, ".txt");
					cht = path;
					StatsMenuCustom();
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	
	exit(0);
}

void drawButtonLevelsReplacer(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered, int yOffset) {
	
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;
	setcolor(10);
	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text) + yOffset) / 2;
	outtextxy(textX, textY, text);
	setbkcolor(button_color);
}

void drawCustomLevelsMenuReplacer(int screenWidth, int screenHeight) {
	int textHeight;

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	if (SplitMenuItems == 1) {
		char headerText[] = "ALEGE CE NIVEL INLOCUIESTI:";
		int textWidth = textwidth(headerText);
		textHeight = textheight(headerText);
		outtextxy((screenWidth - textWidth) / 2, textHeight, headerText);
	}
	else {
		char headerText[] = "CHOOSE WHICH LEVEL TO REPLACE:";
		int textWidth = textwidth(headerText);
		textHeight = textheight(headerText);
		outtextxy((screenWidth - textWidth) / 2, textHeight, headerText);
	}

	
	int cellWidth = screenWidth / 4; 
	int cellHeight = screenHeight / 6; 
	int marginX = (screenWidth - (3 * cellWidth)) / 4; 
	int marginY = (screenHeight - (3 * cellHeight)) / 4; 
	int yOffset = textHeight; 

	
	for (int i = 0; i < CUSTOM_LEVEL_ITEMS; i++) {
		int column = i % 3;
		int row = i / 3;
		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY) + yOffset;

		bool isHovered = (i == hoveredButton);

		if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 0) {
			drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, "BACK", WHITE, BLUE, isHovered, yOffset);
		}
		else {
			if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 1) {
				drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, "INAPOI", WHITE, BLUE, isHovered, yOffset);
			}
			else {
				drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, customLevelText[i], WHITE, BLUE, isHovered, yOffset);
			}
		}
	}
}

void CustomLevelsMenuReplacer(char filename[]) {
	ma_sound_stop(&MenuMusic);
	ma_sound_seek_to_pcm_frame(&MenuMusic, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&MapEditorMusic)) ma_sound_start(&MapEditorMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		int mouseX = mousex();
		int mouseY = mousey();

		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		drawCustomLevelsMenuReplacer(screenWidth, screenHeight);

		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				if (strcmp(customLevelText[clickedButton], "BACK") != 0) {
					delete customLevelText[clickedButton];
					customLevelText[clickedButton] = new char[strlen(filename) + 1];  
					strcpy(customLevelText[clickedButton], filename); 
					customstats[clickedButton].name = new char[strlen(filename) + 1];
					strcpy(customstats[clickedButton].name, filename);
					customstats[clickedButton].disname = new char[strlen(filename) + 1];
					strcpy(customstats[clickedButton].disname, filename);
					customstats[clickedButton].score = 0;
					customstats[clickedButton].time = 0;
					customstats[clickedButton].enemies = 0;
					setactivepage(page);
					cleardevice();
					setbkcolor(BLACK);
					setactivepage(1 - page);
					cleardevice();
					setbkcolor(BLACK);
					MapPaneler();
					return;
				}
				if (strcmp(customLevelText[clickedButton], "BACK") == 0) {
					setactivepage(page);
					setcolor(WHITE);
					cleardevice();
					setbkcolor(BLACK);
					setactivepage(1 - page);
					cleardevice();
					setbkcolor(BLACK);
					MapPaneler();
					return;
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	
	exit(0);
}

void drawArrowGameOver(int option, int color, int menuX, int menuY, int menuSpacing, int winWidth, int winHeight) {
	setcolor(color);

	int arrowWidth = winWidth / 40;  
	int arrowHeight = winHeight / 30; 

	
	int x = menuX - arrowWidth - 10;
	int textHeight;
	
	if (SplitMenuItems == 1) {
		textHeight = textheight(gameOverTextRO[option]);
	}
	else {
		textHeight = textheight(gameOverTextEN[option]);
	}

	int y = menuY + (option * menuSpacing) + (menuSpacing / 2) - (textHeight / 2);

	
	int points[8] = { x, y, x + arrowWidth, y + arrowHeight / 2, x, y + arrowHeight, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

void drawGameOver(int text_color) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int fontSize = winHeight / 40; 
	if (fontSize > 15) fontSize = 15;
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4;

	
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 1);

	setcolor(text_color);

	
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);
	if (SplitMenuItems == 0) {
		int gameOverWidth = textwidth("GAME OVER");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "GAME OVER");
	}
	else {
		int gameOverWidth = textwidth("AI PIERDUT");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "AI PIERDUT");
	}

	int textX, textY;

	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	for (int i = 0; i < GAMEOVER_ITEMS; i++) {
		if (SplitMenuItems == 1) {
			textX = menuX + (menuWidth - textwidth(gameOverTextRO[i])) / 2; 
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, gameOverTextRO[i]);
		}
		else {
			textX = menuX + (menuWidth - textwidth(gameOverTextEN[i])) / 2; 
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, gameOverTextEN[i]);
		}
	}
}

void GameOverMenu() {
	ma_sound_stop(&BackGroundMusic);
	if (!ma_sound_is_playing(&DeathEffect)) ma_sound_start(&DeathEffect);
	selectedOption = 0;
	setbkcolor(BLACK);
	cleardevice();
	setbkcolor(BLACK);

	int text_color = 14;
	int arrow_color = 14;

	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; 

	
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 1);

	while (kbhit()) {
		getch(); 
	}
	selectedOption = 0;

	drawGameOver(text_color);
	drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) { // UP
			drawArrowGameOver(selectedOption, 0, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
			selectedOption = (selectedOption - 1 + GAMEOVER_ITEMS) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowGameOver(selectedOption, 0, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
			selectedOption = (selectedOption + 1) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight);
		}
		if (key == 13) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				MapReseter();
				cht = levelselect;
				ma_sound_stop(&DeathEffect);
				MarioGame();
				break;
			case 1:
				selectedOption = 0;
				if (menustate == 0) {
					MapReseter();
					LevelsMenu();
				}
				else {
					MapReseter();
					CustomLevelsMenu();
				}
				break;
			case 2:
				selectedOption = 0;
				if (menustate == 0) {
					MapReseter();
					MainMenu();
				}
				else {
					MapReseter();
					CustomMenu();
				}
				break;
			}
		}
	}
}

void drawArrowPause(int option, int r, int g, int b, int menuX, int menuY, int menuSpacing, int winWidth, int winHeight) {
	setcolor(RGB(r, g, b));

	
	int arrowWidth = winWidth / 40;  
	int arrowHeight = winHeight / 30; 

	
	int x = menuX - arrowWidth - 10;
	int textHeight;

	if (SplitMenuItems == 1)
		textHeight = textheight(PauseTextRO[option]);
	else
		textHeight = textheight(PauseTextEN[option]);
	int y = menuY + (option * menuSpacing) + (menuSpacing / 2) - (textHeight / 2);

	
	int points[8] = { x, y, x + arrowWidth, y + arrowHeight / 2, x, y + arrowHeight, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, RGB(r, g, b));
	fillpoly(4, points);
}

void drawPause(int r, int g, int b) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int fontSize = winHeight / 40; 
	if (fontSize > 15) fontSize = 15;  
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; 

	
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (PAUSE_ITEMS + 1); 

	setcolor(RGB(r, g, b));
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);

	if (SplitMenuItems == 1) {
		int gameOverWidth = textwidth("PAUZA");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "PAUZA");
	}
	else {
		int gameOverWidth = textwidth("GAME PAUSED");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "GAME PAUSED");
	}

	// Draw menu options
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	for (int i = 0; i < PAUSE_ITEMS; i++) {
		int textX, textY;
		if (SplitMenuItems == 1) {
			textX = menuX + (menuWidth - textwidth(PauseTextRO[i])) / 2; 
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, PauseTextRO[i]);
		}
		else {
			textX = menuX + (menuWidth - textwidth(PauseTextEN[i])) / 2; 
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, PauseTextEN[i]);
		}
	}
}

void PauseMenu() {
	setvisualpage(1);
	setactivepage(1);
	selectedOption = 2;
	setbkcolor(RGB(126, 132, 246));
	cleardevice();
	setbkcolor(RGB(126, 132, 246));
	

	int arrow_color[3] = { 255, 255, 255 };
	char text_color[20] = "RGB(126, 132, 246)";

	int winWidth = getmaxx();
	int winHeight = getmaxy();
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; 

	
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (PAUSE_ITEMS + 1);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_start(&PauseEffect);
	drawPause(255, 255, 255);
	
	while (kbhit()) {
		getch(); // Consume all available keypresses
	}

	selectedOption = 0;
	drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) { // UP
			drawArrowPause(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
			selectedOption = (selectedOption - 1 + PAUSE_ITEMS) % PAUSE_ITEMS;
			drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowPause(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
			selectedOption = (selectedOption + 1) % PAUSE_ITEMS;
			drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); 
		}
		if (key == 13) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				setvisualpage(0);
				setactivepage(0);
				delay(1000);
				return;
				break;
			case 1:
				if (menustate == 0) {
					MapReseter();
					LevelsMenu();
				}
				else {
					MapReseter();
					CustomLevelsMenu();
				}

				break;
			case 2:
				selectedOption = 0;
				if (menustate == 0) {
					MapReseter();
					MainMenu();
				}
				else {
					MapReseter();
					CustomMenu();
				}
				break;
			}
		}
	}
}

void displayText(char* text, int screenWidth, int screenHeight, int fontSize, int color) {
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	setcolor(color);
	int textX = (screenWidth - textwidth(text)) / 2;
	int textY = (screenHeight - textheight(text)) / 2;
	outtextxy(textX, textY, text);
}

void drawButtonStats(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;  
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	
	setbkcolor(finalColor);
	setcolor(textColor);
		settextstyle(EUROPEAN_FONT, HORIZ_DIR, height/110);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);

	setcolor(WHITE);
	line(x + 1.40 * width, y - 1.25 * height, x + 1.40 * width, y + 2 * height);

	
	setbkcolor(button_color);
}

int detectMouseHoverStats(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 11;
	int marginY = screenHeight / 3;

	for (int i = 0; i < BUTTON_MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  

		
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;  
}

// Draw Menu
void drawStatsMenu(int screenWidth, int screenHeight, int selected) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 11;
	int marginY = screenHeight / 3;

	settextjustify(LEFT_TEXT, TOP_TEXT);
	int fontsize = screenHeight / 170;
	char LevelSpecific[50], coinsCounter[50], enemiesCounter[50], timeCounter[50], scoreCounter[50];
	int textHeight;

	if (SplitMenuItems == 1) {
		sprintf(LevelSpecific, "%s STATISTICI", levelstats[selected].disname);
		displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

		textHeight = textheight(LevelSpecific);
		sprintf(coinsCounter, "Monede colectate: %d", levelstats[selected].coins);
		sprintf(enemiesCounter, "Inamici ucisi: %d", levelstats[selected].enemies);
		sprintf(timeCounter, "TIME: %ds", levelstats[selected].time);
		sprintf(scoreCounter, "SCOR: %d", levelstats[selected].score);

		displayText(coinsCounter, 1.35 * screenWidth, 2 * marginY + 4.5 * textHeight, fontsize, WHITE);
		displayText(enemiesCounter, 1.35 * screenWidth, 2 * marginY + 7.0 * textHeight, fontsize, WHITE);
		displayText(timeCounter, 1.35 * screenWidth, 2 * marginY + 9.5 * textHeight, fontsize, WHITE);
		displayText(scoreCounter, 1.35 * screenWidth, 2 * marginY + 13.0 * textHeight, fontsize + 0.75, WHITE);
	}
	else {
		sprintf(LevelSpecific, "%s STATS", levelstats[selected].disname);
		displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

		textHeight = textheight(LevelSpecific);
		sprintf(coinsCounter, "Coins collected:  %d", levelstats[selected].coins);
		sprintf(enemiesCounter, "Enemies killed:  %d", levelstats[selected].enemies);
		sprintf(timeCounter, "TIME:  %ds", levelstats[selected].time);
		sprintf(scoreCounter, "HIGH SCORE:  %d", levelstats[selected].score);

		displayText(coinsCounter, 1.35 * screenWidth, 2 * marginY + 4.5 * textHeight, fontsize, WHITE);
		displayText(enemiesCounter, 1.35 * screenWidth, 2 * marginY + 7.0 * textHeight, fontsize, WHITE);
		displayText(timeCounter, 1.35 * screenWidth, 2 * marginY + 9.5 * textHeight, fontsize, WHITE);
		displayText(scoreCounter, 1.35 * screenWidth, 2 * marginY + 13.0 * textHeight, fontsize + 0.75, WHITE);
	}


	for (int i = 0; i < BUTTON_MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);

		bool isHovered = (i == hoveredButton);

		if (SplitMenuItems == 1)
			drawButtonStats(x, y, buttonWidth, buttonHeight, statsTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButtonStats(x, y, buttonWidth, buttonHeight, statsTextEN[i], WHITE, BLACK, isHovered);

	}
}

void StatsMenu() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;
	int selected = 0;
	hoveredButton = -1;
	clickedButton = -1;

	char charArray[50];
	strcpy(charArray, cht.c_str());

	for (int i = 0;i < 9;i++) {
		if (strcmp(charArray, levelstats[i].name) == 0)
		{
			selected = i;
			break;
		}
	}

	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		
		int mouseX = mousex();
		int mouseY = mousey();



		
		hoveredButton = detectMouseHoverStats(mouseX, mouseY, screenWidth, screenHeight);

		
		drawStatsMenu(screenWidth, screenHeight, selected);

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					MapReseter();
					delay(1000);
					MarioGame();
					break;
				case 1:
					MainMenu();
					break;
				case 2:
					LevelsMenu();
					break;
				}
			}
		}

		page = 1 - page;
		delay(50);  
	}
}

void drawStatsMenuCustom(int screenWidth, int screenHeight, int selected) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 11;
	int marginY = screenHeight / 3;

	settextjustify(LEFT_TEXT, TOP_TEXT);
	int fontsize = screenHeight / 170;
	char LevelSpecific[50], coinsCounter[50], enemiesCounter[50], timeCounter[50], scoreCounter[50];

	sprintf(LevelSpecific, "%s STATS", customstats[selected].disname);
	displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

	int textHeight = textheight(LevelSpecific);
	if (SplitMenuItems == 1) {
		sprintf(LevelSpecific, "%s STATISTICI", levelstats[selected].disname);
		displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

		textHeight = textheight(LevelSpecific);
		sprintf(coinsCounter, "Monede colectate: %d", levelstats[selected].coins);
		sprintf(enemiesCounter, "Inamici ucisi: %d", levelstats[selected].enemies);
		sprintf(timeCounter, "TIME: %ds", levelstats[selected].time);
		sprintf(scoreCounter, "SCOR: %d", levelstats[selected].score);

		displayText(coinsCounter, 1.35 * screenWidth, 2 * marginY + 4.5 * textHeight, fontsize, WHITE);
		displayText(enemiesCounter, 1.35 * screenWidth, 2 * marginY + 7.0 * textHeight, fontsize, WHITE);
		displayText(timeCounter, 1.35 * screenWidth, 2 * marginY + 9.5 * textHeight, fontsize, WHITE);
		displayText(scoreCounter, 1.35 * screenWidth, 2 * marginY + 13.0 * textHeight, fontsize + 0.75, WHITE);
	}
	else {
		sprintf(LevelSpecific, "%s STATS", levelstats[selected].disname);
		displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

		textHeight = textheight(LevelSpecific);
		sprintf(coinsCounter, "Coins collected:  %d", levelstats[selected].coins);
		sprintf(enemiesCounter, "Enemies killed:  %d", levelstats[selected].enemies);
		sprintf(timeCounter, "TIME:  %ds", levelstats[selected].time);
		sprintf(scoreCounter, "HIGH SCORE:  %d", levelstats[selected].score);

		displayText(coinsCounter, 1.35 * screenWidth, 2 * marginY + 4.5 * textHeight, fontsize, WHITE);
		displayText(enemiesCounter, 1.35 * screenWidth, 2 * marginY + 7.0 * textHeight, fontsize, WHITE);
		displayText(timeCounter, 1.35 * screenWidth, 2 * marginY + 9.5 * textHeight, fontsize, WHITE);
		displayText(scoreCounter, 1.35 * screenWidth, 2 * marginY + 13.0 * textHeight, fontsize + 0.75, WHITE);
	}

	for (int i = 0; i < BUTTON_MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		bool isHovered = (i == hoveredButton);

		if (SplitMenuItems == 1)
			drawButtonStats(x, y, buttonWidth, buttonHeight, statsTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButtonStats(x, y, buttonWidth, buttonHeight, statsTextEN[i], WHITE, BLACK, isHovered);

	}
}

void StatsMenuCustom() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;
	int selected = 0;
	hoveredButton = -1;
	clickedButton = -1;

	char charArray[50];
	strcpy(charArray, cht.c_str());

	for (int i = 0;i < 9;i++) {
		char str[50];
		strcpy(str, customstats[i].name);
		strcat(str, ".txt");
		if (strcmp(charArray, str) == 0)
		{
			selected = i;
			break;
		}
	}

	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

		int mouseX = mousex();
		int mouseY = mousey();




		hoveredButton = detectMouseHoverStats(mouseX, mouseY, screenWidth, screenHeight);


		drawStatsMenuCustom(screenWidth, screenHeight, selected);


		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;


				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					MapReseter();
					delay(1000);
					MarioGame();
					break;
				case 1:
					CustomMenu();
					break;
				case 2:
					CustomLevelsMenu();
					break;
				}
			}
		}

		page = 1 - page;
		delay(50);
	}
}

void drawArrowStats(int option, int r, int g, int b, int menuX, int menuY, int menuSpacing, int winWidth, int winHeight, int TextHeight) {
	setcolor(RGB(r, g, b));

	
	int arrowWidth = winWidth / 40;  
	int arrowHeight = winHeight / 30; 

	
	int x = menuX - arrowWidth - 10;
	int textHeight;

	if (SplitMenuItems == 1)
		textHeight = textheight(PauseTextRO[option]);
	else
		textHeight = textheight(PauseTextEN[option]);
	int y = menuY + (option * menuSpacing) + (menuSpacing / 2) - (textHeight / 2) + 4 * TextHeight;

	
	int points[8] = { x, y, x + arrowWidth, y + arrowHeight / 2, x, y + arrowHeight, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, RGB(r, g, b));
	fillpoly(4, points);
}

void drawLevelClear(int r, int g, int b) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int fontSize = winHeight / 40; 
	if (fontSize > 15) fontSize = 15;  
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; 

	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (PAUSE_ITEMS + 1); 

	setcolor(RGB(r, g, b));
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);
	int gameOverHeight = textheight("LEVEL CLEARED"), gameOverWidth;

	if (SplitMenuItems == 1) {
		gameOverWidth = textwidth("NIVEL TERMINAT");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "NIVEL TERMINAT");
	}
	else {
		gameOverWidth = textwidth("LEVEL CLEARED");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  
		outtextxy(gameOverX, gameOverY, "LEVEL CLEARED");
	}

	char coinsCounter[50], enemiesCounter[50], timeCounter[50], scoreCounter[50];
	if (SplitMenuItems == 0) {

		sprintf(coinsCounter, "Coins collected: %d", coinono);
		sprintf(enemiesCounter, "Enemies killed: %d", gdead + pdead);
		sprintf(timeCounter, "Time: %ds", (int)time_spent);
		if (score1 > 0) {
			sprintf(scoreCounter, "HIGH SCORE: %d", score1);
		}
		else {
			sprintf(scoreCounter, "NEW HIGH SCORE: %d", score1);
		}
	}
	else {
		sprintf(coinsCounter, "Monede Colectate: %d", coinono);
		sprintf(enemiesCounter, "Inamici ucisi: %d", gdead + pdead);
		sprintf(timeCounter, "Timp: %ds", (int)time_spent);
		if (score1 > 0) {
			sprintf(scoreCounter, "PUNCTAJ:  %d", score1);
		}
		else {
			sprintf(scoreCounter, "PUNCTAJ NOU:  %d", score1);
		}
	}

	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 2);
	int textHeight = textheight("LEVEL STATS");
	textH = textHeight;


	displayText(coinsCounter, winWidth, menuY + 150 + 1.25 * gameOverHeight, fontSize + 1, WHITE);
	displayText(enemiesCounter, winWidth, menuY + 2 * textHeight + 150 + 1.25 * gameOverHeight, fontSize + 1, WHITE);
	displayText(timeCounter, winWidth, menuY + 4 * textHeight + 150 + 1.25 * gameOverHeight, fontSize + 1, WHITE);
	displayText(scoreCounter, winWidth, menuY + 6 * textHeight + 150 + 1.25 * gameOverHeight, fontSize + 1.75, WHITE);


	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);


	
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 0.75);
	for (int i = 0; i < GAMEOVER_ITEMS; i++) {
		int textX, textY;
		if (SplitMenuItems == 1) {
			textX = menuX + (menuWidth - textwidth(levelclearedTextRO[i])) / 2;
			textY = menuY + i * menuSpacing + 4 * textHeight;
			outtextxy(textX, textY, levelclearedTextRO[i]);
		}
		else {
			textX = menuX + (menuWidth - textwidth(levelclearedTextEN[i])) / 2;
			textY = menuY + i * menuSpacing + 4 * textHeight;
			outtextxy(textX, textY, levelclearedTextEN[i]);
		}
	}
}

void LevelCLearMenu() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	ma_sound_start(&StageClear);
	setvisualpage(1);
	setactivepage(1);
	selectedOption = 2;
	setbkcolor(RGB(126, 132, 246));
	cleardevice();
	setbkcolor(RGB(126, 132, 246));

	char charArray[50];
	strcpy(charArray, cht.c_str());

	for (int i = 0;i < 9;i++) {
		if (strcmp(levelstats[i].name, charArray) == 0) {
			if (levelstats[i].score < score1) {
				levelstats[i].score = score1;
			}
			levelstats[i].coins = coinono;
			levelstats[i].enemies = gdead + pdead;
			levelstats[i].time = (int)time_spent;
		}
	}
	for (int i = 0;i < CUSTOM_LEVEL_ITEMS -1;i++) {
		char str[50];
		strcpy(str, customstats[i].disname);
		strcat(str, ".txt");
		if (strcmp(str, charArray) == 0) {
			if (customstats[i].score < score1) {
				customstats[i].score = score1;
			}
			customstats[i].coins = coinono;
			customstats[i].enemies = gdead + pdead;
			customstats[i].time = (int)time_spent;
		}
	}


	int arrow_color[3] = { 255, 255, 255 };
	char text_color[20] = "RGB(126, 132, 246)";

	int winWidth = getmaxx();
	int winHeight = getmaxy();
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; 


	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 1);
	

	while (kbhit()) {
		getch(); // Consume all available keypresses
	}
	selectedOption = 0;

	drawLevelClear(255, 255, 255);
	drawArrowStats(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight, textH);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) { // UP
			drawArrowStats(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight, textH); // Erase current arrow
			selectedOption = (selectedOption - 1 + GAMEOVER_ITEMS) % GAMEOVER_ITEMS;
			drawArrowStats(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight, textH); // Draw new arrow
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowStats(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight, textH); // Erase current arrow
			selectedOption = (selectedOption + 1) % GAMEOVER_ITEMS;
			drawArrowStats(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight, textH); // Draw new arrow
		}
		if (key == 13) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				MapReseter();
				cht = levelselect;
				ma_sound_stop(&StageClear);
				MarioGame();
				break;
			case 1:
				if (menustate == 0) {
					MapReseter();
					LevelsMenu();
				}
				else {
					MapReseter();
					CustomLevelsMenu();
				}
				exit(0);
				break;
			case 2:
				selectedOption = 0;
				if (menustate == 0) {
					MapReseter();
					MainMenu();
				}
				else {
					MapReseter();
					CustomMenu();
				}
				break;
			}
		}
	}
}

void drawButtonControls(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);
	setbkcolor(button_color);
}

int detectMouseHoverControls(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 5;
	int buttonHeight = screenHeight / 10;
	int marginX = (screenWidth - buttonWidth) / 14;
	int marginY = screenWidth - screenHeight + 50;

	for (int i = 0; i < GAME_CONTROLS_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);

		
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;
}

void drawButtonsMenuCustom(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 5;
	int buttonHeight = screenHeight / 10;
	int marginX = (screenWidth - buttonWidth) / 14;
	int marginY = screenWidth - screenHeight + 50;

	for (int i = 0; i < GAME_CONTROLS_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);
		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1) {
			drawButtonControls(x, y, buttonWidth, buttonHeight, "INAPOI", WHITE, BLUE, isHovered);
		}
		else {
			drawButtonControls(x, y, buttonWidth, buttonHeight, "BACK", WHITE, BLUE, isHovered);
		}
	}
}

void ControlMenu() {
	
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	bool running = true;
	int page = 0;

	while (running) {
		setbkcolor(BLACK);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();

		if (SplitMenuItems == 1) {
			readimagefile("GameControlsRO.jpg", 0, 0, screenWidth, screenHeight);
		}
		else {
			readimagefile("GameControlsEN.jpg", 0, 0, screenWidth, screenHeight);
		}

		int mouseX = mousex();
		int mouseY = mousey();

		hoveredButton = detectMouseHoverControls(mouseX, mouseY, screenWidth, screenHeight);

		drawButtonsMenuCustom(screenWidth, screenHeight);

		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				if (clickedButton == 0) {
					MainMenu();
					break;
				}
			}
		}

		setvisualpage(page);
		page = 1 - page;
	}
}

void CustomControlMenu() {
	
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	bool running = true;
	int page = 0;

	while (running) {
		setbkcolor(BLACK);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();

		if (SplitMenuItems == 1) {
			readimagefile("EditorControlsRO.jpg", 0, 0, screenWidth, screenHeight);
		}
		else {
			readimagefile("EditorControlsEN.jpg", 0, 0, screenWidth, screenHeight);
		}

		int mouseX = mousex();
		int mouseY = mousey();

		hoveredButton = detectMouseHoverControls(mouseX, mouseY, screenWidth, screenHeight);

		drawButtonsMenuCustom(screenWidth, screenHeight);

		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				if (clickedButton == 0) {
					CustomMenu();
					break;
				}
			}
		}

		setvisualpage(page);
		page = 1 - page;
	}
}

struct CreditEntry {
	char text[100];
};

void drawTextCredits(int x, int y, const char* text, int fontSize) {
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, fontSize);
	outtextxy(x, y, const_cast<char*>(text));
}


void Credits() {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	CreditEntry creditsEN[] = {
		{"Mario De FII"},
		{" "},
		{"Developed by:"},
		{"Patranea Cosmin-Cristian"},
		{"Iftimi George-Daniel"},
		{" "},
		{"Art and Graphic Design:"},
		{"Lead Artist and Designer..............Iftimi George-Daniel"},
		{"Artist and Designer..............Patranea Cosmin-Cristian"},
		{"Main Menu art by Edi Capitanul"},
		{" "},
		{"Level Design:"},
		{"Patranea Cosmin-Cristian"},
		{"Iftimi George-Daniel"},
		{"Logica Vietii"},
		{" "},
		{"Music and Sound:"},
		{"Sound Engineer..............Patranea Cosmin-Cristian"},
		{" "},
		{"Quality Assurance:"},
		{"QA manager..............Patranea Cosmin-Cristian"},
		{"Lead QA..............Logica Vietii"},
		{"QA..............Edi Capitanul"},
		{"QA..............Idorando Crypto SRL"},
		{" "},
		{"Voice Actors:"},
		{"Logica Vietii as Voice from Map Editor"},
		{" "},
		{"Extra Special thanks:"},
		{"Room 404 from C5 dormatory for the hospitality"},
		{" "},
		{" "},
		{"Thank you for playing!"},
		{" "},
		{"Press ESC to return to the main menu" }
	};

	CreditEntry creditsRO[] = {
		{"Mario De FII"},
		{" "},
		{"Dezvoltat de:"},
		{"Patranea Cosmin-Cristian"},
		{"Iftimi George-Daniel"},
		{" "},
		{"Arta si design grafic:"},
		{"Lead Artist and Designer.............. Iftimi George-Daniel"},
		{"Artist and Designer..............Patranea Cosmin-Cristian"},
		{"Arta pentru meniu de Edi Capitanul"},
		{" "},
		{"Level Design:"},
		{"Patranea Cosmin-Cristian"},
		{"Iftimi George-Daniel"},
		{"Logica Vietii"},
		{" "},
		{"Muzica si sunet:"},
		{"Inginer de sunet..............Patranea Cosmin-Cristian"},
		{" "},
		{"Asigurarea calitatii:"},
		{"QA manager..............Patranea Cosmin-Cristian"},
		{"Lead QA..............Logica Vietii"},
		{"QA..............Edi Capitanul"},
		{"QA..............Idorando Crypto SRL"},
		{" "},
		{"Voice Actors:"},
		{"Logica Vietii drept vocea din Editorul pentru harti"},
		{" "},
		{"Multumiri speciale:"},
		{"Camera 404 din caminul C5 pentru ospitalitate"},
		{" "},
		{" "},
		{"Va multumesc ca ati jucat!"},
		{" "},
		{"Apasa ESC pentru a reveni la meniu"}
	};

	int creditCount;
	cleardevice();
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	if (SplitMenuItems == 1)
		creditCount = sizeof(creditsRO) / sizeof(creditsRO[0]); // Total number of credits
	else
		creditCount = sizeof(creditsEN) / sizeof(creditsEN[0]);

	
	float fontScale = screenWidth / 480.0;
	int fontSize = max(1, static_cast<int>(fontScale * 2));
	int lineHeight = textheight("A") * fontSize + 5;
	int scrollSpeed = max(1, static_cast<int>(2 * fontScale));

	// Y-coordinate for scrolling
	int yPos = screenHeight;

	int ok = 1;

	ma_sound_stop(&MenuMusic);
	ma_sound_seek_to_pcm_frame(&MenuMusic, 0);
	delay(1000);

	
	while (ok == 1) {
		cleardevice();
		if (!ma_sound_is_playing(&CreditMusic)) ma_sound_start(&CreditMusic);
		if (SplitMenuItems == 1) {
			
			for (int i = 0; i < creditCount; i++) {
				int yOffset = yPos + i * lineHeight;
				if (yOffset >= 0 && yOffset < screenHeight) {
					int textWidth = textwidth(creditsRO[i].text);
					int xPos = (screenWidth - textWidth) / 2; 
					drawTextCredits(xPos, yOffset, creditsRO[i].text, fontSize);
					
				}
			}

			
			yPos -= scrollSpeed;

			
			if (yPos + creditCount * lineHeight < 0) {
				yPos = screenHeight;
			}

			delay(30);
		}
		else {
			
			for (int i = 0; i < creditCount; i++) {
				int yOffset = yPos + i * lineHeight;
				if (yOffset >= 0 && yOffset < screenHeight) {
					int textWidth = textwidth(creditsEN[i].text);
					int xPos = (screenWidth - textWidth) / 2;
						drawTextCredits(xPos, yOffset, creditsEN[i].text, fontSize);
				}
			}

			
			yPos -= scrollSpeed;

			
			if (yPos + creditCount * lineHeight < 0) {
				yPos = screenHeight;
			}

			delay(30);
			
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
				ok = 0;
			}
	}

	ma_sound_stop(&CreditMusic);
	ma_sound_seek_to_pcm_frame(&CreditMusic, 0);
	MainMenu();
}

void drawSettingsButton(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x - width / 5, y, x + width + width / 5, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x - width/5, y, x + width + width/5, y + height);

	// Draw text
	setbkcolor(finalColor);
	setcolor(textColor);
		settextstyle(EUROPEAN_FONT, HORIZ_DIR, height / 110);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	if (strcmp(text, "OPRESTE SUNETUL") == 0 && isMuted == TRUE) {
		outtextxy(textX, textY, "PORNESTE SUNETUL");
	}
	else {
		if (strcmp(text, "MUTE SOUND") == 0 && isMuted == TRUE)
			outtextxy(textX, textY, "UNMUTE SOUND");
		else
			outtextxy(textX, textY, text);
	}

	setbkcolor(button_color);
}


int detectSettingsMouseHover(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 2.5;
	int marginY = screenHeight / 4;

	for (int i = 0; i < SETTINGS_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  

		
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;  
}

// Draw Menu
void drawSettingsMenu(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 2.5;
	int marginY = screenHeight / 4;


	settextjustify(LEFT_TEXT, TOP_TEXT);

	for (int i = 0; i < SETTINGS_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20); 

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawSettingsButton(x, y, buttonWidth, buttonHeight, settingsTextRO[i], WHITE, BLACK, isHovered);
		else
			drawSettingsButton(x, y, buttonWidth, buttonHeight, settingsTextEN[i], WHITE, BLACK, isHovered);
	}
	int imageWidth = screenWidth / 3;  
	int imageX = (screenWidth - imageWidth) / 2; 
	int imageY = marginY - (x / 3 * 612) / x - screenHeight / 20; 


}

void SettingsMenu() {
	ma_sound_stop(&MapEditorMusic);
	ma_sound_seek_to_pcm_frame(&MapEditorMusic, 0);
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);

	menustate = 0;
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&MenuMusic)) ma_sound_start(&MenuMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		
		int mouseX = mousex();
		int mouseY = mousey();

		
		hoveredButton = detectSettingsMouseHover(mouseX, mouseY, screenWidth, screenHeight);

		
		drawSettingsMenu(screenWidth, screenHeight);

		
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					if (!isMuted) {
						volume += 0.1f;
						if (volume > 1.0f) volume = 1.0f;
						ma_engine_set_volume(&engine, volume);
						break;
					}
				case 1:
					if (!isMuted) {
						volume -= 0.1f;
						if (volume < 0.0f) volume = 0.0f;
						ma_engine_set_volume(&engine, volume);
						break;
					}
				case 2:
					isMuted = !isMuted;
					ma_engine_set_volume(&engine, isMuted ? 0.0f : volume);
					break;
				case 3:
					MainMenu();
					break;
				}
			}
		}

		page = 1 - page;
		delay(10);
	}

	
	exit(0);
}