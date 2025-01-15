#include "graphics.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include "Mario.h"
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Sounds.h"
#include "Loader.h"
#include "Menus.h"
#include "miniaudio.h"
using namespace std;

extern float wh, nci, ncf, nc1, nci;
extern int x, y, nl;

struct spawnpoint {
	int i1 = 0, j1 = 0;
	int i2 = 0, j2 = 0;

}spawn[100];

extern int CUSTOM_LEVEL_ITEMS;
extern char* customLevelText[10];

extern LevelStats levelstats[9], customstats[9];
extern ma_engine engine;
extern ma_sound plinc, incplace, mapediRO, mapediEN, blselecRO, blselecEN, BackGroundMusic, MapEditorMusic, MenuMusic;

int hartaloader[20][1000] = { 0 }, nr=0, edit = 1, mapi = 0, mapj = 1, selecpoz[15] = { 1,0,3,4,12,13,14,141,131,8,7,2,5,9,11}, iselec = 0, bkselect = 1, panelnr = 0, ncmax = 0, jpole = -1, ipole = -1;
float nwh, ncimap=0, ncfmap;
int SplitMenuItems = 1;

extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * flagpolemapedit, * pipehead, * pipebody, * pipeheadpir;
void* brickblockmap, * skyblockmap, * mario_vinemap, * mario_vine_topmap, * lucky_blockmap, * mario_coinmap, * mario_idle_rightmap, * one_upmap, * flagpolepmap, * gombamap,
* pipeheadmap, * pipebodymap, * pipeheadpirmap, * brickblockmono, * skyblockmono, * mario_vinemono, * mario_vine_topmono, * lucky_blockmono, * mario_coinmono,
* mario_idle_rightmono, * one_upmono, * flagpolepmono, * gombamono, * pipeheadmono, * pipebodymono, * pipeheadpirmono, * flagpolemapeditmono, * flagpolemapeditp,
* Rpipeheadpirmono, * Rpipeheadmono, * Rpipeheadpir, * Rpipehead, * Rpipeheadpirmap, * Rpipeheadmap, * skyblockmap1;


void PutMovingImage(int i, int j) {
	if (hartaloader[i][j] == 0)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, skyblockmap, COPY_PUT);
	if (hartaloader[i][j] == 1)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, brickblockmap, COPY_PUT);
	if (hartaloader[i][j] == 3)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vinemap, COPY_PUT);
	if (hartaloader[i][j] == 4)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vine_topmap, COPY_PUT);
	if (hartaloader[i][j] == 5)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, gombamap, COPY_PUT);
	if (hartaloader[i][j] == 9)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_idle_rightmap, COPY_PUT);
	if (hartaloader[i][j] == 8)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, lucky_blockmap, COPY_PUT);
	if (hartaloader[i][j] == 7)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_coinmap, COPY_PUT);
	if (hartaloader[i][j] == 13)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadpirmap, COPY_PUT); // placeholder pt pirhana
	if (hartaloader[i][j] == 14)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadmap, COPY_PUT); // placeholder pt pipehead
	if (hartaloader[i][j] == 12)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipebodymap, COPY_PUT); // placeholder pt pipebody
	if (hartaloader[i][j] == 2)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, one_upmap, COPY_PUT);
	if (hartaloader[i][j] == 11)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, flagpolemapeditp, COPY_PUT);
	if (hartaloader[i][j] == 141)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, Rpipeheadpirmap, COPY_PUT);
	if (hartaloader[i][j] == 131)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, Rpipeheadmap, COPY_PUT);
}

