#pragma once
#include <raylib.h>
class HealthBar {
public: 
	Texture emptyBar;
	Texture fullBar;
	HealthBar(Texture emptyBar, Texture fullBar) {
		this->emptyBar = emptyBar;
		this->fullBar = fullBar;
	}
	void draw(int);
};