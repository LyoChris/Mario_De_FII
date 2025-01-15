#pragma once
#include <string>

struct pozitii {
	int ibegin, jbegin;
	int ifinal, jfinal;
};

void preloadImage(const char* filename, int width, void*& buffer);
void MapReaderandSetter();
void MapLoader();
void MapLoader2();
void MapLoaderNextRight();
void MapLoaderPrevLeft();