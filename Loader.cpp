#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <string.h>
#include <random>
#include <windows.h>
#include "Enemies.h"
#include "Map.h"
#include "MapEditor.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Mario.h"


extern int coinono, lifes, ok, gdead, power, pdead, lifo, staro, coino, timespent;
extern firebll fireb[9];
extern colectible coins[100], life[100], starpow[100], fflower[100];
extern goompa gompav[100];
extern pirhana piranav[100];
extern int harta[30][1000], n, p, x, y, firo, fpow, flagpolei, flagpolej;
extern std::string cht;
extern float wh, nci, ncf, nc1;
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * pipehead, * pipebody, * pirana_1, * pirana_2, * pipeheadpir,
* brickblockmap, * skyblockmap, * mario_vinemap, * mario_vine_topmap, * mario_star, * lucky_blockmap, * mario_coinmap, * mario_idle_rightmap, * one_upmap, * flagpolepmap, * flagpolemapedit,
* gombamap, * pipeheadmap, * pipebodymap, * pipeheadpirmap, * brickblockmono, * skyblockmono, * mario_vinemono, * mario_vine_topmono, * lucky_blockmono, * mario_coinmono,
* mario_idle_rightmono, * one_upmono, * flagpolepmono, * gombamono, * pipeheadmono, * pipebodymono, * pipeheadpirmono, * flagpolemapeditmono, * flagpolemapeditp,
* mario_main_screen, * mario_levels_menu, * mario_jump_2, * Rpipeheadpirmono, * Rpipeheadmono, * Rpipeheadpir, * Rpipehead, * Rpipeheadpirmap, * Rpipeheadmap,
* Rpirana_1, * Rpirana_2, * Mmario_climbing_down_1, * Mmario_climbing_down_2, * Mmario_climbing_up_1,
* Mmario_climbing_up_2, * Mmario_idle_left, * Mmario_idle_right, * Mmario_jump_1, * Mmario_left_run_1, * Mmario_left_run_2, * Mmario_left_run_3, * Mmario_right_run_1,
* Mmario_right_run_2, * Mmario_right_run_3, * Mmario_jump_2, * MFmario_climbing_down_1, * MFmario_climbing_down_2, * MFmario_climbing_up_1,
* MFmario_climbing_up_2, * MFmario_idle_left, * MFmario_idle_right, * MFmario_jump_1, * MFmario_left_run_1, * MFmario_left_run_2, * MFmario_left_run_3, * MFmario_right_run_1,
* MFmario_right_run_2, * MFmario_right_run_3, * MFmario_jump_2, * Fmario_climbing_down_1, * Fmario_climbing_down_2, * Fmario_climbing_up_1,
* Fmario_climbing_up_2, * Fmario_idle_left, * Fmario_idle_right, * Fmario_jump_1, * Fmario_left_run_1, * Fmario_left_run_2, * Fmario_left_run_3, * Fmario_right_run_1,
* Fmario_right_run_2, * Fmario_right_run_3, * Fmario_jump_2, * fireball_1, * fireball_2, * fire_flower, * skyblockmap1, * mario_custom_screen, 
* mario_vine_idle_up, * mario_vine_idle_down, * Mmario_vine_idle_up, * Mmario_vine_idle_down, * Fmario_vine_idle_up, * Fmario_vine_idle_down,
* FMmario_vine_idle_up, * FMmario_vine_idle_down;

void preloadImage(const char* filename, int width, int height, void*& buffer) {
    readimagefile(filename, 0, 0, width, height);
    buffer = malloc(imagesize(0, 0, width, height));
    getimage(0, 0, width, height, buffer);
}

void preloadImage2(const char* filename, int width, int height, void*& buffer) {
    readimagefile(filename, 0.30*wh, 0.30*wh, 0.70*width, 0.70*height);
    buffer = malloc(imagesize(0, 0, width, height));
    getimage(0, 0, width, height, buffer);
}

void preloadImage3(const char* filename, int width, int height, void*& buffer) {
    readimagefile(filename, 0, 0, width, height);
    buffer = malloc(imagesize(0, 0, width, height));
	rectangle(0, 0, width, height);
	rectangle(1, 1, width-1, height-1);
	rectangle(2, 2, width - 2, height - 2);
    getimage(0, 0, width, height, buffer);
}

void preloadImage4(const char* filename1, const char* filename2, int width, int height, void*& buffer) {
    readimagefile(filename1, 0, 0, width, height);
	readimagefile(filename2, 0, 0, width, height);
    buffer = malloc(imagesize(0, 0, width, height));
    getimage(0, 0, width, height, buffer);
}

