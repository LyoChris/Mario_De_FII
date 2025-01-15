#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <string>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Menus.h"
#include "miniaudio.h"

using namespace std;

#define MAX1 30
#define MAX2 1000

extern double MarioInterval;
extern string cht;
LevelStats levelstats[9], customstats[9];
extern ma_engine engine;
extern ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, DeathEffect, BackGroundMusic, StageClear, OneUpEffect, FireBallEffect, PowerUpAppearEffect, 
PowerUpEffect, DmgEffect, FlagEffect;
extern clock_t start, initpause;
extern colectible coins[100], life[100], starpow[100], fflower[100];
extern firebll fireb[9];
extern goompa gompav[100];
extern pirhana piranav[100];
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * flagpolemapedit, * mario_jump_2, * mario_star,
* Mmario_climbing_down_1, * Mmario_climbing_down_2, * Mmario_climbing_up_1,
* Mmario_climbing_up_2, * Mmario_idle_left, * Mmario_idle_right, * Mmario_jump_1, * Mmario_left_run_1, * Mmario_left_run_2, * Mmario_left_run_3, * Mmario_right_run_1,
* Mmario_right_run_2, * Mmario_right_run_3, * Mmario_jump_2, * MFmario_climbing_down_1, * MFmario_climbing_down_2, * MFmario_climbing_up_1,
* MFmario_climbing_up_2, * MFmario_idle_left, * MFmario_idle_right, * MFmario_jump_1, * MFmario_left_run_1, * MFmario_left_run_2, * MFmario_left_run_3, * MFmario_right_run_1,
* MFmario_right_run_2, * MFmario_right_run_3, * MFmario_jump_2, * Fmario_climbing_down_1, * Fmario_climbing_down_2, * Fmario_climbing_up_1,
* Fmario_climbing_up_2, * Fmario_idle_left, * Fmario_idle_right, * Fmario_jump_1, * Fmario_left_run_1, * Fmario_left_run_2, * Fmario_left_run_3, * Fmario_right_run_1,
* Fmario_right_run_2, * Fmario_right_run_3, * Fmario_jump_2, * fireball_1, * fireball_2, * fire_flower, * pipehead, * Rpipehead,
* mario_vine_idle_up, * mario_vine_idle_down, * Mmario_vine_idle_up, * Mmario_vine_idle_down, * Fmario_vine_idle_up, * Fmario_vine_idle_down,
* FMmario_vine_idle_up, * FMmario_vine_idle_down;

double time_spent;
extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000], mv2, map, stage=-7, mappart, coino, lifo, flagpole, staro, SplitMenuItems, fpow;
extern int time1, okesc, n, selectedOption, p, firo, flagpolej , flagpolei;
string direct;
int score1, lifes = 3, okmov = 0, shoot = 0, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0, hoverm = 0, play = 0, gdead = 0, hit, power = 0, pdead = 0, timespent = 0;

void MarioStageput() {
    switch (stage) {
    case -10:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_up_1, COPY_PUT); break;
    case 10:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_up_2, COPY_PUT); break;
    case -9:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_down_1, COPY_PUT); break;
    case 9:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_down_2, COPY_PUT); break;
    case -7:
		putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT); break;
    case 7:
		putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT); break;
    case 1:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_1, COPY_PUT); break;
    case 2:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_2, COPY_PUT); break;
    case 3:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_3, COPY_PUT); break;
    case -1:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_1, COPY_PUT); break;
    case -2:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_2, COPY_PUT); break;
    case -3:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_3, COPY_PUT); break;
    case -6:
		putimage((jmario - nci) * wh, imario * wh, mario_jump_1, COPY_PUT); break;
    case 6:
        putimage((jmario - nci) * wh, imario * wh, mario_jump_2, COPY_PUT); break;
    }
}

