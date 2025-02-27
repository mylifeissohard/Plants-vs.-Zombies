#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"



class Sun: public Object {
public:
    Sun(std::vector<int> path);
    virtual ~Sun();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool Move();

    // functions that return informations of monster
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

   // bool Subtract_HP(int);
    int Increase_HP(int);
    void ToggleClicked() { isClicked = !isClicked; }
    virtual int getWidth() { return 40; }
    virtual int getHeight() { return 40; }
    // show selected tower image on cursor position
    static void SelectedSun(int, int);

protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
private:
    // direction and index for "path"
    unsigned int step;
    int direction;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;
    bool isClicked = false;
    ALLEGRO_BITMAP *img;

};















enum {LEFT=0, RIGHT, UP, DOWN};

class Monster: public Object {
public:
    Monster(std::vector<int> path);
    virtual ~Monster();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool Move();

    // functions that return informations of monster
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

    bool Subtract_HP(int);
    //int notFrozen = 1;
    int hurtNumber(int);

protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
private:
    // direction and index for "path"
    unsigned int step;
    int direction;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;

};


#endif // MONSTER_H_INCLUDED



