void AssetLoader() {
    initwindow(x, y, "", -3, -3);
    setvisualpage(0);
    setactivepage(1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("BrickBlock.jpg", wh, wh, brickblock);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("SkyBlock.jpg", wh, wh, skyblock);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine.gif", wh, wh, mario_vine);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine_top.gif", wh, wh, mario_vine_top);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_block.jpg", wh, wh, lucky_block);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_coin.gif", wh, wh, mario_coin);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_1.gif", wh, wh, goomba_walking_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_2.gif", wh, wh, goomba_walking_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_down_1.gif", wh, wh, mario_climbing_down_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_down_2.gif", wh, wh, mario_climbing_down_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_up_1.gif", wh, wh, mario_climbing_up_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_up_2.gif", wh, wh, mario_climbing_up_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_left.gif", wh, wh, mario_idle_left);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_right.gif", wh, wh, mario_idle_right);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_jump_1.gif", wh, wh, mario_jump_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_1.gif", wh, wh, mario_left_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_2.gif", wh, wh, mario_left_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_3.gif", wh, wh, mario_left_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_1.gif", wh, wh, mario_right_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_2.gif", wh, wh, mario_right_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_3.gif", wh, wh, mario_right_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_climbing_down_1.gif", wh, wh, Mmario_climbing_down_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_climbing_down_2.gif", wh, wh, Mmario_climbing_down_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_climbing_up_1.gif", wh, wh, Mmario_climbing_up_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_climbing_up_2.gif", wh, wh, Mmario_climbing_up_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_idle_left.gif", wh, wh, Mmario_idle_left);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_idle_right.gif", wh, wh, Mmario_idle_right);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_jump_1.gif", wh, wh, Mmario_jump_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_jump_2.gif", wh, wh, Mmario_jump_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_left_run_1.gif", wh, wh, Mmario_left_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_left_run_2.gif", wh, wh, Mmario_left_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_left_run_3.gif", wh, wh, Mmario_left_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_right_run_1.gif", wh, wh, Mmario_right_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_right_run_2.gif", wh, wh, Mmario_right_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Mmario_right_run_3.gif", wh, wh, Mmario_right_run_3);

    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_climbing_down_1.gif", wh, wh, MFmario_climbing_down_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_climbing_down_2.gif", wh, wh, MFmario_climbing_down_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_climbing_up_1.gif", wh, wh, MFmario_climbing_up_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_climbing_up_2.gif", wh, wh, MFmario_climbing_up_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_idle_left.gif", wh, wh, MFmario_idle_left);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_idle_right.gif", wh, wh, MFmario_idle_right);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_jump_1.gif", wh, wh, MFmario_jump_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_jump_2.gif", wh, wh, MFmario_jump_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_left_run_1.gif", wh, wh, MFmario_left_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_left_run_2.gif", wh, wh, MFmario_left_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_left_run_3.gif", wh, wh, MFmario_left_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_right_run_1.gif", wh, wh, MFmario_right_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_right_run_2.gif", wh, wh, MFmario_right_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MFmario_right_run_3.gif", wh, wh, MFmario_right_run_3);

    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_climbing_down_1.gif", wh, wh, Fmario_climbing_down_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_climbing_down_2.gif", wh, wh, Fmario_climbing_down_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_climbing_up_1.gif", wh, wh, Fmario_climbing_up_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_climbing_up_2.gif", wh, wh, Fmario_climbing_up_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_idle_left.gif", wh, wh, Fmario_idle_left);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_idle_right.gif", wh, wh, Fmario_idle_right);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_jump_1.gif", wh, wh, Fmario_jump_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_jump_2.gif", wh, wh, Fmario_jump_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_left_run_1.gif", wh, wh, Fmario_left_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_left_run_2.gif", wh, wh, Fmario_left_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_left_run_3.gif", wh, wh, Fmario_left_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_right_run_1.gif", wh, wh, Fmario_right_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_right_run_2.gif", wh, wh, Fmario_right_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Fmario_right_run_3.gif", wh, wh, Fmario_right_run_3);

    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_block_used.jpg", wh, wh, lucky_block_used);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("one_up.gif", wh, wh, one_up);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_head.gif", wh, wh, pipehead);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_body.gif", wh, wh, pipebody);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pirana_1.gif", wh, wh, pirana_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pirana_2.gif", wh, wh, pirana_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_head_pirana.gif", wh, wh, pipeheadpir);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Flagpole.gif", wh, 7 * wh, flagpolep);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Flagpolecut.gif", wh, wh, flagpolemapedit);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("BrickBlockMono.jpg", (wh), (wh), brickblockmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("SkyBlockMono.jpg", (wh), (wh), skyblockmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vineMono.gif", (wh), (wh), mario_vinemono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine_topMono.gif", (wh), (wh), mario_vine_topmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_blockMono.jpg", (wh), (wh), lucky_blockmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_coinMono.gif", (wh), (wh), mario_coinmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_rightMono.gif", (wh), (wh), mario_idle_rightmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_1Mono.gif", wh, wh, gombamono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("one_upMono.gif", (wh), (wh), one_upmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_headMono.gif", wh, wh, pipeheadmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_bodyMono.gif", wh, wh, pipebodymono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_head_piranaMono.gif", wh, wh, pipeheadpirmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_headMono.gif", wh, wh, Rpipeheadmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_head_piranaMono.gif", wh, wh, Rpipeheadpirmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_head.gif", wh, wh, Rpipehead);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_head_pirana.gif", wh, wh, Rpipeheadpir);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("FlagpolecutMono.gif", wh, wh, flagpolemapeditmono);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_star.gif", wh, wh, mario_star);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_jump_2.gif", wh, wh, mario_jump_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpirana_1.gif", wh, wh, Rpirana_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpirana_2.gif", wh, wh, Rpirana_2);

    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("fire.gif", wh, wh, fire_flower);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage2("fireball_1.gif", wh, wh, fireball_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage2("fireball_2.gif", wh, wh, fireball_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pxfuel.jpg", x-3, y-3, mario_main_screen);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pxfuel_custom.jpg", x - 3, y - 3, mario_custom_screen);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("MarioLevelsMenu.jpg", x-3, y-3, mario_levels_menu);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "mario_climbing_down_1.gif", wh, wh, mario_vine_idle_down);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "mario_climbing_up_1.gif", wh, wh, mario_vine_idle_up);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "Mmario_climbing_down_1.gif", wh, wh, Mmario_vine_idle_down);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "Mmario_climbing_up_1.gif", wh, wh, Mmario_vine_idle_up);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "Fmario_climbing_down_1.gif", wh, wh, Fmario_vine_idle_down);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "Fmario_climbing_up_1.gif", wh, wh, Fmario_vine_idle_up);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "MFario_climbing_down_1.gif", wh, wh, FMmario_vine_idle_down);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage4("mario_vine.gif", "MFmario_climbing_up_1.gif", wh, wh, FMmario_vine_idle_up);
	closegraph();
}

