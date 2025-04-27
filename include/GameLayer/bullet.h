#pragma once
#include <raylib.h>
class Bullet {
public:
	Vector2 position;
	Vector2 fireDirection;
	float orientation;

	void draw(Texture&);

	void update(float);
};