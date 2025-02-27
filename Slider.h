#ifndef SLIDER_H_INCLUDED
#define SLIDER_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"

class Slider : public Object
{
public:
    Slider(int, int);
    ~Slider();

    void Draw();
    void set_color(ALLEGRO_COLOR);
    void set_label_content(const char*);
    void toggleDrag() { dragged = !dragged; }

    float Drag(int, int);
    float getDegree() { return degree; }

    int getLength() { return lengthOftrack; }

    bool isClicked(int, int);
    bool isDragged() { return dragged; }

private:
    int target_x, target_y;
    int track_x, track_y;
    int lengthOftrack = 200;
    float degree = 1.0;
    bool dragged = false;
    char label[20];
    ALLEGRO_COLOR target_color;
    ALLEGRO_FONT *font;
};

#endif // SLIDER_H_INCLUDED