void AssetLoaderMap() {
    initwindow((0.7 * wh) + 1, 7 * (0.7 * wh) + 1, "", -3, -3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("BrickBlock.jpg", (0.7 * wh), (0.7 * wh), brickblockmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("SkyBlock.jpg", (0.7 * wh), (0.7 * wh), skyblockmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage3("SkyBlock.jpg", (0.7 * wh), (0.7 * wh), skyblockmap1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine.gif", (0.7 * wh), (0.7 * wh), mario_vinemap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine_top.gif", (0.7 * wh), (0.7 * wh), mario_vine_topmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_block.jpg", (0.7 * wh), (0.7 * wh), lucky_blockmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_coin.gif", (0.7 * wh), (0.7 * wh), mario_coinmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_right.gif", (0.7 * wh), (0.7 * wh), mario_idle_rightmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_1.gif", 0.7 * wh, 0.7 * wh, gombamap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("one_up.gif", (0.7 * wh), (0.7 * wh), one_upmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Flagpole.gif", (0.7 * wh), 7 * (0.7 * wh), flagpolepmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_head.gif", 0.7 * wh, 0.7 * wh, pipeheadmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_body.gif", 0.7 * wh, 0.7 * wh, pipebodymap);
        cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Flagpolecut.gif", 0.7 * wh, 0.7 * wh, flagpolemapeditp);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("pipe_head_pirana.gif", 0.7 * wh, 0.7 * wh, pipeheadpirmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_head_pirana.gif", 0.7 * wh, 0.7 * wh, Rpipeheadpirmap);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Rpipe_head.gif", 0.7 * wh, 0.7 * wh, Rpipeheadmap);
    closegraph();
}

int randnumb(int a, int b) {
    // Cream un random number generator
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(a, b);

    int randomInt = dist(gen);  // Generam un numar random
    return randomInt;
}

void MapReseter() {
    memset(harta, 0, sizeof(harta));
    coinono = 0;
    lifes = 3;
    ok = 0;
    gdead = 0;
    power = 0;
    pdead = 0;
    for(int i = 1;i <= n;i++) {
        gompav[i].igompa = 0;
        gompav[i].jgompa = 0;
        gompav[i].gdirection = 1;
        gompav[i].gstage = 1;
        gompav[i].dead = 0;
        gompav[i].hit = 0;
        gompav[i].mapart=0;
    }
    n = 0;
	for (int i = 1;i <= p;i++) {
		piranav[i].ipinit = 0;
		piranav[i].jpinit = 0;
		piranav[i].ipirana = 0;
		piranav[i].jpirana = 0;
		piranav[i].pdirection = 1;
		piranav[i].pstage = 1;
		piranav[i].upframes = 0;
		piranav[i].orientation = 1;
		piranav[i].reset = 0;
		piranav[i].dead = 0;
		piranav[i].mapart = 0;
	}
    p = 0;
	for (int i = 1;i <= coino;i++) {
		coins[i].icolec = 0;
		coins[i].jcolec = 0;
		coins[i].mapart = 0;
		coins[i].colected = 0;
	}
	for (int i = 1;i <= lifo;i++) {
		life[i].icolec = 0;
		life[i].jcolec = 0;
		life[i].mapart = 0;
		life[i].colected = 0;
	}
    for (int i = 1;i <= staro;i++) {
        starpow[i].icolec = 0;
        starpow[i].jcolec = 0;
        starpow[i].mapart = 0;
		starpow[i].colected = 0;
    }
	for (int i = 1;i <= firo;i++) {
		fflower[i].icolec = 0;
		fflower[i].jcolec = 0;
		fflower[i].mapart = 0;
		fflower[i].colected = 0;
	}
	for (int i = 0;i <= 8;i++) {
        fireb[i].exist = 0;
        fireb[i].ifireb = 0; 
        fireb[i].jfireb = 0;
        fireb[i].fbdirection = 1;
        fireb[i].fbstage = 1;
        fireb[i].hoverf = 0;
        fireb[i].mapart = 0;
	}
	firo = 0;
    staro = 0;
    coino = 0;
    lifo = 0;
    ncf = nc1;
    nci = 0;
    timespent = 0;
	flagpolei = -1;
    flagpolej = -2;
    fpow = 0;
}

void saveData(char* strArray[], int intValue, LevelStats LvlSts[]) {
    std::ofstream outfile("CUSTOMLEVELS.txt");

    if (!outfile.is_open()) {
        std::cerr << "Error opening file for saving!" << std::endl;
        return;
    }

    outfile << intValue << '\n';

    for (int i = 0; i < intValue; i++) {
        outfile << strArray[i] << " ";
        if (i <= 8) {
            outfile << LvlSts[i].coins << " " << LvlSts[i].enemies << " " << LvlSts[i].time << " " << LvlSts[i].score << '\n';
        }
    }

    outfile.close();
}


void loadData(char* strArray[], int& intValue, LevelStats LvlSts[]) {
    std::ifstream infile("CUSTOMLEVELS.txt");

    infile >> intValue;
    infile.ignore();

    for (int i = 0; i < intValue; i++) {
        char str[50];
        infile.getline(str, 50, ' ');

        strArray[i] = new char[strlen(str) + 1];
        strcpy(strArray[i], str);
       
		LvlSts[i].disname = new char[strlen(str) + 1];
		strcpy(LvlSts[i].disname, str);
        LvlSts[i].name = new char[strlen(str) + 1];
        strcpy(LvlSts[i].name, str);
		infile >> LvlSts[i].coins >> LvlSts[i].enemies >> LvlSts[i].time >> LvlSts[i].score;
		infile.ignore();

    }

    infile.close();
}

void saveStats(LevelStats LvlSts[]) {
    std::ofstream outfile("LEVELSTATS.txt");

    if (!outfile.is_open()) {
        std::cerr << "Error opening file for saving!" << std::endl;
        return;
    }
    for (int i = 0; i < 9; i++) {
        outfile << LvlSts[i].name << " " << LvlSts[i].disname << "% "<< LvlSts[i].coins << " " << LvlSts[i].enemies << " " << LvlSts[i].time << " " << LvlSts[i].score << '\n';
    }

    outfile.close();
}

void loadStats(LevelStats LvlSts[]) {
    std::ifstream infile("LEVELSTATS.txt");

    for (int i = 0; i < 9; i++) {
        char str[50], str1[50];
        infile.getline(str, 50, ' ');
        LvlSts[i].name = new char[strlen(str) + 1];
        strcpy(LvlSts[i].name, str);
        infile.getline(str1, 50, '%');
        LvlSts[i].disname = new char[strlen(str1) + 1];
        strcpy(LvlSts[i].disname, str1);

        infile >> LvlSts[i].coins >> LvlSts[i].enemies >> LvlSts[i].time >> LvlSts[i].score;
        infile.ignore();

    }

    infile.close();
}