#pragma once
#include <GameLayer/character.h>
#include <raylib.h>
class User : public Character {
public:
	int health;
	int maxHealth;
	int orientation = 1;
	int frameY = 1;
	User(Spritesheet* spritesheet,int maxHealth)
		: Character({ 100,100 }, spritesheet) {
		this->maxHealth = maxHealth;
		this->health = maxHealth;
		speed = 500;
		frame = 1;
		maxFrames = 4;
		frameSpace = 80;
		frameY = 1;
		frameYSpace = 80;
		frameWidth = 16;
		frameHeight = 16;
		animationTimer = 0.0f;
		animationInterval = 0.2f;
	}
	void draw() override;
	void update(float deltaTime) override;


};
