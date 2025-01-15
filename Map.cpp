#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <thread>
#include <string>
#include <mmsystem.h>
#include "Enemies.h"
#include "Map.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Sounds.h"
#include "MapEditor.h"
using namespace std;

string cht,  levelselect;

void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * flagpolemapedit, * pipebody,
* mario_star, * pipehead, * pirana_1, * pirana_2, * pipeheadpir, * mariostar, * mario_climbing_down_1_star, * mario_climbing_down_2_star, * mario_climbing_up_1_star,
* mario_climbing_up_2_star, * mario_idle_left_star, * mario_idle_right_star, * mario_jump_1_star, * mario_left_run_1_star, * mario_left_run_2_star,
* mario_left_run_3_star, * mario_right_run_1_star, * mario_right_run_2_star, * mario_right_run_3_star, * mario_main_screen, * mario_levels_menu, * mario_jump_2,
* Rpirana_1, * Rpirana_2, * Mmario_climbing_down_1, * Mmario_climbing_down_2, * Mmario_climbing_up_1,
* Mmario_climbing_up_2, * Mmario_idle_left, * Mmario_idle_right, * Mmario_jump_1, * Mmario_left_run_1, * Mmario_left_run_2, * Mmario_left_run_3, * Mmario_right_run_1,
* Mmario_right_run_2, * Mmario_right_run_3, * Mmario_jump_2, * MFmario_climbing_down_1, * MFmario_climbing_down_2, * MFmario_climbing_up_1,
* MFmario_climbing_up_2, * MFmario_idle_left, * MFmario_idle_right, * MFmario_jump_1, * MFmario_left_run_1, * MFmario_left_run_2, * MFmario_left_run_3, * MFmario_right_run_1,
* MFmario_right_run_2, * MFmario_right_run_3, * MFmario_jump_2, * Fmario_climbing_down_1, * Fmario_climbing_down_2, * Fmario_climbing_up_1,
* Fmario_climbing_up_2, * Fmario_idle_left, * Fmario_idle_right, * Fmario_jump_1, * Fmario_left_run_1, * Fmario_left_run_2, * Fmario_left_run_3, * Fmario_right_run_1,
* Fmario_right_run_2, * Fmario_right_run_3, * Fmario_jump_2, * fireball_1, * fireball_2, * fire_flower, * mario_custom_screen,
* mario_vine_idle_up, * mario_vine_idle_down, * Mmario_vine_idle_up, * Mmario_vine_idle_down, * Fmario_vine_idle_up, * Fmario_vine_idle_down,
* FMmario_vine_idle_up, * FMmario_vine_idle_down;

extern void* Rpipeheadpir, * Rpipehead;

extern pirhana piranav[100];
extern colectible coins[100], life[100], starpow[100], fflower[100];
extern firebll fireb[100];
pozitii spawn[100];
float wh, ncf, nci = 0, nc1, imario, jmario;
int  x, y, nl = 20, nc, harta[30][1000], mv2, map, mappart, spawncount = 1, flagpolej = -2, flagpolei = -1, okmap = 1, flagpole;
extern goompa gompav[100];
extern int n, coino, lifo, p, staro, firo;



void MapReaderandSetter() {
    x = GetSystemMetrics(SM_CXSCREEN); //1536 864
    y = GetSystemMetrics(SM_CYSCREEN);
    wh = (float)y / (float)nl;
    nc1 = (float)x / wh;
    ncf = nc1;
    AssetLoader();
    AssetLoaderMap();
    initwindow(x, y, "", -3, -3);
}

