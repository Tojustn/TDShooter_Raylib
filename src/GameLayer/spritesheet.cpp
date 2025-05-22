#include <raylib.h>
#include <GameLayer/spritesheet.h>

Image Spritesheet::getSprite(Rectangle spriteRectangle) {
    // Create a new image with just the sprite rectangle's dimensions
    Image sprite = ImageFromImage(spritesheet, spriteRectangle);
    return sprite;
}
void Spritesheet::drawSprite(Vector2 position, Rectangle spriteRectangle,bool flipped) {
    // Scale it up to yxy pixels
    Rectangle dest = { position.x, position.y, 16*6, 16*6 };

    if (flipped) {
        // Make width negative to flip
        spriteRectangle.width = -spriteRectangle.width;
    }

        DrawTexturePro(texture, spriteRectangle, dest, { 16*3,16*3 }, 0.0f, WHITE);
}

Spritesheet::~Spritesheet() {
    UnloadImage(spritesheet);
    UnloadTexture(texture);
}