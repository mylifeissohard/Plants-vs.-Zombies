#include "Tower.h"

Tower::Tower(int pos_x = 0, int pos_y = 0)
{
    this->circle = new Circle(pos_x, pos_y, 70);
}

Tower::~Tower()
{
    delete circle;

    al_destroy_bitmap(img);
    al_destroy_bitmap(attack_img);

    for(auto&& child : this->attack_set) {
        delete child;
    }
    this->attack_set.clear();
}

void
Tower::Draw()
{
    int draw_x = circle->x - (TowerWidth[this->type]/2);
    int draw_y = circle->y - (TowerHeight[this->type] - (TowerWidth[this->type]/2));


    al_draw_bitmap(img, draw_x, draw_y, 0);

    for(unsigned int i=0; i<this->attack_set.size(); i++)
        this->attack_set[i]->Draw();

    if(isClicked)
    {
        al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
        al_draw_filled_circle(circle->x, circle->y, 2, al_map_rgb(0, 0, 0));
    }
}

void
Tower::SelectedTower(int mouse_x, int mouse_y, int type)
{
    int draw_x = mouse_x - (TowerWidth[type]/2);
    int draw_y = mouse_y - (TowerHeight[type] - (TowerWidth[type]/2));
    char filename[50];
    ALLEGRO_BITMAP *bitmap;

    sprintf(filename, "./Tower/%s.png", TowerClass[type]);
    bitmap = al_load_bitmap(filename);

    al_draw_bitmap(bitmap, draw_x, draw_y, 0);
    al_draw_filled_circle(mouse_x, mouse_y, TowerRadius[type], al_map_rgba(196, 79, 79, 200));
    al_draw_filled_circle(mouse_x, mouse_y, 2, al_map_rgb(0, 0, 0));

    al_destroy_bitmap(bitmap);
}

bool
Tower::DetectAttack(Monster *monster)
{
    bool willAttack = false;
    Attack *attack;

    if(Circle::isOverlap(this->circle, monster->getCircle()))
    {
        if(attack_counter == 0)
        {
            attack = new Attack(
                this->circle,
                monster->getCircle(),
                this->attack_harm_point,
                this->attack_velocity,
                this->attack_img
            );

            this->attack_set.push_back(attack);
        }
         willAttack = true;

        attack_counter = (attack_counter + 1) % attack_frequency;
    }

    return willAttack;
}

bool
Tower::TriggerAttack(Monster *monster)
{
    bool isDestroyed = false;

    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), monster->getCircle()))
        {

            /*TODO:*/
            /*1. Reduce the monster HP by the harm point*/
            /*2. Erase and delete the attack from attack set*/
            /*3. Return true if the monster's HP is reduced to zero*/
            /*isDestroyed = monster->Subtract_HP(attack_set[i]->getHarmPoint());
            attack_set.erase(attack_set.begin()+i);
            i--;
            if(isDestroyed) return true;*/

                if(monster->Subtract_HP(attack_set[i]->getHarmPoint())){
                    return 1;
                    attack_set.erase(attack_set.begin()+i);
                    i--;
                }
        }
    }
    return false;
}

void
Tower::UpdateAttack()
{
    for(unsigned int i=0; i < this->attack_set.size(); i++)
    {
        if(!Circle::isOverlap(this->attack_set[i]->getCircle(), this->circle))
        {
            Attack *attack = this->attack_set[i];

            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete attack;
        }
    }
}