void MapLoader() {
    ifstream f(cht);
    f >> nc;
    for (int i = 0; i < nl;i++) {
        for (int j = 0;j < nc;j++) {
            f >> harta[i][j];
        }
    }
    f.close();
    levelselect = cht;
    //initwindow(x, y, "", -3, -3);
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0; i < nl;i += 1) {
        for (int j = nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                putimage(j * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
                putimage(j * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
                putimage(j * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 9) {
                putimage(j * wh, i * wh, mario_idle_right, COPY_PUT);
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
            if (harta[i][j] == 7) {
                putimage(j * wh, i * wh, mario_coin, COPY_PUT);
                coino++;
                coins[coino].icolec = i;
                coins[coino].jcolec = j;
                coins[coino].mapart = (int)(nci - nc1);
                coins[coino].colected = 0;
                harta[i][j] = 0;
            }
            if (harta[i][j] == 16) {
                putimage(j * wh, i * wh, fire_flower, COPY_PUT);
                firo++;
                fflower[firo].icolec = i;
                fflower[firo].jcolec = j;
                fflower[firo].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 15) {
                putimage(j * wh, i * wh, mario_star, COPY_PUT);
                staro++;
                starpow[staro].icolec = i;
                starpow[staro].jcolec = j;
                starpow[staro].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 8) {
                putimage(j * wh, i * wh, lucky_block, COPY_PUT);
            }
            if (harta[i][j] == 10) {
                putimage(j * wh, i * wh, lucky_block_used, COPY_PUT);
            }
            if (harta[i][j] == 2) {
                putimage(j * wh, i * wh, one_up, COPY_PUT);
                lifo++;
                life[lifo].icolec = i;
                life[lifo].jcolec = j;
                life[lifo].mapart = (int)(nci - nc1);
                harta[i][j] = 0;

            }
            if (harta[i][j] == 11) {
                flagpolej = j;
                flagpolei = i;
                putimage((j) * wh, ((i) - 6) * wh, flagpolep, COPY_PUT);

                harta[i][j] = 11;
                for (int k = i;k >= i - 6;k--) {
                    harta[k][j] = 20;
                }
            }
            if (harta[i][j] == 12) {
                putimage(j * wh, i * wh, pipebody, COPY_PUT);
            }
            if (harta[i][j] == 14) {
                if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
                }
                else {
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
            }
            if (harta[i][j] == 13) {
                p++;
				piranav[p].ipinit = i;
				piranav[p].jpinit = j;
                piranav[p].ipirana = i;
                piranav[p].jpirana = j;
				if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
					piranav[p].orientation = -1;
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
				}
                else {
					piranav[p].orientation = 1;
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
				piranav[p].mapart = (int)(nci - nc1);
            }
            if (harta[i][j] == 5) {
                    n++;
                    gompav[n].mapart = (int)(nci - nc1);
                    gompav[n].igompa = i;
                    gompav[n].jgompa = j;
                    harta[i][j] = 0;
					putimage(j * wh, i * wh, goomba_walking_1, COPY_PUT);
                    harta[i][j] == 0;
            }
        }
		putimage(0, 0, skyblock, COPY_PUT);
    }
	setvisualpage(0);
}

void MapLoaderNextRight() {
    nci = nci + nc1;
    ncf = ncf + nc1;
	if (ncf > nc) ncf = nc;
    okmap = 1;
    setactivepage(1);
    cleardevice();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    cleardevice();

    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
				putimage((j - nci) * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
				putimage((j - nci) * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
				putimage((j - nci) * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 8) {
                putimage((j - nci) * wh, i * wh, lucky_block, COPY_PUT);
            }
            if (harta[i][j] == 10) {
                putimage((j - nci) * wh, i * wh, lucky_block_used, COPY_PUT);
            }
            if (harta[i][j] == 5) {
                n++;
                gompav[n].mapart = (int)(nci - nc1);
                gompav[n].igompa = i;
                gompav[n].jgompa = j;
                putimage((j - nci) * wh, i * wh, goomba_walking_1, COPY_PUT);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 11) {
                flagpolej = j;
                flagpolei = i;
                putimage((j - nci) * wh, (i - 6) * wh, flagpolep, COPY_PUT);

                harta[i][j] = 11;
				for (int k = i;k >= i-6;k--) {
						harta[k][j] = 20;
				}
            }
            if (harta[i][j] == 12) {
                putimage(j * wh, i * wh, pipebody, COPY_PUT);
            }
            if (harta[i][j] == 14) {
                if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
                }
                else {
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
            }
            if (harta[i][j] == 13) {
                p++;
                piranav[p].ipinit = i;
                piranav[p].jpinit = j;
                piranav[p].ipirana = i;
                piranav[p].jpirana = j;
                if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
                    piranav[p].orientation = -1;
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
                }
                else {
                    piranav[p].orientation = 1;
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
                piranav[p].mapart = (int)(nci - nc1);
            }
            if (harta[i][j] == 7) {
                putimage((j - nci) * wh, i * wh, mario_coin, COPY_PUT);
                coino++;
                coins[coino].icolec = i;
                coins[coino].jcolec = j;
                coins[coino].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 2) {
                putimage((j - nci) * wh, i * wh, one_up, COPY_PUT);
                lifo++;
                life[lifo].icolec = i;
                life[lifo].jcolec = j;
                life[lifo].mapart = (int)(nci - nc1);
                harta[i][j] = 0;

            }
            if (harta[i][j] == 15) {
				setcolor(YELLOW);
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
                staro++;
                starpow[staro].icolec = i;
                starpow[staro].jcolec = j;
                starpow[staro].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
        }
        for (int i = 1;i <= coino;i++) {
            if (coins[i].mapart == (int)(nci - nc1) && coins[i].colected == 0) {
                putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
            }
        }
        for (int i = 1;i <= staro;i++) {
            if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].colected == 0) {
                putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
            }
        }
        for (int i = 1;i <= lifo;i++) {
            if (life[i].mapart == (int)(nci - nc1) && life[i].colected == 0) {
                putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
            }
        }
        for (int i = imario; i < nl;++i) {
            for (int j = (int)jmario+1;j < jmario + 3;++j) {
                if (harta[i + 1][j] == 1 && harta[i][j]!=1 && okmap==1) {
                    imario = i;
                    jmario = j +1;
                    okmap = 0;
                }
				if (okmap == 0)
					break;
            }
        }
        if (okmap != 0) {
            imario = 0;
            jmario = ncf - nci + 2;
        }
        putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT);
    };
    setvisualpage(0);
}

