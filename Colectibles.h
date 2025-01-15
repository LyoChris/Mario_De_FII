#pragma once

struct colectible {
	int icolec, jcolec;
	int colected = 0;
	int mapart;
};


struct firebll {
	int exist = 0;
	float ifireb, jfireb;
	int fbdirection = 1;
	int fbstage = 1;
	int hoverf = 0;
	int mapart;
};

void fireballsmov();