#pragma once
#include <raylib.h>
#include <iostream>
class Spritesheet {
public:
    Image spritesheet;
    Texture texture;
    bool textureLoaded = false;

    Spritesheet(Image sheet) {
        if (sheet.data == nullptr) {
            std::cout << "Invalid image passed to Spritesheet constructor!" << std::endl;
            return;
        }
        else {
            std::cout << "Valid Image" << std::endl;
        }
        spritesheet = sheet;           
        textureLoaded = false;
        // Can't load the texture here because of some nullptr issue

    }

    void loadTexture();
	Image getSprite(Rectangle);
	void drawSprite(Vector2, Rectangle, int, bool);
	~Spritesheet();
};