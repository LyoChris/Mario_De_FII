#include "graphics.h"
#include <iostream>
#include "Colissions.h"
#include "Colectibles.h"
#include "Enemies.h"
#include "miniaudio.h"
#include "Sounds.h"

extern ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, DeathEffect, BackGroundMusic, StageClear, OneUpEffect, FireBallEffect, PowerUpAppearEffect, PowerUpEffect, FireBallEffect;
colectible coins[100], stars[100], life[100], starpow[100], fflower[100];
extern goompa gompav[100];
extern pirhana piranav[100];
firebll fireb[9];
int coino = 0, lifo = 0, staro = 0, fpow, firo=0;
extern float nci, ncf, nc1, wh;
extern int harta[30][1000], n, p, gdead;
extern void* skyblock, * mario_coin, * one_up, * mario_star, * mario_vine, * mario_vine_top, * fireball_1, * fireball_2, * fire_flower, * pipehead, * Rpipehead;


void fireballstateput(int a) {
	switch (fireb[a].fbstage) {
	case 1:
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, fireball_1, COPY_PUT); break;
	case 2:
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, fireball_2, COPY_PUT); break;
	}
}

void fireballstateread(int a) {
	switch (fireb[a].fbstage) {
		case 1:
			readimagefile("fireball_1.gif", (fireb[a].jfireb - nci+ 0.3) * wh, (fireb[a].ifireb +0.3) * wh, ((fireb[a].jfireb - nci) + 0.7) * wh, (fireb[a].ifireb + 0.7) * wh); break;
		case 2:
			readimagefile("fireball_2.gif", (fireb[a].jfireb - nci + 0.3) * wh, (fireb[a].ifireb + 0.3) * wh, ((fireb[a].jfireb - nci) + 0.7) * wh, (fireb[a].ifireb + 0.7) * wh); break;
	}
}

void fireballmov(int a) {
	if (fireb[a].fbstage == 1) fireb[a].fbstage = 2;
	else fireb[a].fbstage = 1;
	if (fireb[a].fbdirection == 1) {
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, skyblock, COPY_PUT);
		if (fireb[a].jfireb - (int)fireb[a].jfireb != 0) {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 3) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 4) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
		}
		else {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == fireb[a].ifireb && coins[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, coins[i].icolec, coins[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= staro; i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == fireb[a].ifireb && starpow[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, starpow[i].icolec, starpow[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == fireb[a].ifireb && life[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, life[i].icolec, life[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= firo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == fireb[a].ifireb && fflower[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, fflower[i].icolec, fflower[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, fire_flower, COPY_PUT);
				}
			}
		}
		if (fireb[a].hoverf == 1) {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb > nci && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 10)) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					ma_sound_stop(&FireBallEffect);
					ma_sound_seek_to_pcm_frame(&FireBallEffect, 0);
					ma_sound_start(&FireBallEffect);
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb > nci) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}

		}
		else {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb > nci && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 10)) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					ma_sound_stop(&FireBallEffect);
					ma_sound_seek_to_pcm_frame(&FireBallEffect, 0);
					ma_sound_start(&FireBallEffect);
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb > nci) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}

		}
	}
	if (fireb[a].fbdirection == 0) {
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, skyblock, COPY_PUT);
		if (fireb[a].jfireb - (int)fireb[a].jfireb != 0) {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 3) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 4) {
				fireb[a].hoverf = 1;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
		}
		else {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == fireb[a].ifireb && coins[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, coins[i].icolec, coins[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= staro; i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == fireb[a].ifireb && starpow[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, starpow[i].icolec, starpow[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == fireb[a].ifireb && life[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, life[i].icolec, life[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
				}
			}
		}
		for (int i = 1;i <= firo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == fireb[a].ifireb && fflower[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, fflower[i].icolec, fflower[i].jcolec)) {
					fireb[a].hoverf = 1;
					putimage((fflower[i].jcolec - nci)* wh, fflower[i].icolec* wh, fire_flower, COPY_PUT);
				}
			}
		}
		if (fireb[a].hoverf == 1) {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb < ncf && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb+1] != 1
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 13
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 8
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 10)) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					ma_sound_stop(&FireBallEffect);
					ma_sound_seek_to_pcm_frame(&FireBallEffect, 0);
					ma_sound_start(&FireBallEffect);
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb < ncf) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}
			
		}
		else {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb < ncf && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 10)) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					ma_sound_stop(&FireBallEffect);
					ma_sound_seek_to_pcm_frame(&FireBallEffect, 0);
					ma_sound_start(&FireBallEffect);
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb < ncf) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}
		}
	}
}

