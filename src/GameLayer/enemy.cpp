#include <GameLayer/character.h>
#include <GameLayer/enemy.h>
#include <raylib.h>
#include <raymath.h>

void Enemy::update(float deltaTime) {
	
}
void Enemy::update(float deltaTime, Vector2 playerPos, bool collision) {
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
