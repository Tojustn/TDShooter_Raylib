#include <GameLayer/character.h>
#include <GameLayer/enemy.h>
#include <raylib.h>
#include <raymath.h>

void Enemy::update(float deltaTime) {
	
}
void Enemy::update(float deltaTime, Vector2 playerPos, bool collision) {
	animationTimer+= deltaTime;
	if (animationTimer >= animationInterval) {
		animationTimer = 0.0f;
		frame++;
		if (frame > maxFrames) frame = 1;
	}

	// Get vector pointing at the player
	Vector2 direction = Vector2Normalize(Vector2Subtract(playerPos, position));
	 position = Vector2Add(position, Vector2Scale(direction, deltaTime * speed));

	 if (collision) {
		 knockback = Vector2Scale(direction, -5);
	 }
	 if (Vector2Length(knockback) > 0.1f) {
		 position = Vector2Add(position, Vector2Scale(knockback, deltaTime*speed));
		 // Dampen knockback over time (simulate friction)
		 knockback = Vector2Scale(knockback, 0.9f); // lower = faster stop
	 }



	// Change direction of enemy
	direction.x <= 0 ? flipped = true :flipped = false;
}

void Enemy::draw() {
	std::cout << "Drawing enemy";
	Rectangle enemyRectangle{
		(frame - 1) * frameSpace,
		frameY,
		frameWidth,
		frameHeight

	};
	sheet->drawSprite(position, enemyRectangle, flipped);
}
