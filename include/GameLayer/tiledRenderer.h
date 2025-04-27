#pragma once 
#include <raylib.h>

class TiledRenderer {
public:
	float backgroundSize = 1200;
	Texture texture;

	float parallaxFactor = .1;
	void draw(Camera2D&);
};