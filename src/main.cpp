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
constexpr int screenHeight = 800;

void UpdateGame();
int main(void)
{
	// Checks the last time the snake has moved
	bool showImGUI = true;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TD Shooter");
	SetTargetFPS(60);

	// Get a single sprite fron the bundle
	Image spriteBundle = LoadImage(RESOURCES_PATH "/idle.png");
	const float spriteWidth = spriteBundle.width /4;
	const float spriteHeight = spriteBundle.height/3;
	Rectangle cropSpace = { 0,0,spriteWidth,spriteHeight };
	ImageCrop(&spriteBundle, cropSpace);
	Texture2D spriteTexture = LoadTextureFromImage(spriteBundle);
	// Unload image to save memory
	UnloadImage(spriteBundle);
	while (!WindowShouldClose())
	{
		UpdateGame();

		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangle(100,100,100,100,WHITE);
		DrawTextureEx(spriteTexture, data.playerPosition,0,6,WHITE);
		EndDrawing();


	}

	CloseWindow();

	return 0;
}


void UpdateGame() {
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
		move.x= { -1 };
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
		}
	
#pragma endregion
}
