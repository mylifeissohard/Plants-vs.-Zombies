#ifndef BLACKDRAGON_H_INCLUDED
#define BLACKDRAGON_H_INCLUDED

#include "Monster.h"

class CaveMan : public Monster
{
public:
    CaveMan(std::vector<int> path) : Monster(path)
    {
        //moveImg[0] = al_load_bitmap("./CaveMan/LEFT_0.png");  // LEFT
        //moveImg[1] = al_load_bitmap("./CaveMan/RIGHT_0.png"); // RIGHT
        //moveImg[2] = al_load_bitmap("./CaveMan/UP_0.png");    // UP
        //moveImg[3] = al_load_bitmap("./CaveMan/DOWN_0.png");  // DOWN

        direction_count[LEFT] = 4;
        direction_count[RIGHT] = 4;
        direction_count[UP] = 4;
        direction_count[DOWN] = 4;

        HealthPoint = 200;
        speed = 2;
        worth = 30;
        score = 500;

        strncpy(class_name, "CaveMan", 20);

        Load_Move();
    }
};


#endif // BLACKDRAGON_H_INCLUDED
