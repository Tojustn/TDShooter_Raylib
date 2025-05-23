#include <GameLayer/user.h>
#include <raylib.h>
#include <raymath.h>
void User::draw() {

	Rectangle userRect{
		(frame - 1) * frameSpace,
		(frameY - 1) * frameYSpace,
		frameWidth,
		frameHeight
	};

	sheet->drawSprite(position, userRect, flipped);
}

void User::update(float deltaTime) {
#pragma region animation
	animationTimer += deltaTime;
	if (animationTimer >= animationInterval) {
		animationTimer = 0.0f;
		frame++;
		if (frame > maxFrames) frame = 1;
	}
#pragma endregion
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
		position = Vector2Add(position, move);
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
	switch (orientation) {
	case 0:  // Right
		frameY = 1;
		flipped = false;
		break;
	case 1:  // Down
		frameY = 2;
		flipped = false;
		break;
	case 2:  // Up
		frameY = 3;
		flipped = false;
		break;
	case 3:  // Left
		frameY = 1;
		flipped = true;
		break;


	}
#pragma endregion
};
