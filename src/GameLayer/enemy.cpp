#include <GameLayer/character.h>
#include <GameLayer/enemy.h>
#include <raylib.h>
#include <raymath.h>

void Enemy::update(float deltaTime) {
	
}
void Enemy::update(float deltaTime, Vector2 playerPos) {
	MoveEnemy(deltaTime, playerPos);
}
void Enemy::MoveEnemy(float deltaTime, Vector2 playerPos) {
	// Get vector pointing at the player
	Vector2 direction = Vector2Normalize(Vector2Subtract(playerPos, position));
	position = Vector2Add(position, Vector2Scale(direction, deltaTime * speed));
}