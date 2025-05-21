#include <GameLayer/healthbar.h>
#include <iostream>
void HealthBar::draw(int health) {
    float length[4] = {0, 33, 65, 98 };
    int bars = health  <0 ? 0: health;

    float x = 20;
    float y = 20;

    float scale = 1.5;
    DrawTextureEx(emptyBar, {x,y}, 0 ,scale,WHITE);

    Rectangle source = { 0, 0, length[bars], 16};
    Rectangle dest = {x, y, length[bars]* scale, 16* scale };

    DrawTexturePro(fullBar, source, dest, { 0, 0 }, 0.0f, WHITE);
}

