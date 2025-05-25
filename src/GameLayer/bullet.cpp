#include <GameLayer/bullet.h>
#include <raylib.h>
#include "raymath.h"
void Bullet::draw(Texture& texture) {
    float bulletWidth = static_cast<float>(texture.width);
    float bulletHeight = static_cast<float>(texture.height);

    Rectangle source = { 0, 0, bulletWidth, bulletHeight };
    Rectangle dest = { position.x, position.y, bulletWidth, bulletHeight };

    Vector2 origin = { bulletWidth / 2, bulletHeight / 2 };  // center of the bullet

    DrawTexturePro(texture, source, dest, origin, orientation, WHITE);
}
void Bullet::update(float deltaTime) {
	position = Vector2Add(position, Vector2Scale(fireDirection, deltaTime * 1500.f));

}