#pragma once
#include <raylib.h>
#include <iostream>
class Spritesheet {
public:
	Image spritesheet{ 0 };
	Texture texture{ 0 };

	Spritesheet(Image sheet) {
		if (sheet.data == nullptr) {
			std::cout << "Invalid image passed to Spritesheet constructor!" << std::endl;
			return;
		}
		else {
			std::cout << RESOURCES_PATH;
			std::cout << "Valid Image" << std::endl;
		}
		spritesheet = sheet;
		texture = LoadTextureFromImage(spritesheet);
	}
	Spritesheet() {

	}

	Image getSprite(Rectangle);
	void drawSprite(Vector2, Rectangle, bool);
	~Spritesheet();
};