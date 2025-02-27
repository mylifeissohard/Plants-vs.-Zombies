#include "Attack.h"

const int Velocity[] = {8, 8, 6, 10, 20};
const int Harm[] = {5, 7, 15, 3, 5};

Attack::Attack(Circle *created_circle, Circle *target_circle, int harm_point, int velocity, ALLEGRO_BITMAP* attack_img)
{
    float vector_x = created_circle->x;
    float vector_y = created_circle->y;
    float len = sqrt(vector_x * vector_x + vector_y * vector_y);

    // initialize the information of attack
    this->pos_x = created_circle->x;
    this->pos_y = created_circle->y;
    this->circle = new Circle(created_circle->x, created_circle->y, 10);

    //this->direction_x = vector_x/ len;
    //this->direction_y = vector_y/ len;

    this->attack_velocity = velocity;
    this->harm_point = harm_point;
    this->attack_img = attack_img;

    // initialize the effect sound of attack
    sample = al_load_sample("Arrow.wav");
    arrow = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(arrow, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(arrow, al_get_default_mixer());
    al_set_sample_instance_gain(arrow, Attack::volume);
   // al_play_sample_instance(arrow);
}

Attack::~Attack()
{
    delete circle;
    al_destroy_sample_instance(arrow);
    al_destroy_sample(sample);
}

void
Attack::Draw()
{
    al_draw_bitmap(attack_img, pos_x - circle->r, pos_y , 0);
    pos_x += attack_velocity;// * direction_x;
    //pos_y += attack_velocity ;//* direction_y;

    circle->x = (int)pos_x;
    circle->y = (int)pos_y;

    //al_draw_filled_circle(pos_x, pos_y, circle->r, al_map_rgba(196, 79, 79, 200));
}