void fireballsmov() {
	for (int i = 0;i < 8;i++) {
		if (fireb[i].exist == 1) {
			
			for (int j = 1;j <= n;j++) {
				if (gompav[j].mapart == (int)(nci - nc1) && gompav[j].igompa == fireb[i].ifireb && gompav[j].dead == 0) {
					if (CheckBlock(fireb[i].ifireb * wh, fireb[i].jfireb * wh, wh, gompav[j].igompa * wh, gompav[j].jgompa * wh)) {
						
						fireb[i].exist = 0;
						gompav[j].dead = 1;
						gdead++;
						ma_sound_stop(&GombaDeadEffect);
						ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
						ma_sound_start(&GombaDeadEffect);
						putimage((fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, skyblock, COPY_PUT);
						putimage((gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, skyblock, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 3)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 4)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 3)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 4)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb] == 3)
							putimage(((int)fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, mario_vine, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb] == 4)
							putimage(((int)fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb + 1] == 3)
							putimage(((int)fireb[i].jfireb - nci + 1) * wh, fireb[i].ifireb * wh, mario_vine, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb + 1] == 4)
							putimage(((int)fireb[i].jfireb - nci + 1) * wh, fireb[i].ifireb * wh, mario_vine_top, COPY_PUT);
						
					}
					for (int k = 1;k <= coino;k++) {
						if (coins[k].mapart == (int)(nci - nc1) && coins[k].icolec == gompav[j].igompa && coins[k].colected == 0 && abs((int)(coins[k].jcolec - gompav[j].jgompa)) <= 1) {
							if (CheckBlock(gompav[j].igompa, gompav[j].jgompa, wh, coins[k].icolec, coins[k].jcolec)) {
								putimage((coins[k].jcolec - nci) * wh, coins[k].icolec * wh, mario_coin, COPY_PUT);
							}
						}
						if (coins[k].mapart == (int)(nci - nc1) && coins[k].icolec == fireb[i].ifireb && coins[k].colected == 0 && abs((int)(coins[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, coins[k].icolec, coins[k].jcolec)) {
								putimage((coins[k].jcolec - nci) * wh, coins[k].icolec * wh, mario_coin, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= staro; k++) {
						if (starpow[k].mapart == (int)(nci - nc1) && starpow[j].icolec == gompav[j].igompa && starpow[k].colected == 0 && abs((int)(starpow[k].jcolec - gompav[j].jgompa)) <= 1) {
							if (CheckBlock(gompav[j].igompa, gompav[j].jgompa, wh, starpow[k].icolec, starpow[k].jcolec)) {
								putimage((starpow[k].jcolec - nci) * wh, starpow[k].icolec * wh, mario_star, COPY_PUT);
							}
						}
						if (starpow[k].mapart == (int)(nci - nc1) && starpow[k].icolec == fireb[i].ifireb && starpow[k].colected == 0 && abs((int)(starpow[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, starpow[k].icolec, starpow[k].jcolec)) {
								putimage((starpow[k].jcolec - nci) * wh, starpow[k].icolec * wh, mario_star, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= lifo; k++) {
						if (life[k].mapart == (int)(nci - nc1) && life[k].icolec == gompav[j].igompa && life[k].colected == 0 && abs((int)(life[k].jcolec - gompav[j].jgompa)) <= 1) {
							if (CheckBlock(gompav[j].igompa, gompav[j].jgompa, wh, life[k].icolec, life[k].jcolec)) {
								putimage((life[k].jcolec - nci) * wh, life[k].icolec * wh, one_up, COPY_PUT);
							}
						}
						if (life[k].mapart == (int)(nci - nc1) && life[k].icolec == fireb[i].ifireb && life[k].colected == 0 && abs((int)(life[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, life[k].icolec, life[k].jcolec)) {
								putimage((life[k].jcolec - nci) * wh, life[k].icolec * wh, one_up, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= firo; k++) {
						if (fflower[k].mapart == (int)(nci - nc1) && fflower[k].icolec == gompav[j].igompa && fflower[k].colected == 0 && abs((int)(fflower[k].jcolec - gompav[j].jgompa)) <= 1) {
							if (CheckBlock(gompav[j].igompa, gompav[j].jgompa, wh, fflower[k].icolec, fflower[k].jcolec)) {
								putimage((fflower[k].jcolec - nci) * wh, fflower[k].icolec * wh, fire_flower, COPY_PUT);
							}
						}
						if (fflower[k].mapart == (int)(nci - nc1) && fflower[k].icolec == fireb[i].ifireb && fflower[k].colected == 0 && abs((int)(fflower[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, fflower[k].icolec, fflower[k].jcolec)) {
								putimage((fflower[k].jcolec - nci) * wh, fflower[k].icolec * wh, fire_flower, COPY_PUT);
							}
						}
					}
				}
			}
			for (int j = 1;j <= p;j++) {
				if (piranav[j].mapart == (int)(nci - nc1) && piranav[j].ipirana == fireb[i].ifireb && piranav[j].dead == 0 && piranav[j].ipinit != piranav[j].ipirana) {
					if (CheckBlock(fireb[i].ifireb * wh, fireb[i].jfireb * wh, wh, piranav[j].ipirana * wh, piranav[j].jpirana * wh)) {
						fireb[i].exist = 0;
						piranav[j].dead = 1;
						ma_sound_stop(&GombaDeadEffect);
						ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
						ma_sound_start(&GombaDeadEffect);
						putimage((piranav[j].jpinit - nci) * wh, piranav[j].ipirana * wh, skyblock, COPY_PUT);
						putimage((fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, skyblock, COPY_PUT);
						if (piranav[p].orientation == -1)
							putimage((piranav[j].jpinit - nci) * wh, (piranav[j].ipinit) * wh, Rpipehead, COPY_PUT);
						else
							putimage((piranav[j].jpinit - nci) * wh, (piranav[j].ipinit) * wh, pipehead, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb] == 3)
							putimage(((int)fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, mario_vine, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb] == 4)
							putimage(((int)fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb + 1] == 3)
							putimage(((int)fireb[i].jfireb - nci + 1) * wh, fireb[i].ifireb * wh, mario_vine, COPY_PUT);
						if (harta[(int)fireb[i].ifireb][(int)fireb[i].jfireb + 1] == 4)
							putimage(((int)fireb[i].jfireb - nci + 1) * wh, fireb[i].ifireb * wh, mario_vine_top, COPY_PUT);
					}
					for (int k = 1;k <= coino;k++) {
						if (coins[k].mapart == (int)(nci - nc1) && coins[k].icolec == piranav[j].ipirana && coins[k].colected == 0 && abs((int)(coins[k].jcolec - piranav[j].jpirana)) <= 1) {
							if (CheckBlock(piranav[j].ipirana, piranav[j].jpirana, wh, coins[k].icolec, coins[k].jcolec)) {
								putimage((coins[k].jcolec - nci) * wh, coins[k].icolec * wh, mario_coin, COPY_PUT);
							}
						}
						if (coins[k].mapart == (int)(nci - nc1) && coins[k].icolec == fireb[i].ifireb && coins[k].colected == 0 && abs((int)(coins[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, coins[k].icolec, coins[k].jcolec)) {
								putimage((coins[k].jcolec - nci) * wh, coins[k].icolec * wh, mario_coin, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= staro; k++) {
						if (starpow[k].mapart == (int)(nci - nc1) && starpow[j].icolec == piranav[j].ipirana && starpow[k].colected == 0 && abs((int)(starpow[k].jcolec - piranav[j].jpirana)) <= 1) {
							if (CheckBlock(piranav[j].ipirana, piranav[j].jpirana, wh, starpow[k].icolec, starpow[k].jcolec)) {
								putimage((starpow[k].jcolec - nci) * wh, starpow[k].icolec * wh, mario_star, COPY_PUT);
							}
						}
						if (starpow[k].mapart == (int)(nci - nc1) && starpow[k].icolec == fireb[i].ifireb && starpow[k].colected == 0 && abs((int)(starpow[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, starpow[k].icolec, starpow[k].jcolec)) {
								putimage((starpow[k].jcolec - nci) * wh, starpow[k].icolec * wh, mario_star, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= lifo; k++) {
						if (life[k].mapart == (int)(nci - nc1) && life[k].icolec == piranav[j].ipirana && life[k].colected == 0 && abs((int)(life[k].jcolec - piranav[j].jpirana)) <= 1) {
							if (CheckBlock(piranav[j].ipirana, piranav[j].jpirana, wh, life[k].icolec, life[k].jcolec)) {
								putimage((life[k].jcolec - nci) * wh, life[k].icolec * wh, one_up, COPY_PUT);
							}
						}
						if (life[k].mapart == (int)(nci - nc1) && life[k].icolec == fireb[i].ifireb && life[k].colected == 0 && abs((int)(life[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, life[k].icolec, life[k].jcolec)) {
								putimage((life[k].jcolec - nci) * wh, life[k].icolec * wh, one_up, COPY_PUT);
							}
						}
					}
					for (int k = 1;k <= firo; k++) {
						if (fflower[k].mapart == (int)(nci - nc1) && fflower[k].icolec == piranav[j].ipirana && fflower[k].colected == 0 && abs((int)(fflower[k].jcolec - piranav[j].jpirana)) <= 1) {
							if (CheckBlock(piranav[j].ipirana, piranav[j].jpirana, wh, fflower[k].icolec, fflower[k].jcolec)) {
								putimage((fflower[k].jcolec - nci) * wh, fflower[k].icolec * wh, fire_flower, COPY_PUT);
							}
						}
						if (fflower[k].mapart == (int)(nci - nc1) && fflower[k].icolec == fireb[i].ifireb && fflower[k].colected == 0 && abs((int)(fflower[k].jcolec - fireb[i].jfireb)) <= 1) {
							if (CheckBlock(fireb[i].ifireb, fireb[i].jfireb, wh, fflower[k].icolec, fflower[k].jcolec)) {
								putimage((fflower[k].jcolec - nci) * wh, fflower[k].icolec * wh, fire_flower, COPY_PUT);
							}
						}
					}
				}
			}
			fireballmov(i);
		}
	}
}