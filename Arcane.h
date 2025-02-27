#ifndef ARCANE_H_INCLUDED
#define ARCANE_H_INCLUDED

#include "Tower.h"

class Arcane : public Tower
{
public:
    Arcane(int mouse_x, int mouse_y) : Tower(mouse_x, mouse_y)
    {
        type = ARCANE;

        circle->r = 80;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./Tower/Arcane.png");
        attack_img = al_load_bitmap("./Tower/Arcane_Beam.png");
    }

    int getWidth() override { return TowerWidth[ARCANE]; }
    int getHeight() override { return TowerHeight[ARCANE]; }

};

#endif // ARCANE_H_INCLUDED
