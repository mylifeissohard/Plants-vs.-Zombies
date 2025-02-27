#ifndef REDDRAGON_H_INCLUDED
#define REDDRAGON_H_INCLUDED

#include "Monster.h"

class WolfKnight : public Monster
{
public:
    WolfKnight(std::vector<int> path) : Monster(path)
    {
        direction_count[LEFT] = 4;
        direction_count[RIGHT] = 4;
        direction_count[UP] = 4;
        direction_count[DOWN] = 4;

        HealthPoint = 40;
        speed = 2;
        worth = 10;
        score = 250;

        strncpy(class_name, "WolfKnight", 20);

        Load_Move();
    }

};
#endif // REDDRAGON_H_INCLUDED
