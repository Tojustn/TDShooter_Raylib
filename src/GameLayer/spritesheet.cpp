#include <raylib.h>
#include <GameLayer/spritesheet.h>

void Spritesheet::loadTexture() {
    if (!textureLoaded) {
        texture = LoadTextureFromImage(spritesheet);
        textureLoaded = true;
    }
}
Image Spritesheet::getSprite(Rectangle spriteRectangle) {
    // Create a new image with just the sprite rectangle's dimensions
    Image sprite = ImageFromImage(spritesheet, spriteRectangle);
    return sprite;
}
void Spritesheet::drawSprite(Vector2 position, Rectangle spriteRectangle, int frame, bool flipped) {
    
    if (!textureLoaded) {
        loadTexture();
    }

    // Scale it up to yxy pixels
    Rectangle dest = { position.x, position.y, 128, 128 };

    if (flipped) {
        // Make width negative to flip
        spriteRectangle.width = -spriteRectangle.width;
    }

        DrawTexturePro(texture, spriteRectangle, dest, { 64,64 }, 0.0f, WHITE);
}

Spritesheet::~Spritesheet() {
    if (textureLoaded) {
        UnloadTexture(texture);
    }
    UnloadImage(spritesheet);
}