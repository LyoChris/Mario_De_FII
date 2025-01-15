#include "graphics.h"
#include <fstream>
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
using namespace std;

goompa gompav[100];
pirhana piranav[100];
extern colectible coins[100], starpow[100], life[100], fflower[100];

extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * pirana_1, * pirana_2, * pipehead, * mario_star, *one_up,
* Rpipehead, * Rpirana_1, * Rpirana_2, *fire_flower;

extern float nci, ncf, nc1;
extern int harta[30][1000], coino, staro, lifo, firo;
int n = 0, p = 0, ranpirana = 0;
extern float wh;

void gompastateput(int a) {
	switch (gompav[a].gstage) {
	case 1:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_1, COPY_PUT); break;
	case 2:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_2, COPY_PUT); break;
	case -1:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_1, COPY_PUT); break;
	case -2:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_2, COPY_PUT); break;
	}
}

void gompastateread(int a) {
	switch (gompav[a].gstage) {
		case 1:
			readimagefile("goomba_walking_1.gif", (gompav[a].jgompa- nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa -nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case 2:
			readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case -1:
			readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case -2:
			readimagefile("goomba_walking_1.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);break;
	}
}

void gompa(int a) {
	float w = 0;
	if ((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 1 || gompav[a].jgompa + 1 > ncf || harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa + 1] == 0)
		|| (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 12 || gompav[a].jgompa + 1 > ncf || harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa + 1] == 0)
		|| (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 13 || gompav[a].jgompa + 1 > ncf || harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa + 1] == 0)
		|| (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 14 || gompav[a].jgompa + 1 > ncf || harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa + 1] == 0)) gompav[a].gdirection = 1;
	if (((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa - 1] == 1 && gompav[a].jgompa - (int)gompav[a].jgompa == 0) || gompav[a].jgompa - 1 < 0 ||
		(harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa - 1] == 0 && (int)gompav[a].jgompa - gompav[a].jgompa == 0))
		|| ((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa - 1] == 12 && gompav[a].jgompa - (int)gompav[a].jgompa == 0) || gompav[a].jgompa - 1 < 0 ||
			(harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa - 1] == 0 && (int)gompav[a].jgompa - gompav[a].jgompa == 0))
		|| ((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa - 1] == 13 && gompav[a].jgompa - (int)gompav[a].jgompa == 0) || gompav[a].jgompa - 1 < 0 ||
			(harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa - 1] == 0 && (int)gompav[a].jgompa - gompav[a].jgompa == 0))
		|| ((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa - 1] == 14 && gompav[a].jgompa - (int)gompav[a].jgompa == 0) || gompav[a].jgompa - 1 < 0 ||
			(harta[(int)gompav[a].igompa + 1][(int)gompav[a].jgompa - 1] == 0 && (int)gompav[a].jgompa - gompav[a].jgompa == 0))) gompav[a].gdirection = 0;
	if (gompav[a].gdirection == 1) {
		gompav[a].hoverg = 0;
		if (gompav[a].gstage < 0) gompav[a].gstage = 0;
		gompav[a].gstage++;
		if (gompav[a].gstage > 2) gompav[a].gstage = 1;
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, skyblock, COPY_PUT);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa -nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 4) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 4) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				gompav[a].hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 4) {
				gompav[a].hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0 && abs(coins[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
			}
		}
		for (int i = 1;i <= staro; i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == gompav[a].igompa && starpow[i].colected == 0 && abs(starpow[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == gompav[a].igompa && life[i].colected == 0 && abs(life[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
			}
		}
		for (int i = 1;i <= firo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == gompav[a].igompa && fflower[i].colected == 0 && abs(fflower[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, fire_flower, COPY_PUT);
			}
		}
		if (gompav[a].hoverg == 1) {
			if (gompav[a].jgompa > 0 && harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] != 1) {
				gompav[a].jgompa -= 0.5;
				gompastateread(a);
			}
		}
		else {
			if (gompav[a].jgompa > 0 && harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] != 1) {
				gompav[a].jgompa -= 0.5;
				gompastateput(a);
			}
		}
		gompav[a].hoverg = 0;
	}
	if (gompav[a].gdirection == 0) {
		gompav[a].hoverg = 0;
		if (gompav[a].gstage > 0) gompav[a].gstage = 0;
		gompav[a].gstage--;
		if (gompav[a].gstage < -2) gompav[a].gstage = -1;
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, skyblock, COPY_PUT);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa +1 - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 4) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 4) {
				gompav[a].hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				gompav[a].hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 4) {
				gompav[a].hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine_top, COPY_PUT);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0 && abs(coins[i].jcolec - gompav[a].jgompa)<2) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[i].icolec, coins[i].jcolec)) {
					gompav[a].hoverg = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= staro;i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == gompav[a].igompa && starpow[i].colected == 0 && abs(starpow[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == gompav[a].igompa && life[i].colected == 0 && abs(life[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
			}
		}
		for (int i = 1;i <= firo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == gompav[a].igompa && fflower[i].colected == 0 && abs(fflower[i].jcolec - gompav[a].jgompa) < 2) {
					gompav[a].hoverg = 1;
					putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, fire_flower, COPY_PUT);
			}
		}
		if (gompav[a].hoverg == 1) {
			if (gompav[a].jgompa < ncf) {
				gompav[a].jgompa += 0.5;
				gompastateread(a);
			}
		}
		else {
			if (gompav[a].jgompa < ncf) {
				gompav[a].jgompa += 0.5;
				gompastateput(a);
			}
		}
		gompav[a].hoverg = 0;
	}
}

