#pragma once
#include <raylib.h>
#include <GameLayer/spritesheet.h>

class Character {
public:
	Vector2 position;
	int health = 100;
	float speed = 400;
	Spritesheet* sheet;
	Rectangle charRectangle;
	Character();
	Character(Vector2 pos, Spritesheet* spritesheet, Rectangle rect) {
		position = pos;
		sheet = spritesheet;
		charRectangle = rect;
	};
	void draw();
	virtual void update(float);
};