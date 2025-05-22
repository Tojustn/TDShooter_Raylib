#pragma once
#include <raylib.h>
#include <GameLayer/spritesheet.h>

class Character {
public:
	Vector2 position;
	bool flipped = false;
	int health = 2;
	float speed = 400;
	Spritesheet* sheet;
	Rectangle charRectangle;
	
	Character();
	Character(Vector2 pos, Spritesheet* spritesheet, Rectangle rect) {
		position = pos;
		sheet = spritesheet;
		charRectangle = rect;
	};
	virtual void draw();
	virtual void update(float);
};