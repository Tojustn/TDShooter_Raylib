#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>
#include <cstdint>
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
#include <GameLayer/user.h>
#pragma endregion

const enum Gameplay { STARTING, PLAYING, GAMEOVER };
struct GameplayData {
	Gameplay state = STARTING;
	int score{ 0 };

	User* user = nullptr;

	std::vector<Bullet> bullets;

	std::vector<Enemy> enemys;

	std::uint8_t wave{ 1 };
	int enemiesPerWave{ wave * 3 };
	bool waveChange{ true };
	float waveTextTimer{};

	const char* nextWaveText = TextFormat("Next Wave!");


};

TiledRenderer tiledRenderer;
GameplayData data;


constexpr int screenWidth = 1200;
constexpr int screenHeight = 1200;


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

	data.user = new User(&walkSprite, 3);

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

#pragma region textureBG
	tiledRenderer.texture = LoadTexture(RESOURCES_PATH "TD_Shooter_BG.png");
#pragma endregion	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		if (data.state == STARTING) {

			int fontSize = 100;
			// Strings are stored as  char* pointer to the first element
			const char* welcomeText = "WELCOME";
			int textWidth = MeasureText(welcomeText, fontSize);
			int centerX = screenWidth / 2 - textWidth / 2;

			ClearBackground(GREEN);
			DrawText(welcomeText, centerX, 200, 100, DARKGREEN);


			Rectangle startRec = { 300,700,600,200 };

			DrawRectangleRec(startRec, DARKGREEN);

			const char* startText = "START";
			textWidth = MeasureText(startText, fontSize);
			centerX = screenWidth / 2 - textWidth / 2;
			DrawText(startText, centerX, 750, 100, GREEN);

			Vector2 mousePosition = GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, startRec)) {
				data.state = PLAYING;
			}
			DrawTexture(cursorTexture, GetMouseX() - 16, GetMouseY() - 16, WHITE);
		}
		else if (data.state == PLAYING) {
			float deltaTime = GetFrameTime();
			ClearBackground(BLACK);
			BeginMode2D(camera);
			data.user->update(deltaTime);


			camera.target = data.user->position;
			tiledRenderer.draw(camera);

			Rectangle userRect = { data.user->position.x - 16 * 6 / 2,
		 data.user->position.y - 16 * 6 / 2,16 * 6, 16 * 6 };
			// DrawRectangle(userRect.x, userRect.y, userRect.width, userRect.height, RED);
			data.user->draw();


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
			DrawTexturePro(spriteWeaponText, { 12,8,27,16 }, { data.user->position.x + cos(mouseAngle) * 32,
				 data.user->position.y + sin(mouseAngle) * 32, 27 * 3,16 * 3 }, { 13.5,8 }, mouseAngle * RAD2DEG, WHITE);


#pragma endregion


#pragma region handle enemies
			Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, camera);
			// Need to find what tile player is on
			int tileX = static_cast<int>(floor(data.user->position.x / screenWidth));
			int tileY = static_cast<int>(floor(data.user->position.y / screenHeight));
			float baseX = tileX * 1200;
			float baseY = tileY * 1200;

			int spawnNum = data.enemiesPerWave;

			if (data.waveChange) {
				for (int i = 0; i < spawnNum; i++) {
					int side = GetRandomValue(0, 3);

					float randomX, randomY;

					switch (side) {
					case 0: // Right side
						randomX = baseX + screenWidth + GetRandomValue(0, 200);
						randomY = baseY + GetRandomValue(-screenHeight / 2, screenHeight / 2);
						break;
					case 1: // Bottom side
						randomX = baseX + GetRandomValue(-screenWidth / 2, screenWidth / 2);
						randomY = baseY + screenHeight + GetRandomValue(0, 200);
						break;
					case 2: // Left side
						randomX = baseX - screenWidth - GetRandomValue(0, 200);
						randomY = baseY + GetRandomValue(-screenHeight / 2, screenHeight / 2);
						break;
					case 3: // Top side
						randomX = baseX + GetRandomValue(-screenWidth / 2, screenWidth / 2);
						randomY = baseY - screenHeight - GetRandomValue(0, 200);
						break;
					}

					Enemy e({ randomX, randomY }, &enemySheet);
					data.enemys.push_back(e);
				}
				data.waveChange = false;
			}

			if (data.enemys.size() <= 0) {
				data.wave++;
				data.waveChange = true;
				data.waveTextTimer = 1.0f;
			
			}
						

			for (int i = 0; i < data.enemys.size(); i++) {
				Enemy& enemy = data.enemys[i];
				Rectangle enemyColRect = {
					enemy.position.x - enemy.frameWidth / 2 * 6,
					enemy.position.y - enemy.frameHeight / 2 * 6,
					enemy.frameWidth * 6,
					enemy.frameHeight * 6
				};
				//DrawRectangleRec(enemyColRect, RED);
				enemy.draw();


				// DrawRectangleRec(enemyColRect, RED);
				if (CheckCollisionRecs(userRect, enemyColRect)) {
					data.user->health -= 1;
					enemy.update(deltaTime, data.user->position, true);
					if (data.user->health <= 0) {
						data.state = GAMEOVER;
					}
				}
				else {
					enemy.update(deltaTime, data.user->position, false);
				}
			}