void pirhanastate(int a) {
	switch (piranav[a].pstage) {
		case 1:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, pirana_1, COPY_PUT); break;
		case 2:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, pirana_2, COPY_PUT); break;
		case -1:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, Rpirana_1, COPY_PUT); break;
		case -2:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, Rpirana_2, COPY_PUT); break;
	}
}

void pirhananext(int a) {
	if (piranav[a].upframes <= 0 && piranav[a].reset == 0) piranav[a].pause--;
	if (piranav[a].upframes <= 0 && piranav[a].reset == 0 && piranav[a].pause<=0) {
		ranpirana = randnumb(0, 1);
		if (ranpirana == 1) {
			piranav[a].upframes = 22;
			piranav[a].reset = 2;
		}
		piranav[a].pause = 30;
	}
	if (piranav[a].orientation == 1 && piranav[a].upframes > 0) {
		if (piranav[a].pstage == 1) piranav[a].pstage = 2;
		else piranav[a].pstage = 1;
		putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, skyblock, COPY_PUT);
		if (piranav[a].upframes > 20) {
			piranav[a].ipirana -= 0.5;
			pirhanastate(a);
			putimage((piranav[a].jpinit - nci) * wh, piranav[a].ipinit * wh, pipehead, COPY_PUT);
		}
		else {
			pirhanastate(a);
		}
	}
	else {
		if (piranav[a].upframes > 0) {
			if (piranav[a].pstage == -1) piranav[a].pstage = -2;
			else piranav[a].pstage = -1;
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, skyblock, COPY_PUT);
			if (piranav[a].upframes > 20) {
				piranav[a].ipirana += 0.5;
				pirhanastate(a);
				putimage((piranav[a].jpinit - nci) * wh, piranav[a].ipinit * wh, Rpipehead, COPY_PUT);
			}
			else {
				pirhanastate(a);
			}
		}
	}
	if (piranav[a].reset > 0 && piranav[a].upframes <=0) {
		if (piranav[a].orientation == 1) {
			if (piranav[a].pstage == 1) piranav[a].pstage = 2;
			else piranav[a].pstage = 1;
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, skyblock, COPY_PUT);
			piranav[a].ipirana += 0.5;
			pirhanastate(a);
			putimage((piranav[a].jpinit - nci) * wh, piranav[a].ipinit * wh, pipehead, COPY_PUT);
		}
		else {
			if (piranav[a].pstage == -1) piranav[a].pstage = -2;
			else piranav[a].pstage = -1;
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, skyblock, COPY_PUT);
			piranav[a].ipirana -= 0.5;
			pirhanastate(a);
			putimage((piranav[a].jpinit - nci) * wh, piranav[a].ipinit * wh, Rpipehead, COPY_PUT);
		}
		piranav[a].reset--;
	}
	piranav[a].upframes--;
}

void EnemiesMoving() {
	for (int i = 1;i <= n;i++) {
		if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
			gompa(i);
		}
	}
	for (int i = 1;i <= p;i++) {
		if (piranav[i].mapart == (int)(nci - nc1) && piranav[i].dead == 0) {
			pirhananext(i);
		}
	}
}
