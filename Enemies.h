#pragma once

struct goompa {
	float igompa, jgompa;
	int gdirection = 1;
	int gstage = 1;
	int dead = 0;
	int hit=0;
	int hoverg = 0;
	int mapart;
};

struct pirhana {
	float ipinit, jpinit;
	float ipirana, jpirana;
	int pdirection = 1;
	int pstage = 1;
	int upframes = 0;
	int orientation = 1;
	int reset = 0;
	int dead = 0;
	int mapart;
	int pause = 0;
};

void EnemiesMoving();