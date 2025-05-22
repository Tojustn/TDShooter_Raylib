#pragma once 
#include <raylib.h>
#include <GameLayer/character.h>
class Enemy : public Character {
public:
	int frame = 1;
	int maxFrames = 8;
	int frameSpace = 64;
	int frameY = 0;
	int frameWidth = 20;
	int frameHeight = 16;
	float animationTimer = 0.0f;
	float animationInterval = .2;
	Vector2 knockback{ 0,0 };
	// Coords for one sprite of enemy
	Enemy(Vector2 startPosition, Spritesheet* spritesheet, Rectangle enemyRect)
		: Character(startPosition, spritesheet, enemyRect) {

	};
	void update(float) override;
	void update(float, Vector2, bool);
	void draw() override;

};