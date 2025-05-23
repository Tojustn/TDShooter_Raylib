#pragma once 
#include <raylib.h>
#include <GameLayer/character.h>
class Enemy : public Character {
public:
	// Coords for one sprite of enemy
	Enemy(Vector2 startPosition, Spritesheet* spritesheet)
		: Character(startPosition, spritesheet) {
		frame = 1;
		maxFrames = 8;
		frameSpace = 64;
		frameYSpace = 0;
		frameWidth = 20;
		frameHeight = 16;
		animationTimer = 0.0f;
		animationInterval = 0.2f;

	};
	void update(float) override;
	void update(float, Vector2, bool);
	void draw() override;

};