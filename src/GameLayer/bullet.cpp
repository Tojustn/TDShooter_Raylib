#include <GameLayer/bullet.h>
#include <raylib.h>
#include "raymath.h"

void Bullet::draw(Texture& texture) {
	DrawTextureEx(texture, position, orientation, .8, WHITE);
}

void Bullet::update(float deltaTime) {
	position = Vector2Add(position, Vector2Scale(fireDirection, deltaTime * 1500.f));

}