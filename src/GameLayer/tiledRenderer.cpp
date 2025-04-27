#include <raylib.h>
#include <raymath.h>
#include <GameLayer/tiledRenderer.h>
#include <iostream>

void TiledRenderer::draw(Camera2D& camera) {
    // Get position of screen relative to world coords
    Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, camera);

    int baseTileX = static_cast<int>(floor(topLeft.x / backgroundSize));
    int baseTileY = static_cast<int>(floor(topLeft.y / backgroundSize));

    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            Vector2 tilePos = {
                (baseTileX + x) * backgroundSize,
                (baseTileY + y) * backgroundSize
            };

            // Draw texture based on what tile the user is on
            DrawTextureV(texture, tilePos, WHITE);
        }
    }
}