void MarioStageread() {
    switch (stage) {
    case -10:
        readimagefile("mario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("mario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("mario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("mario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("mario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("mario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("mario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("mario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("mario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("mario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 6:
		readimagefile("mario_jump_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void MarioStageputM() {
    switch (stage) {
    case -10:
        putimage((jmario - nci) * wh, imario * wh, Mmario_climbing_up_1, COPY_PUT); break;
    case 10:
        putimage((jmario - nci) * wh, imario * wh, Mmario_climbing_up_2, COPY_PUT); break;
    case -9:
        putimage((jmario - nci) * wh, imario * wh, Mmario_climbing_down_1, COPY_PUT); break;
    case 9:
        putimage((jmario - nci) * wh, imario * wh, Mmario_climbing_down_2, COPY_PUT); break;
    case -7:
        putimage((jmario - nci) * wh, imario * wh, Mmario_idle_right, COPY_PUT); break;
    case 7:
        putimage((jmario - nci) * wh, imario * wh, Mmario_idle_left, COPY_PUT); break;
    case 1:
        putimage((jmario - nci) * wh, imario * wh, Mmario_left_run_1, COPY_PUT); break;
    case 2:
        putimage((jmario - nci) * wh, imario * wh, Mmario_left_run_2, COPY_PUT); break;
    case 3:
        putimage((jmario - nci) * wh, imario * wh, Mmario_left_run_3, COPY_PUT); break;
    case -1:
        putimage((jmario - nci) * wh, imario * wh, Mmario_right_run_1, COPY_PUT); break;
    case -2:
        putimage((jmario - nci) * wh, imario * wh, Mmario_right_run_2, COPY_PUT); break;
    case -3:
        putimage((jmario - nci) * wh, imario * wh, Mmario_right_run_3, COPY_PUT); break;
    case -6:
        putimage((jmario - nci) * wh, imario * wh, Mmario_jump_1, COPY_PUT); break;
    case 6:
        putimage((jmario - nci) * wh, imario * wh, Mmario_jump_2, COPY_PUT); break;
    }
}

void MarioStagereadM() {
    switch (stage) {
    case -10:
        readimagefile("Mmario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("Mmario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("Mmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("Mmario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("Mmario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("Mmario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("Mmario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("Mmario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("Mmario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("Mmario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("Mmario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("Mmario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("Mmario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 6:
        readimagefile("Mmario_jump_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void MarioStageputF() {
    switch (stage) {
    case -10:
        putimage((jmario - nci) * wh, imario * wh, Fmario_climbing_up_1, COPY_PUT); break;
    case 10:
        putimage((jmario - nci) * wh, imario * wh, Fmario_climbing_up_2, COPY_PUT); break;
    case -9:
        putimage((jmario - nci) * wh, imario * wh, Fmario_climbing_down_1, COPY_PUT); break;
    case 9:
        putimage((jmario - nci) * wh, imario * wh, Fmario_climbing_down_2, COPY_PUT); break;
    case -7:
        putimage((jmario - nci) * wh, imario * wh, Fmario_idle_right, COPY_PUT); break;
    case 7:
        putimage((jmario - nci) * wh, imario * wh, Fmario_idle_left, COPY_PUT); break;
    case 1:
        putimage((jmario - nci) * wh, imario * wh, Fmario_left_run_1, COPY_PUT); break;
    case 2:
        putimage((jmario - nci) * wh, imario * wh, Fmario_left_run_2, COPY_PUT); break;
    case 3:
        putimage((jmario - nci) * wh, imario * wh, Fmario_left_run_3, COPY_PUT); break;
    case -1:
        putimage((jmario - nci) * wh, imario * wh, Fmario_right_run_1, COPY_PUT); break;
    case -2:
        putimage((jmario - nci) * wh, imario * wh, Fmario_right_run_2, COPY_PUT); break;
    case -3:
        putimage((jmario - nci) * wh, imario * wh, Fmario_right_run_3, COPY_PUT); break;
    case -6:
        putimage((jmario - nci) * wh, imario * wh, Fmario_jump_1, COPY_PUT); break;
    case 6:
        putimage((jmario - nci) * wh, imario * wh, Fmario_jump_2, COPY_PUT); break;
    }
}

void MarioStagereadF() {
    switch (stage) {
    case -10:
        readimagefile("Fmario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("Fmario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("Fmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("Fmario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("Fmario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("Fmario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("Fmario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("Fmario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("Fmario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("Fmario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("Fmario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("Fmario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("Fmario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 6:
        readimagefile("Fmario_jump_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void MarioStageputMF() {
    switch (stage) {
    case -10:
        putimage((jmario - nci) * wh, imario * wh, MFmario_climbing_up_1, COPY_PUT); break;
    case 10:
        putimage((jmario - nci) * wh, imario * wh, MFmario_climbing_up_2, COPY_PUT); break;
    case -9:
        putimage((jmario - nci) * wh, imario * wh, MFmario_climbing_down_1, COPY_PUT); break;
    case 9:
        putimage((jmario - nci) * wh, imario * wh, MFmario_climbing_down_2, COPY_PUT); break;
    case -7:
        putimage((jmario - nci) * wh, imario * wh, MFmario_idle_right, COPY_PUT); break;
    case 7:
        putimage((jmario - nci) * wh, imario * wh, MFmario_idle_left, COPY_PUT); break;
    case 1:
        putimage((jmario - nci) * wh, imario * wh, MFmario_left_run_1, COPY_PUT); break;
    case 2:
        putimage((jmario - nci) * wh, imario * wh, MFmario_left_run_2, COPY_PUT); break;
    case 3:
        putimage((jmario - nci) * wh, imario * wh, MFmario_left_run_3, COPY_PUT); break;
    case -1:
        putimage((jmario - nci) * wh, imario * wh, MFmario_right_run_1, COPY_PUT); break;
    case -2:
        putimage((jmario - nci) * wh, imario * wh, MFmario_right_run_2, COPY_PUT); break;
    case -3:
        putimage((jmario - nci) * wh, imario * wh, MFmario_right_run_3, COPY_PUT); break;
    case -6:
        putimage((jmario - nci) * wh, imario * wh, MFmario_jump_1, COPY_PUT); break;
    case 6:
        putimage((jmario - nci) * wh, imario * wh, MFmario_jump_2, COPY_PUT); break;
    }
}

void MarioStagereadMF() {
    switch (stage) {
    case -10:
        readimagefile("MFmario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("MFmario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("MFmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("MFmario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("MFmario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("MFmario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("MFmario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("MFmario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("MFmario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("MFmario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("MFmario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("MFmario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("MFmario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 6:
        readimagefile("MFmario_jump_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void NextState(string direction1) {
    if (direction1 == "right") { 
        if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = -1;
        if (stage > 0) stage = -stage;
        stage--;
        if (stage == -4) stage = -1;
		putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
        jmario += 0.5;
        if (jmario - (int)jmario != 0) {
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario +1] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci+1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario+1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci+1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
            }

            if (harta[(int)imario + 1][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, ((int)imario +1) * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario + 1][(int)jmario + 1] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario + 1][(int)jmario + 1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
            }
            if (harta[(int)imario + 1][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
            }
            
            
        }
        else {
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario -1] == 3) {
                hoverm = 1;
                putimage(((int)jmario -1 - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (jmario == flagpole) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * 6 * wh, flagpolep, COPY_PUT);
            }
            if (jmario-1 == flagpole) {
                hoverm = 1;
                putimage(((int)jmario -1- nci) * wh, (int)imario * 6 * wh, flagpolep, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario - 1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - 1 - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
            }
			if (harta[(int)imario + 1][(int)jmario] == 3) {
				hoverm = 1;
				putimage(((int)jmario - nci) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
			}
            if (harta[(int)imario + 1][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
            }
            if (harta[(int)imario + 1][(int)jmario - 1] == 3) {
                hoverm = 1;
                putimage(((int)jmario - 1 - nci) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario + 1][(int)jmario - 1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - 1 - nci) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
            }
        }
        if (hoverm == 1) {
            //jmario += 0.5;
            if (imario - (int)imario != 0 && !(harta[(int)imario + 1][(int)jmario +1] == 0 && harta[(int)imario][(int)jmario +1] != 0)) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 12 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 13 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 14 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 8 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 10 && (jmario - (int)jmario != 0)))) {
                    jmario -= 0.5;
                    stage = -7;
					ma_sound_stop(&ColideEffect);
					ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
					ma_sound_start(&ColideEffect);
                    if (power != 0 && fpow != 0) {
                        MarioStagereadMF();
                    }
                    else {
                        if (power != 0)
                            MarioStagereadM();
                        else {
                            if (fpow != 0)
                                MarioStagereadF();
                            else {
                                MarioStageread();
                            }
                        }
                    }
                    
                }
                else {
                    if (power != 0 && fpow != 0) {
                        MarioStagereadMF();
                    }
                    else {
                        if (power != 0)
                            MarioStagereadM();
                        else {
                            if (fpow != 0)
                                MarioStagereadF();
                            else {
                                MarioStageread();
                            }
                        }
                    }
                }
            }
            else {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 12 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 13 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 14 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 8 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 10 && (jmario - (int)jmario != 0)))) {
                    jmario -= 0.5;
                    stage = -7;
                    ma_sound_stop(&ColideEffect);
                    ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                    ma_sound_start(&ColideEffect);
                    if (power != 0 && fpow != 0) {
                        MarioStagereadMF();
                    }
                    else {
                        if (power != 0)
                            MarioStagereadM();
                        else {
                            if (fpow != 0)
                                MarioStagereadF();
                            else {
                                MarioStageread();
                            }
                        }
                    }
                }
                else {
                    if (power != 0 && fpow != 0) {
                        MarioStagereadMF();
                    }
                    else {
                        if (power != 0)
                            MarioStagereadM();
                        else {
                            if (fpow != 0)
                                MarioStagereadF();
                            else {
                                MarioStageread();
                            }
                        }
                    }
                }
            }
        }
        else {
            //jmario += 0.5;
            if (imario - (int)imario != 0 && !(harta[(int)imario + 1][(int)jmario + 1] == 0 && harta[(int)imario][(int)jmario + 1] != 0)) {
                if ((CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf)
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 12 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 13 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 8 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 14 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 10 && (jmario - (int)jmario != 0)))) {
                    jmario -= 0.5;
                    stage = -7;
                    ma_sound_stop(&ColideEffect);
                    ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                    ma_sound_start(&ColideEffect);
                    if (power != 0 && fpow != 0) {
                        MarioStageputMF();
                    }
                    else {
                        if (power != 0)
                            MarioStageputM();
                        else {
                            if (fpow != 0)
                                MarioStageputF();
                            else {
                                MarioStageput();
                            }
                        }
                    }
                }
                else {
                    if (power != 0 && fpow != 0) {
                        MarioStageputMF();
                    }
                    else {
                        if (power != 0)
                            MarioStageputM();
                        else {
                            if (fpow != 0)
                                MarioStageputF();
                            else {
                                MarioStageput();
                            }
                        }
                    }
                }
            }
            else {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 12 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 13 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 8 && (jmario - (int)jmario != 0)))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 14 && (jmario - (int)jmario != 0)))
                || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 10 && (jmario - (int)jmario != 0)))) {
                    jmario -= 0.5;
                    stage = -7;
                    ma_sound_stop(&ColideEffect);
                    ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                    ma_sound_start(&ColideEffect);
                    if (power != 0 && fpow != 0) {
                        MarioStageputMF();
                    }
                    else {
                        if (power != 0)
                            MarioStageputM();
                        else {
                            if (fpow != 0)
                                MarioStageputF();
                            else {
                                MarioStageput();
                            }
                        }
                    }
                }
                else {
                    if (power != 0 && fpow != 0) {
                        MarioStageputMF();
                    }
                    else {
                        if (power != 0)
                            MarioStageputM();
                        else {
                            if (fpow != 0)
                                MarioStageputF();
                            else {
                                MarioStageput();
                            }
                        }
                    }
                }
            }
        }
        hoverm = 0;
    }
    else
        if (direction1 == "left") {
            hoverm = 0;
            if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = 1;
            if (stage < 0) stage = -stage;
            stage++;
            if (stage == 4) stage = 1;
			putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
            jmario -= 0.5;
                if (harta[(int)imario][(int)jmario] == 3) {
                    hoverm = 1;
					putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine, COPY_PUT);
                }
                if (harta[(int)imario][(int)jmario + 1] == 3) {
					hoverm = 1;
                    putimage(((int)jmario - nci + 1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                }
                if (harta[(int)imario][(int)jmario] == 4) {
                    hoverm = 1;
                    putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                }
                if (harta[(int)imario][(int)jmario +1] == 4) {
                    hoverm = 1;
                    putimage(((int)jmario - nci +1) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                }
                if (harta[(int)imario + 1][(int)jmario + 1] == 3) {
                    hoverm = 1;
                    putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
                }
                if (harta[(int)imario + 1][(int)jmario + 1] == 4) {
                    hoverm = 1;
                    putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
                }
            if (hoverm == 1) {
                if (imario - (int)imario != 0 && !(harta[(int)imario + 1][(int)jmario] == 0 && harta[(int)imario][(int)jmario] != 0)) {
                    if ((CheckBlock(imario * wh, jmario * wh, wh, (float)(imario) * wh, (float)(jmario)*wh) && (harta[(int)imario +1 ][(int)jmario] == 1)) || (jmario < 0)
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 12))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && harta[(int)imario + 1][(int)jmario] == 13)
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && harta[(int)imario + 1][(int)jmario] == 14)
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 8))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && harta[(int)imario + 1][(int)jmario] == 10)) {
                        jmario += 0.5;
                        stage = 7;
                        ma_sound_stop(&ColideEffect);
                        ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                        ma_sound_start(&ColideEffect);
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                    }
                    else {
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                    }
                }
                else {
                    if ((CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 1 || jmario < 0))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 12))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 13))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 14))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 8))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 10))) {
                        jmario += 0.5;
                        stage = 7;
                        ma_sound_stop(&ColideEffect);
                        ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                        ma_sound_start(&ColideEffect);
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                    }
                    else {
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                    }
                }
            }
            else {
                //jmario -= 0.5;
                if (imario - (int)imario != 0 && !(harta[(int)imario + 1][(int)jmario] == 0 && harta[(int)imario][(int)jmario] != 0)) {
                    if ((CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 1 || jmario < 0))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 12))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 14))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && harta[(int)imario + 1][(int)jmario] == 13)
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 8))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && harta[(int)imario + 1][(int)jmario] == 10)) {
                        jmario += 0.5;
                        stage = 7;
                        ma_sound_stop(&ColideEffect);
                        ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                        ma_sound_start(&ColideEffect);
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                    }
                    else {
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                    }
                }
                else {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 1 || jmario < 0)
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 12))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 13))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 14))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 8))
                    || (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 10))) {
                        jmario += 0.5;
                        stage = 7;
                        ma_sound_stop(&ColideEffect);
                        ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                        ma_sound_start(&ColideEffect);
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                    }
                    else {
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                    }
                }
            }
        }
    
    if (direction1 == "up")
    {
        if (abs(stage) == 10) stage = -stage;
        else stage = 10;
        if (harta[(int)imario][(int)jmario] == 3) {
            putimage(((int)jmario - nci)* wh, (int)imario* wh, skyblock, COPY_PUT);
			putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine, COPY_PUT);
        }
        else {
            putimage(((int)jmario - nci)* wh, (int)imario* wh, skyblock, COPY_PUT);
            putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine_top, COPY_PUT);
        }
        if (harta[(int)imario + 1][(int)jmario] == 3) {
			putimage(((int)jmario - nci)* wh, ((int)imario + 1)* wh, skyblock, COPY_PUT);
			putimage(((int)jmario - nci)* wh, ((int)imario + 1)* wh, mario_vine, COPY_PUT);
        }
        imario -= 0.5;
        if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !((harta[(int)imario][(int)jmario] == 3) || harta[(int)imario][(int)jmario] == 4) && (jmario - (int)jmario == 0)) {
            imario += 0.5;
            stage = 10;
            if (power != 0 && fpow != 0) {
                MarioStagereadMF();
            }
            else {
                if (power != 0)
                    MarioStagereadM();
                else {
                    if (fpow != 0)
                        MarioStagereadF();
                    else {
                        MarioStageread();
                    }
                }
            }
        }
        else
            if (power != 0 && fpow != 0) {
                MarioStagereadMF();
            }
            else {
                if (power != 0)
                    MarioStagereadM();
                else {
                    if (fpow != 0)
                        MarioStagereadF();
                    else {
                        MarioStageread();
                    }
                }
            }
    }

    if (direction1 == "down")
    {
        if (abs(stage) == 9) stage = -stage;
        else stage = -9;
        if (harta[(int)imario][(int)jmario] == 3) {
			putimage(((int)jmario - nci)* wh, (int)imario* wh, skyblock, COPY_PUT);
			putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine, COPY_PUT);
        }
        else {
			putimage(((int)jmario - nci)* wh, (int)imario* wh, skyblock, COPY_PUT);
			putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine_top, COPY_PUT);
        }
        if (harta[(int)imario + 1][(int)jmario] == 3) {
			putimage(((int)jmario - nci)* wh, ((int)imario + 1)* wh, skyblock, COPY_PUT);
			putimage(((int)jmario - nci)* wh, ((int)imario + 1)* wh, mario_vine, COPY_PUT);
        }
        imario += 0.5;
        if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !(harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4) && 
            (harta[(int)imario][(int)jmario] == 1)) {
            imario -= 0.5;
            stage = 9;
            if (power != 0 && fpow != 0) {
                MarioStagereadMF();
            }
            else {
                if (power != 0)
                    MarioStagereadM();
                else {
                    if (fpow != 0)
                        MarioStagereadF();
                    else {
                        MarioStageread();
                    }
                }
            }
        }
        else
            if (power != 0 && fpow != 0) {
                MarioStagereadMF();
            }
            else {
                if (power != 0)
                    MarioStagereadM();
                else {
                    if (fpow != 0)
                        MarioStagereadF();
                    else {
                        MarioStageread();
                    }
                }
            }
    }

    if (direction1 == "space" || ok>0) {
        if(direct == "right") stage = -6;
		else stage = 6;
        if (ok > 0) {
			putimage((jmario - nci)* wh, imario* wh, skyblock, COPY_PUT);
            imario -= 0.5;
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
            }
            if (harta[(int)imario+1][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, ((int)imario+1) * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario+1][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, ((int)imario+1) * wh, mario_vine_top, COPY_PUT);
            }
            if (hoverm == 1) {
                if (jmario - (int)jmario != 0) {
                    if ((imario > 0 && ((harta[(int)imario][(int)jmario] != 1 && (harta[(int)imario][(int)jmario + 1] != 1)) && (harta[(int)imario][(int)jmario] != 8 && (harta[(int)imario][(int)jmario + 1] != 8) && (harta[(int)imario][(int)jmario] != 10 && (harta[(int)imario][(int)jmario + 1] != 10)))))
                        && (harta[(int)imario][(int)jmario] != 12 && (harta[(int)imario][(int)jmario + 1] != 12)) && (harta[(int)imario][(int)jmario] != 14 && (harta[(int)imario][(int)jmario + 1] != 14))
                        && (harta[(int)imario][(int)jmario] != 13 && (harta[(int)imario][(int)jmario + 1] != 13))) {
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                        ok--;
                    }
                    else {
                        imario += 0.5;
                        ok = 0;
                    }
                }
                else {
                    if (CheckBlock(imario, jmario, wh, (float)(imario - 1), (float)(jmario)) && (imario > 0 && (harta[(int)imario][(int)jmario] != 1)
                        && (harta[(int)imario][(int)jmario] != 12) && (harta[(int)imario][(int)jmario] != 8) && (harta[(int)imario][(int)jmario] != 10)
                        && (harta[(int)imario][(int)jmario] != 13) && (harta[(int)imario][(int)jmario] != 14))) {
                        if (power != 0 && fpow != 0) {
                            MarioStagereadMF();
                        }
                        else {
                            if (power != 0)
                                MarioStagereadM();
                            else {
                                if (fpow != 0)
                                    MarioStagereadF();
                                else {
                                    MarioStageread();
                                }
                            }
                        }
                        ok--;
                    }
                    else {
                        if (harta[(int)imario][(int)jmario] == 8 && harta[(int)imario - 1][(int)jmario]==0) {
                            putimage(((int)jmario - nci) * wh, ((int)imario) * wh, lucky_block_used, COPY_PUT);
                            int ranblock = randnumb(0, 3);
                            if (ranblock == 1) {
                                lifo++;
                                life[lifo].icolec = (int)imario - 1;
                                life[lifo].jcolec = (int)jmario;
                                life[lifo].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, one_up, COPY_PUT);
                            }
                            else {
                                if (ranblock == 0)
                                {
                                    coino++;
                                    coins[coino].icolec = (int)imario - 1;
                                    coins[coino].jcolec = (int)jmario;
                                    coins[coino].mapart = (int)(nci - nc1);
                                    putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, mario_coin, COPY_PUT);
                                }
                                else {
                                    if (ranblock == 3) {
                                        staro++;
                                        starpow[staro].icolec = (int)imario - 1;
                                        starpow[staro].jcolec = (int)jmario;
                                        starpow[staro].mapart = (int)(nci - nc1);
                                        putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, mario_star, COPY_PUT);
                                    }
                                    else {
                                        ma_sound_stop(&PowerUpAppearEffect);
                                        ma_sound_seek_to_pcm_frame(&PowerUpAppearEffect, 0);
                                        ma_sound_start(&PowerUpAppearEffect);
                                        firo++;
                                        fflower[firo].icolec = (int)imario - 1;
                                        fflower[firo].jcolec = (int)jmario;
                                        fflower[firo].mapart = (int)(nci - nc1);
                                        putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, fire_flower, COPY_PUT);
                                    }
                                }
                            }
                            harta[(int)imario][(int)jmario] = 10;
                        }
                        imario += 0.5;
                        ok = 0;
                    }
                }
            }
            else {
                if (jmario - (int)jmario != 0) {
                    if ((imario > 0 && ((harta[(int)imario][(int)jmario] != 1 && (harta[(int)imario][(int)jmario + 1] != 1)) && (harta[(int)imario][(int)jmario] != 8 && (harta[(int)imario][(int)jmario + 1] != 8) 
                        && (harta[(int)imario][(int)jmario] != 10 && (harta[(int)imario][(int)jmario + 1] != 10)))))
                        && (harta[(int)imario][(int)jmario] != 12 && (harta[(int)imario][(int)jmario + 1] != 12)) && (harta[(int)imario][(int)jmario] != 14 && (harta[(int)imario][(int)jmario + 1] != 14))
                        && (harta[(int)imario][(int)jmario] != 13 && (harta[(int)imario][(int)jmario + 1] != 13))) {
                        
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                        ok--;
                    }
                    else {
                        imario += 0.5;
                        ok = 0;
                    }
                }
                else {
                    if (CheckBlock(imario, jmario, wh, (float)(imario - 1), (float)(jmario)) && (imario > 0 && (harta[(int)imario][(int)jmario] != 1) 
                    && (harta[(int)imario][(int)jmario] != 12) && (harta[(int)imario][(int)jmario] != 8) && (harta[(int)imario][(int)jmario] != 10)
                    && (harta[(int)imario][(int)jmario] != 13) && (harta[(int)imario][(int)jmario] != 14))) {
                        if (power != 0 && fpow != 0) {
                            MarioStageputMF();
                        }
                        else {
                            if (power != 0)
                                MarioStageputM();
                            else {
                                if (fpow != 0)
                                    MarioStageputF();
                                else {
                                    MarioStageput();
                                }
                            }
                        }
                        ok--;
                    }
                    else {
                        if (harta[(int)imario][(int)jmario] == 8 && harta[(int)imario - 1][(int)jmario] == 0) {
                            putimage(((int)jmario - nci) * wh, ((int)imario) * wh, lucky_block_used, COPY_PUT);
                            int ranblock = randnumb(0, 3);
                            if (ranblock == 1) {
                                lifo++;
                                life[lifo].icolec = (int)imario-1;
                                life[lifo].jcolec = (int)jmario;
                                life[lifo].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, one_up, COPY_PUT);
                            }
                            else {
                                if (ranblock == 0)
                                {
                                    coino++;
                                    coins[coino].icolec = (int)imario-1;
                                    coins[coino].jcolec = (int)jmario;
                                    coins[coino].mapart = (int)(nci - nc1);
                                    putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, mario_coin, COPY_PUT);
                                }
                                else {
                                    if (ranblock == 3) {
                                        staro++;
                                        starpow[staro].icolec = (int)imario - 1;
                                        starpow[staro].jcolec = (int)jmario;
                                        starpow[staro].mapart = (int)(nci - nc1);
                                        putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, mario_star, COPY_PUT);
                                    }
                                    else {
                                        ma_sound_stop(&PowerUpAppearEffect);
                                        ma_sound_seek_to_pcm_frame(&PowerUpAppearEffect, 0);
                                        ma_sound_start(&PowerUpAppearEffect);
                                        firo++;
                                        fflower[firo].icolec = (int)imario - 1;
                                        fflower[firo].jcolec = (int)jmario;
                                        fflower[firo].mapart = (int)(nci - nc1);
                                        putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, fire_flower, COPY_PUT);
                                    }
                                }
                            }
                            harta[(int)imario][(int)jmario] = 10;
                        }
                        imario += 0.5;
                        ok = 0;
                    }
                }
            }
            
        }
        hoverm = 0;
    }

}