void MapLoaderPrevLeft() {
    if (ncf == nc) {
        ncf = nci;
        nci = nci - nc1;
    }
    else {
        nci = nci - nc1;
        ncf = ncf - nc1;
    }
    
    okmap = 1;
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                putimage((j - nci) * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
                putimage((j - nci) * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
                putimage((j - nci) * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 8) {
                putimage((j-nci) * wh, i * wh, lucky_block, COPY_PUT);
            }
            if (harta[i][j] == 12) {
				putimage((j - nci) * wh, i * wh, pipebody, COPY_PUT);

                //bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe body
            }
            if (harta[i][j] == 14) {
				putimage((j - nci) * wh, i * wh, pipehead, COPY_PUT);
               // bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head without pirhana
            }
            if (harta[i][j] == 13) {
				putimage((j - nci) * wh, i * wh, pipehead, COPY_PUT);
                //bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head with pirhana
            }
            if (harta[i][j] == 10) {
                putimage((j-nci) * wh, i * wh, lucky_block_used, COPY_PUT);
            }
            if (harta[i][j] == 12) {
                putimage(j * wh, i * wh, pipebody, COPY_PUT);
            }
            if (harta[i][j] == 14) {
                if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
                }
                else {
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
            }
            if (harta[i][j] == 13) {
                if (harta[i - 1][j] == 1 || harta[i - 1][j] == 12 || harta[i - 1][j] == 14 || harta[i - 1][j] == 13) {
                    putimage(j * wh, i * wh, Rpipehead, COPY_PUT);
                }
                else {
                    putimage(j * wh, i * wh, pipehead, COPY_PUT);
                }
                piranav[p].mapart = (int)(nci - nc1);
            }
            
        }
        for (int i = 1;i <= coino;i++) {
            if (coins[i].mapart == (int)(nci - nc1) && coins[i].colected == 0) {
                putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
            }
        }
        for (int i = 1;i <= staro;i++) {
            if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].colected == 0) {
                putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
            }
        }
        for (int i = 1;i <= lifo;i++) {
            if (life[i].mapart == (int)(nci - nc1) && life[i].colected == 0) {
                putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
            }
        }
        for (int i = imario - 1; i < nl;++i) {
            for (int j = ncf - 1;j > ncf - 3;--j) {
                if (harta[i + 1][j] == 1 && harta[i][j] != 1 && okmap == 1) {
                    imario = i;
                    jmario = j;
                    okmap = 0;
                }
                if (okmap == 0)
                    break;
            }
        }
        if (okmap != 0) {
            imario = 0;
            jmario = ncf - nci - 2;
        }
        /*
        imario = spawn[(int)(nci / nc1)].ifinal;
        jmario = spawn[(int)(nci / nc1)].jfinal;
		putimage((spawn[(int)(nci / nc1)].jfinal - nci) * wh, spawn[(int)(nci / nc1)].ifinal * wh, mario_idle_left, COPY_PUT);*/
    }
	setvisualpage(0);
}