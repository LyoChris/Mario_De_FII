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
#include "Game.h"
#include "Sounds.h"
#include "Loader.h"
#include "miniaudio.h"
#include "MapEditor.h"
#include "Colectibles.h"
#include "Loader.h"
using namespace std;

#define MARIO_TIME 0.05 // 80 ms
#define ENEMY_TIME 0.175  // 200 ms
#define FRAME_TIME 0.06 // 16 ms

void* playerImg1;

extern ma_engine engine;
extern LevelStats customstats[9];
extern ma_sound BackGroundMusic, StarTheme, DeathEffect, MenuMusic;
extern float wh, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000], mv2, map, power, timespent;
string direction, direction1;
int time1, okesc = 1, ok1 = 0;
clock_t start, initpause;
double MarioInterval = MARIO_TIME;
double enemyInterval = ENEMY_TIME;
double FrameInterval = FRAME_TIME;
double fireBallinterval = ENEMY_TIME / 1.5;

void MarioGame() {
    MapReseter();
    MapLoader();
    clock_t lastMarioMove = clock(); //facem cate un ceas pentru inamici si Mario
    clock_t lastEnemyMove = clock();
    clock_t lastFrame = clock();
	clock_t lastFireball = clock();
    start = clock();
    timespent = 0;
	ma_sound_stop(&BackGroundMusic);
	ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
    ma_sound_stop(&MenuMusic);
    ma_sound_seek_to_pcm_frame(&MenuMusic, 0);


    do {
        setbkcolor(RGB(126, 132, 246));
        setcolor(WHITE);
        if (power == 0) {
            if (!ma_sound_is_playing(&BackGroundMusic)) {
                ma_sound_stop(&StarTheme);
				ma_sound_seek_to_pcm_frame(&StarTheme, 0);
                ma_sound_start(&BackGroundMusic);
            }
        }
        else {
            MarioInterval = MarioInterval / 2;
            ma_sound_stop(&BackGroundMusic);
            if (!ma_sound_is_playing(&StarTheme)) {
                ma_sound_start(&StarTheme);
            }
        }

        clock_t now = clock();
        if ((now - lastFrame) / (double)CLOCKS_PER_SEC >= FrameInterval) {
            if (harta[(int)imario + 1][(int)jmario] == 0) {
                MarioInterval = MarioInterval / 1.07;
                ok1 = 1;
            }
            if ((now - lastMarioMove) / (double)CLOCKS_PER_SEC >= MarioInterval) {
                MarioMovement();
                lastMarioMove = now;
            }
			if ((now - lastFireball) / (double)CLOCKS_PER_SEC >= fireBallinterval) {
				fireballsmov();
				lastFireball = now;
			}
            fireballsmov();
            if ((now - lastEnemyMove) / (double)CLOCKS_PER_SEC >= enemyInterval) {
                EnemiesMoving();
                lastEnemyMove = now;
            }
            if (ok1 == 1) {
                MarioInterval = MarioInterval / 1.07;
                ok1 = 0;
            }
            if (power != 0) {
                MarioInterval = MarioInterval * 2;
            }
            lastFrame = now;
        }

    } while (okesc != 0);
    cleardevice();
    delay(300);
	closegraph();
}