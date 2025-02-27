#ifndef POISON_H_INCLUDED
#define POISON_H_INCLUDED

#include "Tower.h"

class Poison : public Tower
{
public:
    Poison(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = POISON;

        circle->r = 110;
        attack_frequency = 50;
        attack_velocity = 10;
        attack_harm_point = 3;
        img = al_load_bitmap("./Tower/Poison.png");
        attack_img = al_load_bitmap("./Tower/Poison_Beam.png");
    }

    int getWidth() override { return TowerWidth[POISON]; }
    int getHeight() override { return TowerHeight[POISON]; }
};

#endif // POISON_H_INCLUDED