void PutMapEditor(int i, int j, int block) {
	if (block == 0)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, skyblockmap1, COPY_PUT);
	if (block == 1)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, brickblockmap, COPY_PUT);
	if (block == 3)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vinemap, COPY_PUT);
	if (block == 4)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vine_topmap, COPY_PUT);
	if (block == 5)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, gombamap, COPY_PUT);
	if (block == 9)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_idle_rightmap, COPY_PUT);
	if (block == 8)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, lucky_blockmap, COPY_PUT);
	if (block == 7)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_coinmap, COPY_PUT);
	if (block == 13)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadpirmap, COPY_PUT); // placeholder pt pirhana
	if (block == 14)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadmap, COPY_PUT); // placeholder pt pipehead
	if (block == 12)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipebodymap, COPY_PUT); // placeholder pt pipebody
	if (block == 2)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, one_upmap, COPY_PUT);
	if (block == 11)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, flagpolemapeditp, COPY_PUT);
	if (block == 141) 
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, Rpipeheadpirmap, COPY_PUT);
	if(block == 131)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, Rpipeheadmap, COPY_PUT);
}

void SelectorImageMono(int i){
	if (iselec == 0) putimage((1 + iselec * 1.5) * wh, 17 * wh, brickblockmono, COPY_PUT);
	if (iselec == 1) putimage((1 + iselec * 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	if (iselec == 2)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	if (iselec == 3)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	if (iselec == 4)putimage((1 + iselec * 1.5) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((1 + iselec*1.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((1 + iselec*1.5) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((1 + iselec * 1.5) * wh, 17 * wh, Rpipeheadmono, COPY_PUT);
	if (iselec == 8)putimage((1 + iselec * 1.5) * wh, 17 * wh, Rpipeheadpirmono, COPY_PUT);
	if (iselec == 9)putimage((1 + iselec * 1.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	if (iselec == 10)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	if (iselec == 11)putimage((1 + iselec * 1.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	if (iselec == 12)putimage((1 + iselec * 1.5) * wh, 17 * wh, gombamono, COPY_PUT);
	if (iselec == 13)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	if (iselec == 14)putimage((1 + iselec * 1.5) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);
}

void SelectorImage(int i) {
	if (iselec == 0) putimage((1 + iselec * 1.5) * wh, 17 * wh, brickblock, COPY_PUT);
	if (iselec == 1) putimage((1 + iselec*1.5) * wh, 17 * wh, skyblock, COPY_PUT);
	if (iselec == 2)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_vine, COPY_PUT);
	if (iselec == 3)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_vine_top, COPY_PUT);
	if (iselec == 4)putimage((1 + iselec * 1.5) * wh, 17 * wh, pipebody, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((1 + iselec * 1.5) * wh, 17 * wh, pipeheadpir, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((1 + iselec * 1.5) * wh, 17 * wh, pipehead, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((1 + iselec * 1.5) * wh, 17 * wh, Rpipehead, COPY_PUT);
	if (iselec == 8)putimage((1 + iselec * 1.5) * wh, 17 * wh, Rpipeheadpir, COPY_PUT);


	if (iselec == 9)putimage((1 + iselec * 1.5) * wh, 17 * wh, lucky_block, COPY_PUT);
	if (iselec == 10)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_coin, COPY_PUT);
	if (iselec == 11)putimage((1 + iselec * 1.5) * wh, 17 * wh, one_up, COPY_PUT);
	if (iselec == 12)putimage((1 + iselec * 1.5) * wh, 17 * wh, goomba_walking_1, COPY_PUT);
	if (iselec == 13)putimage((1 + iselec * 1.5) * wh, 17 * wh, mario_idle_right, COPY_PUT);
	if (iselec == 14)putimage((1 + iselec * 1.5) * wh, 17 * wh, flagpolemapedit, COPY_PUT);
}

void MapPaneler() {
	setvisualpage(0);
	setactivepage(0);
	setbkcolor(BLACK);
	cleardevice();
	setbkcolor(BLACK);

	int lastColumnX = 0; 

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	// Draw the matrix
	for (int i = 0; i < nl; i += 1) {
		for (int j = (int)ncimap; j < ncfmap; j += 1) {
			PutMovingImage(i, j);
			lastColumnX = j - ncimap; 
		}
	}

	int blockWidth = nwh;
	int menuStartX = (lastColumnX + 4) * blockWidth + (blockWidth / 10);

	// Place other game elements
	putimage((1 + 0 * 1.5) * wh, 17 * wh, brickblockmono, COPY_PUT);
	putimage((1 + 1 * 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((1 + 2 * 1.5) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((1 + 3 * 1.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((1 + 4 * 1.5) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	putimage((1 + 5 * 1.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	putimage((1 + 6 * 1.5) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	putimage((1 + 7 * 1.5) * wh, 17 * wh, Rpipeheadmono, COPY_PUT);
	putimage((1 + 8 * 1.5) * wh, 17 * wh, Rpipeheadpirmono, COPY_PUT);
	putimage((1 + 9 * 1.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((1 + 10 * 1.5) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((1 + 11 * 1.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((1 + 12 * 1.5) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((1 + 13 * 1.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((1 + 14 * 1.5) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

	SelectorImage(iselec);
	// Menu parameters
	int winHeight = getmaxy();
	int padding = blockWidth / 5;
	int elementHeight = winHeight / 15;
	int rectWidth = elementHeight;
	int textSize = elementHeight / 12;

	int baseX = menuStartX;
	int baseY = padding * 6;

	char* menuItemsRO[5] = { "SALVEAZA HARTA", "INCARCA HARTA", "PANOUL ANTERIOR", "PANOUL URMATOR", "INAPOI" };
	char* menuItemsEN[5] = { "SAVE MAP", "LOAD MAP", "PREV PANEL", "NEXT PANEL", "BACK" };
	char keys[5] = { 'M', 'N', 'J', 'L', 'B' };

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, textSize);

	
	for (int i = 0; i < 5; i++) {
		int rectY = baseY + i * (elementHeight + 2 * padding);

		
		rectangle(baseX, rectY, baseX + rectWidth, rectY + elementHeight);

		
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		char key[2] = { keys[i], '\0' };
		int keyCenterX = baseX + rectWidth / 2;
		int keyCenterY = rectY + elementHeight / 1.5;
		outtextxy(keyCenterX, keyCenterY, key);

		
		if (SplitMenuItems == 1 && i < 4) { 
			char temp[50];
			strncpy(temp, menuItemsRO[i], sizeof(temp) - 1); 
			temp[sizeof(temp) - 1] = '\0'; 


			int splitY = rectY; 
			char* word = strtok(temp, " ");
			while (word != nullptr) {
				settextjustify(LEFT_TEXT, TOP_TEXT);
				outtextxy(baseX + rectWidth + padding, splitY, word);
				splitY += textSize * 3 + 3 * padding; 
				word = strtok(nullptr, " ");
			}
		}
		else {
			settextjustify(LEFT_TEXT, CENTER_TEXT);
			outtextxy(baseX + rectWidth + padding, keyCenterY, menuItemsEN[i]);
		}
	}

	// Draw panel controls below the matrix
	int panelTextY = nl * (blockWidth + 2);
	int matrixEndX = (lastColumnX + 1) * blockWidth;

	// Current Panel
	int currentCenterX = (matrixEndX - blockWidth) / 3;
	char currentPanelText[20];
	if (SplitMenuItems == 1)
		sprintf(currentPanelText, "PANOUL CURENT: %d", panelnr);
	else
		sprintf(currentPanelText, "CURRENT PANEL: %d", panelnr);
	outtextxy(currentCenterX, panelTextY + elementHeight / 2, currentPanelText);

}

void InitialDrawing() {
	cleardevice();
	ncimap = 0;
	ncfmap = ncf;
	panelnr = 0;

	int lastColumnX = 0;

	// Draw the matrix
	for (int i = 0; i < nl; i += 1) {
		for (int j = (int)ncimap; j < ncfmap; j += 1) {
			PutMovingImage(i, j);
			lastColumnX = j;
		}
	}

	
	int blockWidth = nwh;
	int menuStartX = (lastColumnX + 4) * blockWidth + (blockWidth / 10);

	// Place other game elements
	putimage((1 + 0 * 1.5) * wh, 17 * wh, brickblock, COPY_PUT);
	putimage((1 + 1 * 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((1 + 2 * 1.5) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((1 + 3 * 1.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((1 + 4 * 1.5) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	putimage((1 + 5 * 1.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	putimage((1 + 6 * 1.5) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	putimage((1 + 7 * 1.5) * wh, 17 * wh, Rpipeheadmono, COPY_PUT);
	putimage((1 + 8 * 1.5) * wh, 17 * wh, Rpipeheadpirmono, COPY_PUT);
	putimage((1 + 9 * 1.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((1 + 10 * 1.5) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((1 + 11 * 1.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((1 + 12 * 1.5) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((1 + 13 * 1.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((1 + 14 * 1.5) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

	// Menu parameters
	int winHeight = getmaxy();
	int padding = blockWidth / 5;
	int elementHeight = winHeight / 15;
	int rectWidth = elementHeight;
	int textSize = elementHeight / 12;

	int baseX = menuStartX;
	int baseY = padding * 6;

	char* menuItemsRO[5] = { "SALVEAZA HARTA", "INCARCA HARTA", "PANOUL ANTERIOR", "PANOUL URMATOR", "INAPOI" };
	char* menuItemsEN[5] = { "SAVE MAP", "LOAD MAP", "PREV PANEL", "NEXT PANEL", "BACK" };
	char keys[5] = { 'M', 'N', 'J', 'L', 'B' };

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, textSize);

	
	for (int i = 0; i < 5; i++) {
		int rectY = baseY + i * (elementHeight + 2 * padding);

		
		rectangle(baseX, rectY, baseX + rectWidth, rectY + elementHeight);

		
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		char key[2] = { keys[i], '\0' };
		int keyCenterX = baseX + rectWidth / 2;
		int keyCenterY = rectY + elementHeight / 1.5;
		outtextxy(keyCenterX, keyCenterY, key);

		
		if (SplitMenuItems == 1&& i < 4) {
			char temp[50];
			strncpy(temp, menuItemsRO[i], sizeof(temp) - 1); 
			temp[sizeof(temp) - 1] = '\0';

		
			int splitY = rectY; 
			char* word = strtok(temp, " ");
			while (word != nullptr) {
				settextjustify(LEFT_TEXT, TOP_TEXT);
				outtextxy(baseX + rectWidth + padding, splitY, word);
				splitY += textSize * 3 + 3 * padding; 
				word = strtok(nullptr, " ");
			}
		}
		else {
			settextjustify(LEFT_TEXT, CENTER_TEXT);
			outtextxy(baseX + rectWidth + padding, keyCenterY, menuItemsEN[i]);
		}
	}

	// Draw panel controls below the matrix
	int panelTextY = nl * (blockWidth + 2);
	int matrixEndX = (lastColumnX + 1) * blockWidth;

	// Current Panel
	int currentCenterX = (matrixEndX - blockWidth) / 3;
	char currentPanelText[20];
	if (SplitMenuItems == 1)
		sprintf(currentPanelText, "PANOUL CURENT: %d", panelnr);
	else
		sprintf(currentPanelText, "CURRENT PANEL: %d", panelnr);
	outtextxy(currentCenterX, panelTextY + elementHeight / 2, currentPanelText);
}

void saveMap() {
	char filename[50] = ""; // Buffer for the file name
	int pos = 0;           // Current position in the filename buffer
	char ch;

	// Prompt user to enter filename
	setvisualpage(1);
	setactivepage(1);
	cleardevice();

	setcolor(WHITE);
	int fontSize = min(x / 20, y / 15); // Scale with window size
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, fontSize / 10); // Adjust text style

	int textWidth, textHeight;

	char promptEN[] = "Enter filename to save (without extension):";
	char promptRO[] = "Introduceti numele fisierului de salvat (fara extensie)";
	if (SplitMenuItems == 1) {
		textWidth = textwidth(promptRO);
		textHeight = textheight(promptRO);
		outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, promptRO);
	}
	else {
		textWidth = textwidth(promptEN);
		textHeight = textheight(promptEN);
		outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, promptEN);
	}

	while (true) {
		ch = getch();

		if (ch == 13) { // If ENTER is pressed
			break;
		}
		else if (ch == 8) { // If BACKSPACE is pressed
			if (pos > 0) {
				pos--;
				filename[pos] = '\0'; // Remove the last character

				// Clear the input area before redrawing
				int inputWidth = textwidth("W") * 50; // Approximate width for 50 characters
				setfillstyle(SOLID_FILL, BLACK);
				bar((x - inputWidth) / 2, y / 2 - textHeight / 2, (x + inputWidth) / 2, y / 2 + textHeight / 2);

				// Redraw the updated filename
				outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
			}
		}
		else if (pos < 49 && (isalnum(ch) || ch == '_')) { // Allow alphanumeric and underscore
			filename[pos] = ch;
			pos++;
			filename[pos] = '\0'; // Null-terminate the string

			// Clear the input area before redrawing
			int inputWidth = textwidth("W") * 50; // Approximate width for 50 characters
			setfillstyle(SOLID_FILL, BLACK);
			bar((x - inputWidth) / 2, y / 2 - textHeight / 2, (x + inputWidth) / 2, y / 2 + textHeight / 2);

			// Redraw the updated filename
			outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
		}
	}

	if (CUSTOM_LEVEL_ITEMS ==9) {
		CustomLevelsMenuReplacer(filename);
		strcat(filename, ".txt"); // Append file extension

		// Save the grid to the file
		ofstream outfile(filename);
		outfile << ncmax << '\n';
		if (outfile) {
			for (int i = 0; i < nl; i++) {
				for (int j = 0; j < ncmax; j++) {
					if (hartaloader[i][j] == 131) {
						hartaloader[i][j] = 13;
					}
					if (hartaloader[i][j] == 141) {
						hartaloader[i][j] = 14;
					}
					outfile << hartaloader[i][j] << " ";
				}
				outfile << endl;
			}
			outfile.close();
		}
		return;
	}
	else {
		customLevelText[CUSTOM_LEVEL_ITEMS -1] = new char[strlen(filename) + 1];  // Allocate memory for the string
		strcpy(customLevelText[CUSTOM_LEVEL_ITEMS - 1], filename);  // Copy the string into the allocated memory
		customstats[CUSTOM_LEVEL_ITEMS - 1].name = new char[strlen(filename) + 1];
		strcpy(customstats[CUSTOM_LEVEL_ITEMS - 1].name, filename);
		customstats[CUSTOM_LEVEL_ITEMS - 1].disname = new char[strlen(filename) + 1];
		strcpy(customstats[CUSTOM_LEVEL_ITEMS - 1].disname, filename);
		customstats[CUSTOM_LEVEL_ITEMS - 1].score = 0;
		customstats[CUSTOM_LEVEL_ITEMS - 1].time = 0;
		customstats[CUSTOM_LEVEL_ITEMS - 1].enemies = 0;
		if (SplitMenuItems) {
			customLevelText[CUSTOM_LEVEL_ITEMS] = new char[strlen("INAPOI") + 1];
			strcpy(customLevelText[CUSTOM_LEVEL_ITEMS], "INAPOI");
		}
		else {
			customLevelText[CUSTOM_LEVEL_ITEMS] = new char[strlen("BACK") + 1];
			strcpy(customLevelText[CUSTOM_LEVEL_ITEMS], "BACK");
		}
		CUSTOM_LEVEL_ITEMS++;
	}
	strcat(filename, ".txt"); // Append file extension

	// Save the grid to the file
	ofstream outfile(filename);
	outfile << ncmax << '\n';
	if (outfile) {
		for (int i = 0; i < nl; i++) {
			for (int j = 0; j < ncmax; j++) {
				outfile << hartaloader[i][j] << " ";
			}
			outfile << endl;
		}
		outfile.close();
		if (SplitMenuItems == 0)
			outtextxy((x - textwidth("Map saved successfully!")) / 2, y - 7 * nwh, "Map saved successfully!");
		else
			outtextxy((x - textwidth("Harta salvata cu succes!")) / 2, y - 7 * nwh, "Harta salvata cu succes!");
	}
	else {
		setcolor(RED);
		if(SplitMenuItems == 0)
			outtextxy((x - textwidth("Error saving file.")) / 2, y - 7 * nwh, "Error saving6 file.");
		else
			outtextxy((x - textwidth("Eroare la salvare.")) / 2, y - 7 * nwh, "Eroare la salvare.");
	}
	delay(2000);
	cleardevice();
	setvisualpage(0);
	setactivepage(0);
	return;
}

void loadMap() {
	char filename[50] = ""; // Buffer for the file name
	int pos = 0;           // Current position in the filename buffer
	char ch;
	// Prompt user to enter filename
	setvisualpage(1);
	setactivepage(1);
	cleardevice();

	setcolor(WHITE);
	int fontSize = min(x / 20, y / 15); // Scale with window size
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, fontSize / 10); // Adjust text style
	
	int textWidth, textHeight;

	char promptEN[] = "Enter filename to load (without extension):";
	char promptRO[] = "Introduceti numele fisierului de încarcat(fara extensie) :";
	if (SplitMenuItems == 1) {
		textWidth = textwidth(promptRO);
		textHeight = textheight(promptRO);
		outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, promptRO);
	}
	else {
		textWidth = textwidth(promptEN);
		textHeight = textheight(promptEN);
		outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, promptEN);
	}
	

	// Loop to capture user input
	while (true) {
		ch = getch();

		if (ch == 13) { // If ENTER is pressed
			break;
		}
		else if (ch == 8) { // If BACKSPACE is pressed
			if (pos > 0) {
				pos--;
				filename[pos] = '\0';

				int inputWidth = textwidth("W") * 50;
				setfillstyle(SOLID_FILL, BLACK);
				bar((x - inputWidth) / 2, y / 2 - textHeight / 2, (x + inputWidth) / 2, y / 2 + textHeight / 2);

				// Redraw the updated filename
				outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
			}
		}
		else if (pos < 49 && (isalnum(ch) || ch == '_')) { // Allow alphanumeric and underscore
			filename[pos] = ch;
			pos++;
			filename[pos] = '\0'; // Null-terminate the string

			// Clear the input area before redrawing
			int inputWidth = textwidth("W") * 50; // Approximate width for 50 characters
			setfillstyle(SOLID_FILL, BLACK);
			bar((x - inputWidth) / 2, y / 2 - textHeight / 2, (x + inputWidth) / 2, y / 2 + textHeight / 2);

			// Redraw the updated filename
			outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
		}
	}

	strcat(filename, ".txt"); // Append file extension

	// Save the grid to the file
	ifstream infile(filename);
	memset(hartaloader, 0, sizeof(hartaloader));
	infile >> ncmax;
	if (infile) {
		for (int i = 0; i < nl; i++) {
			for (int j = 0; j < ncmax; j++) {
				infile >> hartaloader[i][j];
				if (hartaloader[i][j] == 13 && (hartaloader[i - 1][j] == 1 || hartaloader[i - 1][j] == 12)) {
					hartaloader[i][j] = 131;
				}
				if (hartaloader[i][j] == 14 && (hartaloader[i - 1][j] == 1 || hartaloader[i - 1][j] == 12)) {
					hartaloader[i][j] = 141;
				}
			};
		}
		infile.close();
		if (SplitMenuItems == 1)
			outtextxy((x - textwidth("Harta incarcata cu succes!")) / 2, y - 7 * nwh, "Harta incarcata cu succes!");
		else
		outtextxy((x - textwidth("Map loaded successfully!")) / 2, y - 7*nwh, "Map loaded successfully!");
	}
	else {
		setcolor(RED);
		if(SplitMenuItems == 1)
			outtextxy((x - textwidth("Eroare la incarcare.")) / 2, y - 7 * nwh, "Eroare la incarcare.");
		else
			outtextxy((x - textwidth("Error loading file.")) / 2, y - 7*nwh, "Error loading file.");
	}
	setcolor(WHITE);
	delay(2000);
	cleardevice();
	setactivepage(0);
	InitialDrawing();
	setvisualpage(0);
}

void MapEditorLevels() {
	ma_sound_stop(&MenuMusic);
	ma_sound_seek_to_pcm_frame(&MenuMusic, 0);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
	if (!ma_sound_is_playing(&MapEditorMusic)) ma_sound_start(&MapEditorMusic);
	setvisualpage(0);
	setactivepage(0);
	nwh = 0.7 * wh;
	ncfmap = nc1;
	memset(hartaloader, 0, sizeof(hartaloader));
	InitialDrawing();

	while (true) {
		if (!ma_sound_is_playing(&MapEditorMusic)) ma_sound_start(&MapEditorMusic);
		PutMovingImage(mapi, mapj);
		PutMapEditor(mapi, mapj, bkselect);
		SelectorImage(iselec);
		char t = getch();
		if (!ma_sound_is_playing(&MapEditorMusic)) ma_sound_start(&MapEditorMusic);
		if (t == 'm') {
			saveMap();
		}
		if (t == 'n') loadMap();
		if (t == 'c' && edit == 0) {
			edit = 1;
			if (SplitMenuItems == 1) {
				ma_sound_stop(&blselecRO);
				ma_sound_seek_to_pcm_frame(&blselecRO, 0);
				ma_sound_stop(&mapediRO);
				ma_sound_seek_to_pcm_frame(&mapediRO, 0);
				ma_sound_start(&mapediRO);
				delay(10);
			}
			else {
				ma_sound_stop(&blselecEN);
				ma_sound_seek_to_pcm_frame(&blselecEN, 0);
				ma_sound_stop(&mapediEN);
				ma_sound_seek_to_pcm_frame(&mapediEN, 0);
				ma_sound_start(&mapediEN);
				delay(10);
			}
		}
		else {
			if (t == 'c') {
				edit = 0;
				if (SplitMenuItems == 1) {
					ma_sound_stop(&mapediRO);
					ma_sound_seek_to_pcm_frame(&mapediRO, 0);
					ma_sound_stop(&blselecRO);
					ma_sound_seek_to_pcm_frame(&blselecRO, 0);
					ma_sound_start(&blselecRO);
					delay(10);
				}
				else {
					ma_sound_stop(&mapediEN);
					ma_sound_seek_to_pcm_frame(&mapediEN, 0);
					ma_sound_stop(&blselecEN);
					ma_sound_seek_to_pcm_frame(&blselecEN, 0);
					ma_sound_start(&blselecEN);
					delay(10);
				}
			}
		}
		if (edit == 1) {
			PutMovingImage(mapi, mapj);
			PutMapEditor(mapi, mapj, bkselect);
			if ((t == 'w' || t == 72) && mapi> 0) {
				PutMovingImage(mapi, mapj);
				mapi--;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if ((t == 'a'|| t==75) && mapj > ncimap) {
				PutMovingImage(mapi, mapj);
				mapj--;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if ((t == 'd'|| t == 77) && mapj < ncfmap-1) {
				PutMovingImage(mapi, mapj);
				mapj++;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if ((t == 's' || t == 80) && mapi < nl-1) {
				PutMovingImage(mapi, mapj);
				mapi++;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if ((int)t == 32) {
				if (bkselect == 11 && mapi > 7 && mapj < ncfmap-3) {
					if (ipole == -1 && jpole == -1) {
						hartaloader[mapi][mapj] = bkselect;
						ipole = mapi;
						jpole = mapj;
					}
					else {
						putimage((jpole - ncimap + 1) * nwh, (ipole + 1) * nwh, skyblockmap, COPY_PUT);
						hartaloader[ipole][jpole] = 0;
						hartaloader[mapi][mapj] = bkselect;
						ipole = mapi;
						jpole = mapj;
					}
				}
				else {
					if (bkselect == 11) {
						if (SplitMenuItems == 1) {
							ma_sound_stop(&mapediRO);
							ma_sound_seek_to_pcm_frame(&mapediRO, 0);
							ma_sound_stop(&plinc);
							ma_sound_seek_to_pcm_frame(&plinc, 0);
							ma_sound_start(&plinc);
						}
						else {
							ma_sound_stop(&mapediEN);
							ma_sound_seek_to_pcm_frame(&mapediEN, 0);
							ma_sound_stop(&incplace);
							ma_sound_seek_to_pcm_frame(&incplace, 0);
							ma_sound_start(&incplace);
						}
					}
				}
				if (bkselect == 5 && hartaloader[mapi + 1][mapj] != 0) {
					hartaloader[mapi][mapj] = bkselect;
				}
				else {
					if (bkselect == 5 && hartaloader[mapi + 1][mapj] == 0) {
						if (SplitMenuItems == 1) {
							ma_sound_stop(&mapediRO);
							ma_sound_seek_to_pcm_frame(&mapediRO, 0);
							ma_sound_stop(&plinc);
							ma_sound_seek_to_pcm_frame(&plinc, 0);
							ma_sound_start(&plinc);
						}
						else {
							ma_sound_stop(&mapediEN);
							ma_sound_seek_to_pcm_frame(&mapediEN, 0);
							ma_sound_stop(&incplace);
							ma_sound_seek_to_pcm_frame(&incplace, 0);
							ma_sound_start(&incplace);
						}
					}
				}
				if (bkselect != 11 && bkselect != 5) {
					hartaloader[mapi][mapj] = bkselect;
				}
			}
			if (t == 'j' && ncimap > 0) {
				panelnr--;
				ncimap =ncimap- nc1;
				ncfmap =ncfmap - nc1;
				mapi = 0;
				mapj = ncimap + 1;
				cleardevice();
				MapPaneler();
			}
			if (t == 'l' && ncfmap < 1000) {
				panelnr++;
				ncimap = ncimap + nc1;
				ncfmap = ncfmap + nc1;
				mapi = 0;
				mapj = ncimap+1;
				cleardevice();
				MapPaneler();
			}
			if(ncfmap>ncmax) ncmax = (int)ncfmap;
		}
		if (edit == 0) {
			if ((t == 'a' || t== 75) && iselec > 0) {
				SelectorImageMono(iselec);
				iselec--;
				SelectorImage(iselec);
			}
			if ((t == 'd' || t == 77) && iselec < 16) {
				SelectorImageMono(iselec);
				iselec++;
				SelectorImage(iselec);
			}
			if ((int)t == 32) {
				bkselect = selecpoz[iselec];
				if (SplitMenuItems == 0) {
					ma_sound_start(&mapediEN);
				}
				else {
					ma_sound_start(&mapediRO);
				}
				edit = 1;
			}

		}
		if (t == 'b') {
			ma_sound_stop(&mapediRO);
			ma_sound_stop(&mapediEN);
			ma_sound_stop(&blselecRO);
			ma_sound_stop(&blselecEN);
			ma_sound_stop(&plinc);
			ma_sound_stop(&incplace);
			CustomMenu();
		}
	}
	
}