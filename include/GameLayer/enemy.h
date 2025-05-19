#pragma once 
#include <raylib.h>
#include <GameLayer/character.h>
class Enemy : public Character {
public:
	// Coords for one sprite of enemy
	Enemy(Vector2 startPosition, Spritesheet* spritesheet, Rectangle enemyRect)
		: Character(startPosition, spritesheet, enemyRect) {

	}
	void update(float) override;
	void update(float, Vector2);
};