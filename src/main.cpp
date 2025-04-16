#include "raylib.h"
#include "raymath.h"
#include <iostream>

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

#pragma region GameLayer
#include <GameLayer/tiledRenderer.h>
#include <GameLayer/spritesheet.h>
#pragma endregion

struct GameplayData {
	Vector2 playerPosition = { 100,100 };
};

TiledRenderer tiledRenderer;
GameplayData data;


constexpr int screenWidth = 1200;
constexpr int screenHeight = 1200;

void UpdateGame(int&);




int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TD Shooter");
	SetTargetFPS(60);

#pragma region spriteTexture 
	// Load the sprite sheet image
	constexpr int spriteWidth = 16;
	constexpr int spriteHeight = 16;
	// Orientation 0 Right, 1 Down, 2 Up, 3 Left
	int orientation = 0;
	Image spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	Spritesheet walkSprite(spriteBundle);
	walkSprite.loadTexture();



#pragma endregion 

#pragma region camera 
	Camera2D camera{ 0 };
	camera.offset = { screenWidth / 2, screenHeight / 2 };
	camera.zoom = 1.0f;
#pragma endregion

#pragma region textureBG
	tiledRenderer.texture = LoadTexture(RESOURCES_PATH "/TD_Shooter_BG.png");
#pragma endregion	
	while (!WindowShouldClose())
	{
		BeginDrawing();


		ClearBackground(BLACK);
		BeginMode2D(camera);
		UpdateGame(orientation);


		tiledRenderer.draw(camera);

		camera.target = data.playerPosition;
		if (orientation == 0) {
			walkSprite.drawSprite(data.playerPosition, { 32,32,spriteWidth,spriteHeight }, 0, false);
		}
		else if (orientation == 1) {

			walkSprite.drawSprite(data.playerPosition, { 32,112,spriteWidth,spriteHeight }, 0, false);
		}
		else if (orientation == 2) {

			walkSprite.drawSprite(data.playerPosition, { 32,192,spriteWidth,spriteHeight }, 0, false);
		}
		else if (orientation == 3) {

			walkSprite.drawSprite(data.playerPosition, { 32,32,spriteWidth,spriteHeight }, 0, true);
		}
		EndMode2D();
		EndDrawing();
	}

		CloseWindow();

		return 0;
	}


void UpdateGame(int& orientation){
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
		move = Vector2Scale(move, deltaTime * 400);
		data.playerPosition = Vector2Add(data.playerPosition, move);
		if (move.y < 0) {
			orientation = 2;

		}
		if (move.y > 0) {
			orientation = 1;
		}
		if (move.x > 0) {
			orientation = 0;
		}
		if (move.x < 0) {
			orientation = 3;
		}

	}

#pragma endregion
}
