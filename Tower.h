#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Attack.h"
#include "Circle.h"
#include "Monster.h"
#include "global.h"

class Tower : public Object
{
public:
    Tower(int, int);
    virtual ~Tower();

    // override virtual function "Object::Draw"
    void Draw();
    void resetAttackCounter() { attack_counter = 0; }
    void ToggleClicked() { isClicked = !isClicked; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    void UpdateAttack();
    // detect if tower needs to attack some monster
    bool DetectAttack(Monster*);
    // process if some of attack in set touches monster
    bool TriggerAttack(Monster*);

    virtual int getWidth() { return 40; }
    virtual int getHeight() { return 40; }

    // show selected tower image on cursor position
    static void SelectedTower(int, int, int);

    int attack_harm_point=5;//зя

protected:
    // setting of attack
    int attack_frequency = 20;
    int attack_counter = 0;

    int attack_velocity = 10;
    ALLEGRO_BITMAP *attack_img;
    std::vector<Attack*> attack_set;
    std::vector<ALLEGRO_BITMAP*> moveplante;

    // information of tower
    int type;
    bool isClicked = false;
    ALLEGRO_BITMAP *img;
};

#endif