void MarioMovement() {
    if (harta[(int)imario + 1][(int)jmario] == 1) {
        safeimario = imario;
        safejmario = jmario;
    }
    int vine = 0;
    mover = 0;

     if (((GetKeyState(VK_SPACE) < 0))) {
        if ((((int)jmario - jmario != 0 && (harta[(int)imario + 1][(int)jmario] == 1 || harta[(int)imario + 1][(int)jmario + 1] == 1)
            || (harta[(int)imario + 1][(int)jmario] == 12 || harta[(int)imario + 1][(int)jmario + 1] == 12) || (harta[(int)imario + 1][(int)jmario] == 13 || harta[(int)imario + 1][(int)jmario + 1] == 13)
            || (harta[(int)imario + 1][(int)jmario] == 14 || harta[(int)imario + 1][(int)jmario + 1] == 14) || (harta[(int)imario + 1][(int)jmario] == 8 || harta[(int)imario + 1][(int)jmario + 1] == 8)
            || (harta[(int)imario + 1][(int)jmario] == 10 || harta[(int)imario + 1][(int)jmario + 1] == 10)) && (harta[(int)imario - 1][(int)jmario] != 1 && harta[(int)imario - 1][(int)jmario + 1] != 1))
            || (((int)jmario - jmario == 0) && (harta[(int)imario + 1][(int)jmario] == 1 || harta[(int)imario + 1][(int)jmario] == 8 || harta[(int)imario + 1][(int)jmario] == 10
                || harta[(int)imario + 1][(int)jmario] == 14 || harta[(int)imario + 1][(int)jmario] == 13 || harta[(int)imario + 1][(int)jmario] == 12)
                && harta[(int)imario - 1][(int)jmario] != 1)) {
            ma_sound_stop(&JumpEffect);
            ma_sound_seek_to_pcm_frame(&JumpEffect, 0);
            ma_sound_start(&JumpEffect);
            ok = 8;
            NextState("space");
            mover = 1;
            okmov = 0;
            //direct = "space";
            //k = 1;
        }
        else {
            if (ok == 0 && (((int)jmario - jmario != 0) && ((harta[(int)imario - 1][(int)jmario] == 1 || harta[(int)imario - 1][(int)jmario] == 8 || harta[(int)imario - 1][(int)jmario] == 10
                || harta[(int)imario - 1][(int)jmario] == 12 || harta[(int)imario - 1][(int)jmario] == 13 || harta[(int)imario - 1][(int)jmario] == 14) && (harta[(int)imario - 1][(int)jmario + 1] == 1
                    || harta[(int)imario - 1][(int)jmario + 1] == 8 || harta[(int)imario - 1][(int)jmario + 1] == 10 || harta[(int)imario - 1][(int)jmario + 1] == 12 || harta[(int)imario - 1][(int)jmario + 1] == 13 || harta[(int)imario - 1][(int)jmario + 1] == 14)))
                || (((int)jmario - jmario == 0) && (harta[(int)imario - 1][(int)jmario] == 1 || harta[(int)imario - 1][(int)jmario] == 12 || harta[(int)imario - 1][(int)jmario] == 13 || harta[(int)imario - 1][(int)jmario] == 14
                    || harta[(int)imario - 1][(int)jmario] == 8 || harta[(int)imario - 1][(int)jmario] == 10))) {
                ma_sound_stop(&ColideEffect);
                ma_sound_seek_to_pcm_frame(&ColideEffect, 0);
                ma_sound_start(&ColideEffect);
            }
        }
    }

    if (((GetKeyState(0x41) < 0 || (GetKeyState(VK_LEFT) < 0))) && jmario > 0) {
        NextState("left");
        mover = 1;
        okmov = 0;
        direct = "left";
    }

    if (((GetKeyState(0x44) < 0 || (GetKeyState(VK_RIGHT) < 0))) && jmario < ncf - 1) {
        NextState("right");
        mover = 1;
        okmov = 0;
        direct = "right";
    }

    if (((GetKeyState(0x57) < 0 || (GetKeyState(VK_UP) < 0))) && (harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4) && jmario - (int)jmario == 0) {
        NextState("up");
        mover = 1;
        okmov = 0;
        direct = "up";
    }

    if (((GetKeyState(0x53) < 0 || (GetKeyState(VK_DOWN) < 0))) && (harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4 || harta[(int)imario + 1][(int)jmario] == 3 || harta[(int)imario + 1][(int)jmario] == 4) 
        && !(imario-(int)imario ==0 && harta[(int)imario +1][(int)jmario] == 1) && jmario - (int)jmario == 0) {
        NextState("down");
        mover = 1;
        okmov = 0;
        direct = "down";
    }

    if (ok > 0) {
        NextState("space");
        mover = 1;
        okmov = 0;
    }

    if (fpow != 0 && (GetAsyncKeyState(0x43) < 0) && shoot > 8 && (int)imario - imario == 0) {
        shoot = 0;
        int put = 0;
        int okput = 1;
        if ((int)jmario - jmario == 0 && (harta[(int)imario][(int)jmario + 1] == 1 || harta[(int)imario][(int)jmario - 1] == 1 
            || harta[(int)imario][(int)jmario + 1] == 12 || harta[(int)imario][(int)jmario - 1] == 12 ||
            harta[(int)imario][(int)jmario + 1] == 13 || harta[(int)imario][(int)jmario - 1] == 13 || 
            harta[(int)imario][(int)jmario + 1] == 14 || harta[(int)imario][(int)jmario - 1] == 14 || 
            harta[(int)imario][(int)jmario + 1] == 8 || harta[(int)imario][(int)jmario - 1] == 8 || 
            harta[(int)imario][(int)jmario + 1] == 10 || harta[(int)imario][(int)jmario - 1] == 10)) okput = 0;
        if ((int)jmario - jmario != 0 && (harta[(int)imario][(int)jmario] == 1 || harta[(int)imario][(int)jmario + 1] == 1 || harta[(int)imario][(int)jmario - 1] == 1 ||
            (harta[(int)imario][(int)jmario] == 12 || harta[(int)imario][(int)jmario + 1] == 12 || harta[(int)imario][(int)jmario - 1] == 12) ||
            (harta[(int)imario][(int)jmario] == 13 || harta[(int)imario][(int)jmario + 1] == 13 || harta[(int)imario][(int)jmario - 1] == 13) ||
            (harta[(int)imario][(int)jmario] == 14 || harta[(int)imario][(int)jmario + 1] == 14 || harta[(int)imario][(int)jmario - 1] == 14) ||
            (harta[(int)imario][(int)jmario] == 8 || harta[(int)imario][(int)jmario + 1] == 8 || harta[(int)imario][(int)jmario - 1] == 8) ||
            (harta[(int)imario][(int)jmario] == 10 || harta[(int)imario][(int)jmario + 1] == 10 || harta[(int)imario][(int)jmario - 1] == 10))) okput = 0;
        if (okput == 1) {
            for (int i = 0;i < 8;i++) {
                if (fireb[i].exist == 0) {
                    fireb[i].exist = 1;
                    if (direct == "right" || direct == "up") {
                        fireb[i].fbdirection = 0;
                        fireb[i].ifireb = imario;
                        fireb[i].jfireb = jmario + 1;
                    }
                    else {
                        if (direct == "left" || direct == "dowm") {
                            fireb[i].fbdirection = 1;
                            fireb[i].ifireb = imario;
                            fireb[i].jfireb = jmario - 1;
                        }
                    }
                    fireb[i].mapart = (int)(nci - nc1);
                    put = 1;
                }
                if (put == 0) {
                    fireb[7].exist = 1;
                    if (direct == "right" || direct == "up") {
                        fireb[7].fbdirection = 0;
                        fireb[7].ifireb = imario;
                        fireb[7].jfireb = jmario + 1;
                    }
                    else {
                        if (direct == "left" || direct == "dowm") {
                            fireb[7].fbdirection = 1;
                            fireb[7].ifireb = imario;
                            fireb[7].jfireb = jmario - 1;

                        }
                    }
                    ma_sound_stop(&FireBallEffect);
                    ma_sound_seek_to_pcm_frame(&FireBallEffect, 0);
                    ma_sound_start(&FireBallEffect);
                    fireb[7].mapart = (int)(nci - nc1);
                }
            }
                
        }
    }

    if ((int)jmario - jmario != 0) {
        if (harta[(int)imario + 1][(int)jmario] == 0 && harta[(int)imario + 1][(int)jmario + 1] == 0 && ok == 0) {
            mover = 1;
            okmov = 0;
            if (harta[(int)imario + 1][(int)jmario] == 0) {
				putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                imario += 0.5;
                if (direct == "right") {
                    if (power != 0 && fpow != 0) {
						putimage((jmario - nci) * wh, (imario)*wh, MFmario_jump_1, COPY_PUT);
                    }
                    else {
                        if (power != 0) {
                            putimage((jmario - nci) * wh, (imario)*wh, Mmario_jump_1, COPY_PUT);
                        }
                        else {
                            if (fpow != 0) {
								putimage((jmario - nci) * wh, (imario)*wh, Fmario_jump_1, COPY_PUT);
                            }
                            else {
                                putimage((jmario - nci) * wh, (imario)*wh, mario_jump_1, COPY_PUT);
                            }
                        }
                    }
                }
                else {
                    if (power != 0 && fpow != 0) {
                        putimage((jmario - nci) * wh, (imario)*wh, MFmario_jump_2, COPY_PUT);
                    }
                    else {
                        if (power != 0) {
                            putimage((jmario - nci) * wh, (imario)*wh, Mmario_jump_2, COPY_PUT);
                        }
                        else {
                            if (fpow != 0) {
                                putimage((jmario - nci) * wh, (imario)*wh, Fmario_jump_2, COPY_PUT);
                            }
                            else {
                                putimage((jmario - nci) * wh, (imario)*wh, mario_jump_2, COPY_PUT);
                            }
                        }
                    }
                }
            }
            if (imario > nl) {
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                if (power != 0 && fpow != 0) {
					putimage((safejmario - nci) * wh, (safeimario)*wh, MFmario_idle_left, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((safejmario - nci) * wh, (safeimario)*wh, Mmario_idle_left, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
							putimage((safejmario - nci)* wh, (safeimario)*wh, Fmario_idle_left, COPY_PUT);
                        }
                        else {
                            putimage((safejmario - nci)* wh, (safeimario)*wh, mario_idle_left, COPY_PUT);
                        }
                    }
                }
                lifes--;
                imario = safeimario;
                jmario = safejmario;
            }
        }
    }
    else {
        if (harta[(int)imario + 1][(int)jmario] == 0 && ok == 0) {
            mover = 1;
            okmov = 0;
            if (harta[(int)imario + 1][(int)jmario] == 0) {
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                imario += 0.5;
                if (direct == "right") {
                    if (power != 0 && fpow != 0) {
						putimage((jmario - nci)* wh, (imario)*wh, MFmario_jump_1, COPY_PUT);
                    }
                    else {
                        if (power != 0) {
                            putimage((jmario - nci) * wh, (imario)*wh, Mmario_jump_1, COPY_PUT);
                        }
                        else {
                            if (fpow != 0) {
								putimage((jmario - nci) * wh, (imario)*wh, Fmario_jump_1, COPY_PUT);
                            }
                            else {
                                putimage((jmario - nci) * wh, (imario)*wh, mario_jump_1, COPY_PUT);
                            }
                        }
                    }
                }
                else {
                    if (power != 0 && fpow != 0) {
						putimage((jmario - nci)* wh, (imario)*wh, MFmario_jump_2, COPY_PUT);
                    }
                    else {
                        if (power != 0) {
                            putimage((jmario - nci) * wh, (imario)*wh, Mmario_jump_2, COPY_PUT);
                        }
                        else {
                            if (fpow != 0) {
								putimage((jmario - nci)* wh, (imario)*wh, Fmario_jump_2, COPY_PUT);
                            }
                            else {
                                putimage((jmario - nci) * wh, (imario)*wh, mario_jump_2, COPY_PUT);
                            }
                        }
                    }
                }
            }
            if (imario > nl) {
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                if (power != 0 && fpow != 0) {
                    putimage((safejmario - nci) * wh, (safeimario)*wh, MFmario_idle_left, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((safejmario - nci) * wh, (safeimario)*wh, Mmario_idle_left, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
                            putimage((safejmario - nci) * wh, (safeimario)*wh, Fmario_idle_left, COPY_PUT);
                        }
                        else {
                            putimage((safejmario - nci) * wh, (safeimario)*wh, mario_idle_left, COPY_PUT);
                        }
                    }
                }
                lifes--;
                imario = safeimario;
                jmario = safejmario;
            }
        }
    }


    for (int i = 1;i <= staro;i++) { //checker pentru coliziuni cu star power
        if (starpow[i].mapart == (int)(nci - nc1)) {
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(starpow[i].icolec) * wh, (float)(starpow[i].jcolec) * wh) == 1 && direct == "right" && starpow[i].colected == 0) {
                power += 80;
                starpow[i].colected = 1;
                putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }

            }
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(starpow[i].icolec) * wh, (float)(starpow[i].jcolec) * wh) == 1 && direct == "left" && starpow[i].colected == 0) {
                power += 80;
                starpow[i].colected = 1;
                putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
            }
        }
    }

    for (int i = 1;i <= n;i++) { //checker pentru coliziuni cu goomba
        if (power == 0) {
            if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
                if (gompav[i].hit == 0) {
                    gompav[i].hit = 3;
                }
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "right") {
                    if (imario < gompav[i].igompa) {
                        gompav[i].dead = 1;
                        gdead++;
                        ok += 4;

                        ma_sound_stop(&GombaDeadEffect);
                        ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
                        ma_sound_start(&GombaDeadEffect);
                        putimage((gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, skyblock, COPY_PUT);
                        readimagefile("goomba_walking_1.gif", (gompav[i].jgompa - nci) * wh, (gompav[i].igompa + 0.5) * wh, (gompav[i].jgompa - nci + 1) * wh, (gompav[i].igompa + 1) * wh);
                        delay(40);
                        putimage((gompav[i].jgompa - nci) * wh, (gompav[i].igompa) * wh, skyblock, COPY_PUT);
                    }
                    else {
						ma_sound_stop(&DmgEffect);
						ma_sound_seek_to_pcm_frame(&DmgEffect, 0);
						ma_sound_start(&DmgEffect);
                        for (int i = 0;i < 3;i++) {
                            putimage((jmario - nci)* wh, imario* wh, skyblock, COPY_PUT);
                            if ((int)imario - imario == 0 && (harta[(int)imario - 1][(int)jmario] == 1 || harta[(int)imario - 1][(int)jmario] == 10 ||
                                harta[(int)imario - 1][(int)jmario] == 8 || harta[(int)imario - 1][(int)jmario] == 12 || harta[(int)imario - 1][(int)jmario] == 13
                                || harta[(int)imario - 1][(int)jmario] == 14)) {
                            }
                            else {
                                imario -= 0.5;
                            }
                            NextState("left");
                            
                        }
                        if (invincibilityframes == 0) {
							if (fpow != 0) fpow = 0;
                            lifes--;
                            invincibilityframes = 10;
                        }
                    }

                }
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "left") {
                    if (imario < gompav[i].igompa) {
                        gompav[i].dead = 1;
                        gdead++;
                        ok += 4;
                        ma_sound_stop(&GombaDeadEffect);
                        ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
                        ma_sound_start(&GombaDeadEffect);
                        putimage((gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, skyblock, COPY_PUT);
                        readimagefile("goomba_walking_1.gif", (gompav[i].jgompa - nci) * wh, (gompav[i].igompa + 0.5) * wh, (gompav[i].jgompa - nci + 1) * wh, (gompav[i].igompa + 1) * wh);
                        delay(40);
                        putimage((gompav[i].jgompa - nci) * wh, (gompav[i].igompa) * wh, skyblock, COPY_PUT);
                    }
                    else {
                        ma_sound_stop(&DmgEffect);
                        ma_sound_seek_to_pcm_frame(&DmgEffect, 0);
                        ma_sound_start(&DmgEffect);
                        for (int i = 0;i < 3;i++) {
							putimage((jmario - nci)* wh, imario* wh, skyblock, COPY_PUT);
                            if((int)imario-imario == 0 && (harta[(int)imario - 1][(int)jmario] == 1 || harta[(int)imario - 1][(int)jmario] == 10 ||
                            harta[(int)imario - 1][(int)jmario] == 8 || harta[(int)imario - 1][(int)jmario] == 12 || harta[(int)imario - 1][(int)jmario] == 13
                                || harta[(int)imario - 1][(int)jmario] == 14)){ }
                            else {
                                imario -= 0.5;
                            }
                            NextState("right");
                            
                        }
                        if (invincibilityframes == 0) {
                            if (fpow != 0) fpow = 0;
                            lifes--;
                            invincibilityframes = 10;
                        }
                    }
                }
            }
        }
        else {
            if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "left") {
                    gompav[i].dead = 1;
                    gdead++;
                    ma_sound_stop(&GombaDeadEffect);
                    ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
                    ma_sound_start(&GombaDeadEffect);
                    putimage((gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, skyblock, COPY_PUT);
                    
                }
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "right") {
                    gompav[i].dead = 1;
                    gdead++;
                    ma_sound_stop(&GombaDeadEffect);
                    ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
                    ma_sound_start(&GombaDeadEffect);
                    putimage((gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, skyblock, COPY_PUT);
                    
                }
            }
        }
    }

    for (int i = 1;i <= p;i++) { //checker pentru coliziuni cu pirana
        if (power == 0) {
            if (piranav[i].mapart == (int)(nci - nc1) && piranav[i].dead == 0 && piranav[i].ipinit!=piranav[i].ipirana /*piranav[i].upframes != 0 && piranav[i].reset*/) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(piranav[i].ipirana) * wh, (float)(piranav[i].jpirana) * wh) == 1 && direct == "right" ) {
					ma_sound_stop(&DmgEffect);
					ma_sound_seek_to_pcm_frame(&DmgEffect, 0);
					ma_sound_start(&DmgEffect);
					if (piranav[i].orientation == 1) {
						ok += 5;
					}
                    if (invincibilityframes == 0) {
                        if (fpow != 0) fpow = 0;
                        lifes--;
                        invincibilityframes = 10;
                    }
                }
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(piranav[i].ipirana) * wh, (float)(piranav[i].jpirana) * wh) == 1 && direct == "left") {
                    ma_sound_stop(&DmgEffect);
                    ma_sound_seek_to_pcm_frame(&DmgEffect, 0);
                    ma_sound_start(&DmgEffect);
                    if (piranav[i].orientation == 1) {
                        ok += 5;
                    }
                    if (invincibilityframes == 0) {
                        if (fpow != 0) fpow = 0;
                        lifes--;
                        invincibilityframes = 10;
                    }
                }
            }
        }
        else {
            if (piranav[i].mapart == (int)(nci - nc1) && piranav[i].dead == 0) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)(piranav[i].ipirana) * wh, (float)(piranav[i].jpirana) * wh) == 1 && direct == "right") {
                    piranav[i].dead = 1;
                    pdead++;
                    putimage((piranav[i].jpirana - nci) * wh, piranav[i].ipirana * wh, skyblock, COPY_PUT);
                    if (piranav[p].orientation == -1) {
                        putimage((piranav[i].jpirana - nci) * wh, (piranav[i].ipinit) * wh, Rpipehead, COPY_PUT);
                    }
                    else {
                        putimage((piranav[i].jpinit - nci) * wh, (piranav[i].ipinit) * wh, pipehead, COPY_PUT);
                    }
                }
                else {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)(piranav[i].ipirana) * wh, (float)(piranav[i].jpirana) * wh) == 1 && direct == "right") {
                        piranav[i].dead = 1;
                        pdead++;
                        putimage((piranav[i].jpirana - nci) * wh, piranav[i].ipirana * wh, skyblock, COPY_PUT);
                        if (piranav[p].orientation == -1) {
                            putimage((piranav[i].jpirana - nci) * wh, (piranav[i].ipinit) * wh, Rpipehead, COPY_PUT);
                        }
                        else {
                            putimage((piranav[i].jpinit - nci) * wh, (piranav[i].ipinit) * wh, pipehead, COPY_PUT);
                        }
                    }
                }
            }
        }
    }


    for (int i = 1;i <= coino;i++) { //checker pentru coliziuni cu coins
        if (coins[i].mapart == (int)(nci - nc1) && coins[i].colected == 0) {
            if (CheckColec(imario * wh, (jmario-nci) * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec- nci) * wh) == 1 && direct == "right") {
                coinono++;
                coins[i].colected = 1;
                ma_sound_stop(&CoinEffect);
                ma_sound_seek_to_pcm_frame(&CoinEffect, 0);
                ma_sound_start(&CoinEffect);
				putimage((coins[i].jcolec - nci)* wh, coins[i].icolec* wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
					putimage((jmario - nci)* wh, imario* wh, mario_idle_left, COPY_PUT);
                }
            }
            if (CheckColec(imario * wh, (jmario - nci) * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec - nci) * wh) == 1 && direct == "left") {
                coinono++;
                coins[i].colected = 1;
                ma_sound_stop(&CoinEffect);
                ma_sound_seek_to_pcm_frame(&CoinEffect, 0);
                ma_sound_start(&CoinEffect);
                putimage((coins[i].jcolec - nci)* wh, coins[i].icolec* wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
            }
        }
    }

    for (int i = 1;i <= firo;i++) { //checker pentru coliziuni cu fire flowers
        if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].colected == 0) {
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(fflower[i].icolec) * wh, (float)(fflower[i].jcolec) * wh) == 1 && direct == "right" && fflower[i].colected == 0) {
                fpow += 80;
				ma_sound_stop(&PowerUpEffect);
				ma_sound_seek_to_pcm_frame(&PowerUpEffect, 0);
				ma_sound_start(&PowerUpEffect);
                fflower[i].colected = 1;
                ma_sound_stop(&CoinEffect);
                ma_sound_seek_to_pcm_frame(&CoinEffect, 0);
                ma_sound_start(&CoinEffect);
                putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
                continue;
            }
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(fflower[i].icolec) * wh, (float)(fflower[i].jcolec) * wh) == 1 && direct == "left" && fflower[i].colected == 0) {
                fpow += 80;
                ma_sound_stop(&PowerUpEffect);
                ma_sound_seek_to_pcm_frame(&PowerUpEffect, 0);
                ma_sound_start(&PowerUpEffect);
                fflower[i].colected = 1;
                putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
                continue;
            }
        }
    }

    for (int i = 1;i <= lifo;i++) { //checker pentru coliziuni cu one_ups
        if (life[i].mapart == (int)(nci - nc1)) {
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(life[i].icolec) * wh, (float)(life[i].jcolec) * wh) == 1 && direct == "right" && life[i].colected == 0) {
                lifes++;
                life[i].colected = 1;
                ma_sound_stop(&OneUpEffect);
                ma_sound_seek_to_pcm_frame(&OneUpEffect, 0);
                ma_sound_start(&OneUpEffect);
                putimage((life[i].jcolec - nci)* wh, life[i].icolec* wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
                
            }
            if (CheckColec(imario * wh, jmario * wh, wh, (float)(life[i].icolec) * wh, (float)(life[i].jcolec) * wh) == 1 && direct == "left" && life[i].colected == 0) {
                lifes++;
                life[i].colected = 1;
                ma_sound_stop(&OneUpEffect);
                ma_sound_seek_to_pcm_frame(&OneUpEffect, 0);
                ma_sound_start(&OneUpEffect);
                putimage((life[i].jcolec - nci)* wh, life[i].icolec* wh, skyblock, COPY_PUT);
                if (direct == "right") {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                }
                else {
                    putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                }
            }
        }
    }
    
    if (mover == 0) {
        if (harta[(int)imario][(int)jmario] == 3)
            putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
        if (harta[(int)imario][(int)jmario] == 4)
            putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
        if (harta[(int)imario][(int)jmario + 1] == 3)
            putimage(((int)jmario - nci + 1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
        if (harta[(int)imario][(int)jmario + 1] == 4)
            putimage(((int)jmario - nci + 1) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
        if (harta[(int)imario + 1][(int)jmario] == 3)
            putimage(((int)jmario - nci) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
        if (harta[(int)imario + 1][(int)jmario] == 4)
            putimage(((int)jmario - nci) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
        if (harta[(int)imario + 1][(int)jmario + 1] == 3)
            putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine, COPY_PUT);
        if (harta[(int)imario + 1][(int)jmario + 1] == 4)
            putimage(((int)jmario - nci + 1) * wh, ((int)imario + 1) * wh, mario_vine_top, COPY_PUT);
        if ((harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4) && (int)jmario-jmario == 0) {
            if (direct == "up") {
                if (fpow != 0 && power != 0) {
                    putimage((jmario - nci) * wh, imario * wh, FMmario_vine_idle_up, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((jmario - nci) * wh, imario * wh, Mmario_vine_idle_up, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
                            putimage((jmario - nci) * wh, imario * wh, Fmario_vine_idle_up, COPY_PUT);
                        }
                        else {
                            putimage((jmario - nci) * wh, imario * wh, mario_vine_idle_up, COPY_PUT);
                        }
                    }
                }
            }
            else {
                if (fpow != 0 && power != 0) {
                    putimage((jmario - nci) * wh, imario * wh, FMmario_vine_idle_down, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((jmario - nci) * wh, imario * wh, Mmario_vine_idle_down, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
                            putimage((jmario - nci) * wh, imario * wh, Fmario_vine_idle_down, COPY_PUT);
                        }
                        else {
                            putimage((jmario - nci) * wh, imario * wh, mario_vine_idle_down, COPY_PUT);
                        }
                    }
                }
            }
        }
        else {
            if (direct == "right") {
                if (fpow != 0 && power != 0) {
                    putimage((jmario - nci) * wh, imario * wh, MFmario_idle_right, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((jmario - nci) * wh, imario * wh, Mmario_idle_right, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
                            putimage((jmario - nci) * wh, imario * wh, Fmario_idle_right, COPY_PUT);
                        }
                        else {
                            putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
                        }
                    }
                }
            }
            else {
                if (fpow != 0 && power != 0) {
                    putimage((jmario - nci) * wh, imario * wh, MFmario_idle_left, COPY_PUT);
                }
                else {
                    if (power != 0) {
                        putimage((jmario - nci) * wh, imario * wh, Mmario_idle_left, COPY_PUT);
                    }
                    else {
                        if (fpow != 0) {
                            putimage((jmario - nci) * wh, imario * wh, Fmario_idle_left, COPY_PUT);
                        }
                        else {
                            putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT);
                        }
                    }
                }
            }
        }
    }
   
    if (jmario >= (int)ncf || ((jmario- nci +1)*wh >= x)) {
        MapLoaderNextRight(); //randam urmatoarea parte din harta
    }

    if ((jmario-nci)*wh < 0) {
        MapLoaderPrevLeft(); //randam o parte anterioara a hartii
    }

	if (power != 0) power--;
	//if (fpow != 0) fpow--;
    if(invincibilityframes!=0) invincibilityframes--;
    if (shoot < 20) shoot++;

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, wh/9);
    char CoinsText[10], LifesText[10], LifesText1[10];
    sprintf(CoinsText, "X %d", coinono);
	sprintf(LifesText, "%d X", lifes);
    sprintf(LifesText1, "%d X", lifes + 1);
	putimage(0.4*wh, 0.3*wh, mario_coin, COPY_PUT);
    outtextxy(1.4*wh, 0.5*wh, CoinsText);
    setcolor(RGB(126, 132, 246));
    outtextxy((ncf - nci - 1.6)* wh - textwidth(LifesText), 0.6 * wh, LifesText);
    setcolor(RGB(126, 132, 246));
    outtextxy((ncf - nci - 1.6) * wh - textwidth(LifesText1), 0.6 * wh, LifesText);
    setcolor(WHITE);
    outtextxy((ncf -nci - 1.6) * wh - textwidth(LifesText), 0.6 * wh, LifesText);
	putimage((ncf-nci -1.4) * wh, 0.4 * wh, one_up, COPY_PUT);

    
	if (harta[(int)imario][(int)jmario] == 11 || harta[(int)imario][(int)jmario] == 20) {
		//PlaySound(TEXT("stage_clear.wav"), NULL, SND_FILENAME | SND_ASYNC);
        clock_t end = clock();
        play = 1;
        time_spent = ((double)(end - start) / CLOCKS_PER_SEC) - timespent;
		score1 = 1000 - (int)time_spent * 10 + gdead * 100 + coinono * 100;
        ma_sound_start(&FlagEffect);
		putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
		putimage((flagpolej - nci)* wh, (flagpolei - 6)* wh, flagpolep, COPY_PUT);

        if (fpow != 0 && power != 0) {
			readimagefile("MFmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, (jmario - nci + 1) * wh, (imario + 1) * wh);
        }
        else {
            if (power != 0) {
                readimagefile("Mmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, (jmario - nci + 1) * wh, (imario + 1) * wh);
            }
            else {
                if (fpow != 0) {
                    readimagefile("Fmario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, (jmario - nci + 1) * wh, (imario + 1) * wh);
                }
                else {
                    readimagefile("mario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, (jmario - nci + 1) * wh, (imario + 1) * wh);
                }
            }
        }
        delay(2000);

		LevelCLearMenu();
    }

    if (lifes <= 0) {
        char key = getch();
		ma_sound_stop(&BackGroundMusic);
		ma_sound_seek_to_pcm_frame(&BackGroundMusic, 0);
		if (!ma_sound_is_playing(&DeathEffect)) ma_sound_start(&DeathEffect);
		GameOverMenu();
        
    }
    if (GetKeyState(VK_ESCAPE)<0) {
		//ma_sound_stop(&BackGroundMusic);
        char key = getch();
		initpause = clock();
        PauseMenu();
		clock_t endpause = clock();
		timespent += (double)(endpause - initpause) / CLOCKS_PER_SEC;
        okesc = 1;
    }
}