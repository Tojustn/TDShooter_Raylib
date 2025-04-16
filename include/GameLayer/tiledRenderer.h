#pragma once 
#include <raylib.h>

class TiledRenderer {
public:
	float backgroundSize = 1200;
	Texture texture;

	void draw(Camera2D&);
};