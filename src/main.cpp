#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

#pragma region GameLayer
#include <GameLayer/tiledRenderer.h>
#include <GameLayer/spritesheet.h>
#include <GameLayer/character.h>
#include <GameLayer/enemy.h>
#include <GameLayer/bullet.h>
#pragma endregion

struct GameplayData {
	float spawnTimer = 0.0f;
	float spawnInterval = 10.0f;

	Vector2 playerPosition = { 100,100 };

	std::vector<Bullet> bullets;

	std::vector<Enemy> enemys;

};

TiledRenderer tiledRenderer;
GameplayData data;


constexpr int screenWidth = 1200;
constexpr int screenHeight = 1200;
void UpdatePlayer(int&, float);


int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TD Shooter");
	double elaspedTime = GetTime();
	SetTargetFPS(60);

#pragma region spriteTexture 
	// Load the sprite sheet image
	constexpr int spriteWidth = 16;
	constexpr int spriteHeight = 16;
	// Orientation 0 Right, 1 Down, 2 Up, 3 Left
	int orientation = 0;
	Image spriteBundle = LoadImage(RESOURCES_PATH "/walk.png");
	Spritesheet walkSprite(spriteBundle);

	Image spriteWeapon{ LoadImage(RESOURCES_PATH "Gun.png") };
	Texture spriteWeaponText{ LoadTextureFromImage(spriteWeapon) };




#pragma endregion 

#pragma region enemyTexture
	Image enemyBundle = LoadImage(RESOURCES_PATH "goblin_walk.png");
	Spritesheet enemySheet(enemyBundle);

#pragma endregion

#pragma region bullet
	Texture bulletTexture{ LoadTexture(RESOURCES_PATH "bullet.png") };

#pragma endregion
	Texture cursorTexture{ LoadTexture(RESOURCES_PATH "cursor.png") };
	HideCursor();
#pragma region camera 
	Camera2D camera{ 0 };
	camera.offset = { screenWidth / 2, screenHeight / 2 };
	camera.zoom = 1.0f;
#pragma endregion
	Vector2 mousePosition{ 0,0 };
	Vector2 screenCenter{ screenWidth / 2.f, screenHeight / 2.f };
#pragma region textureBG
	tiledRenderer.texture = LoadTexture(RESOURCES_PATH "TD_Shooter_BG.png");
#pragma endregion	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		float deltaTime = GetFrameTime();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		UpdatePlayer(orientation, deltaTime);


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


#pragma region mousePos

		mousePosition = GetMousePosition();

		Vector2 mouseDirection{ Vector2Subtract(mousePosition,  screenCenter) };
		if (Vector2Length(mouseDirection) == 0.f) {
			mouseDirection = { 1,0 };
		}
		else {
			mouseDirection = Vector2Normalize(mouseDirection);
		}
		// Get the angle in radians of the mouse to the middle of screen 
		float mouseAngle = atan2(mouseDirection.y, mouseDirection.x);
		// No need to make negative since raylib has positive 90 facing down
		// Place gun around the player using formula xcos(x) ysin(y)
		DrawTexturePro(spriteWeaponText, { 12,8,27,16 }, { data.playerPosition.x + cos(mouseAngle) * 64,
			data.playerPosition.y + sin(mouseAngle) * 64, 27 * 3,16 * 3 }, { 13.5,8 }, mouseAngle * RAD2DEG, WHITE);


#pragma endregion



#pragma region handle bullets
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Bullet b;

			b.position = {
		data.playerPosition.x + cos(mouseAngle) * (64 + 80),
		data.playerPosition.y + sin(mouseAngle) * (64 + 80)
			};

			//Normalize vector, getting the mouse position
			b.fireDirection = mouseDirection;
			b.orientation = mouseAngle * RAD2DEG;

			data.bullets.push_back(b);
		}
		for (int i = 0;i < data.bullets.size(); i++) {

			data.bullets[i].draw(bulletTexture);
			data.bullets[i].update(deltaTime);
		}
#pragma endregion

#pragma region handle enemies
		// Spawn enemies every 10 seconds
		std::cout << data.spawnTimer;
		data.spawnTimer += deltaTime;
		if (data.spawnTimer >= data.spawnInterval) {
			Rectangle enemyRect{ 39,24,18,15 };
			Enemy e = Enemy(data.playerPosition, &enemySheet, enemyRect);
			data.enemys.push_back(e);
			data.spawnTimer = 0;
		}
		for (int i = 0; i < data.enemys.size(); i++) {
			data.enemys[i].draw();
			data.enemys[i].update(deltaTime);
		}



#pragma endregion
		EndMode2D();
		DrawTexture(cursorTexture, GetMouseX() - 16, GetMouseY() - 16, WHITE);
		EndDrawing();
	}


	CloseWindow();

	return 0;
}


void UpdatePlayer(int& orientation, float deltaTime) {
	// Get the render time

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