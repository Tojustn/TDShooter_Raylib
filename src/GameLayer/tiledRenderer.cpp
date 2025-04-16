#include <raylib.h>
#include <GameLayer/tiledRenderer.h>
#include <iostream>

void TiledRenderer::draw(Camera2D& camera) {

	// Draw a rectangle of what the camera sees
	
    Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, camera);

    // Calculate the base position for background tiles (camera position snapped to grid)
    // Positions based on camera, if left then floor() = -1 
    float baseX = std::floor(topLeft.x / backgroundSize) * backgroundSize;
    float baseY = std::floor(topLeft.y / backgroundSize) * backgroundSize;

    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            // Calculate position for this tile
            // Takes the current position (baseX) then positions the 9 tiles using the background size and x or y
            float posX = baseX + (x * backgroundSize);
            float posY = baseY + (y * backgroundSize);

            // Draw the background tile
            DrawTextureV(texture, { posX, posY }, WHITE);
        }
    }
}