#pragma endregion

#pragma region handle bullets
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				Bullet b;

				b.position = {
			 data.user->position.x + cos(mouseAngle) ,
			 data.user->position.y + sin(mouseAngle) };

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

					float bulletWidth = 32;
					float bulletHeight = 24;

					Rectangle bulletRect = {
						bullet.position.x - bulletWidth / 2,
						bullet.position.y - bulletHeight / 2,
						bulletWidth,
						bulletHeight
					};
					Rectangle enemyColRect = { enemy.position.x, enemy.position.y,enemy.frameWidth, enemy.frameHeight };

					// DrawRectangleRec(bulletRect, RED);
					if (CheckCollisionRecs(bulletRect, enemyColRect)) {
						data.score += 1;

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
			healthbar.draw(data.user->health);
			DrawTexture(cursorTexture, GetMouseX() - 16, GetMouseY() - 16, WHITE);
			DrawText(TextFormat("Score: %d", data.score), 900, 25, 50, WHITE);

			constexpr int waveTextSize = 20;
			constexpr int waveTextPadding = 20;

			std::string waveText = TextFormat("Wave: %i", data.wave);

			int textWidth = MeasureText(waveText.c_str(), waveTextSize);

			DrawText(
				waveText.c_str(),
				screenWidth - textWidth - waveTextPadding,
				screenHeight - waveTextSize - waveTextPadding,
				waveTextSize,
				WHITE
			);

			if (data.waveTextTimer > 0.0f) {
				int fontSize = 100;
				int textWidth = MeasureText(data.nextWaveText, fontSize);
				int centerX = screenWidth / 2 - textWidth / 2;
				int centerY = screenHeight / 2 - fontSize / 2;
				DrawText(data.nextWaveText, centerX, centerY, fontSize, WHITE);
				data.waveTextTimer -= deltaTime;
				if (data.waveTextTimer < 0.0f) data.waveTextTimer = 0.0f;
			}
		}
		else if (data.state == GAMEOVER) {

			int fontSize = 100;
			// Strings are stored as  char* pointer to the first element
			const char* gameOverText = "Game Over";
			int textWidth = MeasureText(gameOverText, fontSize);
			int centerX = screenWidth / 2 - textWidth / 2;

			ClearBackground(GREEN);
			DrawText(gameOverText, centerX, 200, 100, DARKGREEN);


			Rectangle restartRec = { 300,700,600,200 };

			DrawRectangleRec(restartRec, DARKGREEN);

			const char* scoreText = TextFormat("Score: %d", data.score);

			// Get width of the text in pixels
			textWidth = MeasureText(scoreText, fontSize);

			// Calculate center position
			int x = (GetScreenWidth() / 2) - (textWidth / 2);
			int y = 25;

			DrawText(scoreText, x, y, fontSize, WHITE);



			const char* restartText = "Restart";
			textWidth = MeasureText(restartText, fontSize);
			centerX = screenWidth / 2 - textWidth / 2;
			DrawText("Restart", centerX, 750, 100, GREEN);

			Vector2 mousePosition = GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, restartRec)) {
				data.state = PLAYING;
				data.user->position = { 100, 100 };
				data.wave = 1;
				data.score = 0;
				data.user->health = data.user->maxHealth;
				data.bullets.clear();
				data.enemys.clear();
			}
			DrawTexture(cursorTexture, GetMouseX() - 16, GetMouseY() - 16, WHITE);
		}
		EndDrawing();
	}


	CloseWindow();

	return 0;
}

