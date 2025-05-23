#pragma once
#include <raylib.h>
#include <GameLayer/spritesheet.h>

class Character {
public:
	Vector2 position;
	bool flipped = false;
	float speed = 400;
	int frame;
	int maxFrames;
	int frameSpace;
	int frameY;
	int frameYSpace;
	int frameWidth;
	int frameHeight;
	float animationTimer;
	float animationInterval;
	Vector2 knockback{ 0,0 };
	Spritesheet* sheet;
	
	Character();
	Character(Vector2 pos, Spritesheet* spritesheet) {
		position = pos;
		sheet = spritesheet;
	};
	virtual void draw();
	virtual void update(float);
};