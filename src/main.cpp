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
#include <GameLayer/healthbar.h>
#pragma endregion

struct GameplayData {
	enum Gameplay {PLAYING, GAMEOVER};
	Gameplay state = PLAYING;
	float spawnTimer = 10.0f;
	float spawnInterval = 10.0f;

	Vector2 playerPosition = { 100,100 };
	const int maxHealth = 3;
	int health = 3;
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
	Vector2 mousePosition{ 0,0 };
	Vector2 screenCenter{ screenWidth / 2.f, screenHeight / 2.f };
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TD Shooter");
	double elaspedTime = GetTime();
	SetTargetFPS(60);

#pragma region healthbar
	Image emptybar{ LoadImage(RESOURCES_PATH "empty_bar.png") };
	Image fullbar{ LoadImage(RESOURCES_PATH "full_health_bar.png") };
	Texture emptyBarText{ LoadTextureFromImage(emptybar) };
	Texture fullBarText{ LoadTextureFromImage(fullbar) };
	UnloadImage(emptybar);
	UnloadImage(fullbar);
	HealthBar healthbar(emptyBarText, fullBarText);
#pragma endregion

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
	Rectangle enemyRect{ 39,24,18,15 };
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


		camera.target = data.playerPosition;
		tiledRenderer.draw(camera);

		Rectangle userRect = { data.playerPosition.x - 16 * 6 / 2,
	data.playerPosition.y - 16 * 6 / 2,16*6, 16*6};
		// DrawRectangle(userRect.x, userRect.y, userRect.width, userRect.height, RED);
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
		DrawTexturePro(spriteWeaponText, { 12,8,27,16 }, { data.playerPosition.x + cos(mouseAngle) * 32,
			data.playerPosition.y + sin(mouseAngle) * 32, 27 * 3,16 * 3 }, { 13.5,8 }, mouseAngle * RAD2DEG, WHITE);


#pragma endregion


#pragma region handle enemies
		// Spawn enemies every 10 seconds
		data.spawnTimer += deltaTime;
		Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, camera);
		// Need to find what tile player is on
		int tileX = static_cast<int>(floor(data.playerPosition.x / 1200));
		int tileY = static_cast<int>(floor(data.playerPosition.y / 1200));
		if (data.spawnTimer >= data.spawnInterval) {

			float randomX = GetRandomValue(-600, 600) + tileX + enemyRect.width;
			float randomY = GetRandomValue(-600, 600) + tileY + enemyRect.height;
			std::cout << "Enemy spawned at " << randomX << randomY;
			Enemy e = Enemy({ randomX, randomY }, &enemySheet, enemyRect);
			data.enemys.push_back(e);
			data.spawnTimer = 0;
		}
		for (int i = 0; i < data.enemys.size(); i++) {
			Enemy& enemy = data.enemys[i];
			Rectangle enemyColRect = {
				enemy.position.x,
				enemy.position.y,
				enemyRect.width,
				enemyRect.height
			};

			enemy.draw();


			if (CheckCollisionRecs(userRect, enemyColRect)) {
				data.health -= 1;
				enemy.update(deltaTime, data.playerPosition, true);
			}
			else {
				enemy.update(deltaTime, data.playerPosition, false);
			}
		}




#pragma endregion

#pragma region handle bullets
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				Bullet b;

				b.position = {
			data.playerPosition.x + cos(mouseAngle) ,
			data.playerPosition.y + sin(mouseAngle) };

				//Normalize vector, getting the mouse position
				b.fireDirection = mouseDirection;
				b.orientation = mouseAngle * RAD2DEG;

				data.bullets.push_back(b);
			}
			for (int i = 0; i < data.bullets.size(); i++) {
				Bullet& bullet = data.bullets[i];
				bullet.draw(bulletTexture);
				bullet.update(deltaTime);

				for (int j = 0; j < data.enemys.size(); j++) {
					Enemy& enemy = data.enemys[j];

					Rectangle bulletRect = { bullet.position.x, bullet.position.y, 32,24 };
					Rectangle enemyColRect = { enemy.position.x, enemy.position.y, enemyRect.width, enemyRect.height };

					if (CheckCollisionRecs(bulletRect, enemyColRect)) {

						data.enemys.erase(data.enemys.begin() + j);
						j--;
						data.bullets.erase(data.bullets.begin() + i);
						i--;
						break;
					}
				}
			}

#pragma endregion

			EndMode2D();


			// Draw UI stuff in screen space after camera ends
			healthbar.draw(data.health);
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