#include <GameLayer/character.h>
#include <raylib.h>

void Character::draw() {
	// call draw from spritesheet class
	sheet->drawSprite(position, charRectangle,1,false);
}
void Character::update(float deltaTime) {}
