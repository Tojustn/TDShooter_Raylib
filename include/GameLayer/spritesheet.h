#pragma once
#include <raylib.h>
#include <iostream>
class Spritesheet {
public:
    Image spritesheet;
    Texture texture;

    Spritesheet(Image sheet) {
        if (sheet.data == nullptr) {
            std::cout << "Invalid image passed to Spritesheet constructor!" << std::endl;
            return;
        }
        else {
            std::cout << "Valid Image" << std::endl;
        }
        spritesheet = sheet;           
        texture = LoadTextureFromImage(spritesheet);

    }

	Image getSprite(Rectangle);
	void drawSprite(Vector2, Rectangle, int, bool);
	~Spritesheet();
};