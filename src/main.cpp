#include "raylib.h"
#include "raymath.h"
#include <iostream>

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

struct GameplayData {
	Vector2 playerPosition = { 100,100 };
};
GameplayData data;
constexpr int screenWidth = 1200;
constexpr int screenHeight = 1200;

void UpdateGame(int&);
int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TD Shooter");
	SetTargetFPS(60);

#pragma region textureSprite
	// Load the sprite sheet image
	Image spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	const float spriteWidth = spriteBundle.width / 8;
	const float spriteHeight = spriteBundle.height / 3;

	// Orientation 0 Right, 1 Down, 2 Up, 3 Left
	int orientation = 0;

	// Crop the sprite for the right direction (Orientation 0)
	Rectangle cropSpaceRight = { 0, 0, spriteWidth, spriteHeight };
	ImageCrop(&spriteBundle, cropSpaceRight);
	Texture2D rightSprite = LoadTextureFromImage(spriteBundle);
	UnloadImage(spriteBundle); // Unload after creating the texture for right orientation

	// Reload the sprite sheet and crop for the down direction (Orientation 1)
	spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	Rectangle cropSpaceDown = { 0, 1 * spriteHeight, spriteWidth, spriteHeight };
	ImageCrop(&spriteBundle, cropSpaceDown);
	Texture2D downSprite = LoadTextureFromImage(spriteBundle);
	UnloadImage(spriteBundle); // Unload after creating the texture for down orientation

	// Reload the sprite sheet and crop for the up direction (Orientation 2)
	spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	Rectangle cropSpaceUp = { 0, 2 * spriteHeight, spriteWidth, spriteHeight };
	ImageCrop(&spriteBundle, cropSpaceUp);
	Texture2D upSprite = LoadTextureFromImage(spriteBundle);
	UnloadImage(spriteBundle); // Unload after creating the texture for up orientation

	// Reload the sprite sheet and crop for the left direction (Orientation 3)
	spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	Rectangle cropSpaceLeft = { 0, 0, spriteWidth, spriteHeight };
	ImageCrop(&spriteBundle, cropSpaceLeft);
	ImageFlipHorizontal(&spriteBundle); // Flip the sprite vertically for the left orientation
	Texture2D leftSprite = LoadTextureFromImage(spriteBundle);
	UnloadImage(spriteBundle); // Unload after creating the texture for left orientation

#pragma endregion


#pragma region textureBG
	Texture background = LoadTexture(RESOURCES_PATH "/TD_Shooter_BG.png");
#pragma endregion	
	while (!WindowShouldClose())
	{
		UpdateGame(orientation);
		BeginDrawing();
		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);
		if (orientation == 0) {
			DrawTextureEx(rightSprite, data.playerPosition, 0, 6, WHITE);
		}
		else if (orientation == 1) {
			DrawTextureEx(downSprite, data.playerPosition, 0, 6, WHITE);
		}
		else if (orientation == 2) {
			DrawTextureEx(upSprite, data.playerPosition, 0, 6, WHITE);
		}
		else if (orientation == 3) {
			DrawTextureEx(leftSprite, data.playerPosition, 0, 6, WHITE);
		}
		EndDrawing();


	}

	CloseWindow();

	return 0;
}


void UpdateGame(int& orientation) {
	// Get the render time
	float deltaTime = GetFrameTime();
#pragma region movement
	Vector2 move = {};

	if (IsKeyDown(KEY_W)) {
		move.y = { -1 };
	}
	if (IsKeyDown(KEY_S)) {
		move.y = { 1 };
	}
	if (IsKeyDown(KEY_A)) {
		move.x = { -1 };
	}
	if (IsKeyDown(KEY_D)) {
		move.x = { 1 };
	}

	if (move.x != 0 || move.y != 0) {
		// Make sure 1 unit is being moved
		move = Vector2Normalize(move);
		// Our velo, just distance/time 
		move = Vector2Scale(move, deltaTime * 200);
		data.playerPosition = Vector2Add(data.playerPosition, move);
		if (move.y < 0) {
			orientation = 2;
			
		}
		if (move.y > 0) {
			orientation = 1;
		}
		if (move.x > 0 ) {
			orientation = 0;
		}
		if (move.x <  0) {
			orientation = 3;
		}

	}

#pragma endregion
}
