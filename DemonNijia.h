#ifndef EAGLE_H_INCLUDED
#define EAGLE_H_INCLUDED

#include "Monster.h"

class DemonNijia : public Monster
{
public:
    DemonNijia(std::vector<int> path) : Monster(path)
    {
        direction_count[LEFT] = 4;
        direction_count[RIGHT] = 4;
        direction_count[UP] = 4;
        direction_count[DOWN] = 4;

        HealthPoint = 100;
        speed = 4;
        worth = 20;
        score = 150;

        strncpy(class_name, "DemonNijia", 20);

        Load_Move();
    }
};

#endif // EAGLE_H_INCLUDED
