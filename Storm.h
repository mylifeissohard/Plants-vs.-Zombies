#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#include "Tower.h"

class Storm : public Tower
{
public:
    Storm(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = STORM;

        circle->r = 150;
        attack_frequency = 5;
        attack_velocity = 20;
        attack_harm_point = 5;
        img = al_load_bitmap("./Tower/Storm.png");
        attack_img = al_load_bitmap("./Tower/Storm_Beam.png");
    }

    int getWidth() override { return TowerWidth[STORM]; }
    int getHeight() override { return TowerHeight[STORM]; }
};

#endif // STORM_H_INCLUDED
