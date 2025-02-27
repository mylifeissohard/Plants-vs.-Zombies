

#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

float Attack::volume = -1;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./map.png");
    menu_back=al_load_bitmap("./menu_back.png");
    menuabout_back=al_load_bitmap("./OH.png");
    menuset_back=al_load_bitmap("./set_back.png");
    shop_back=al_load_bitmap("./shop.png");
    gamestart_back=al_load_bitmap("./startgame.png");



    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("happy.mp3");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL(1);
    menu = new Menu();
}
//menu
//void
//GameWindow::menu1_init()

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

bool
GameWindow::isOnRoad()
{
    int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i))
        {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return false;
        }
    }
    return false;
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isOnRoad())
        return t;

    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y);
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type));

    return t;
}

Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;
}

/*Sun*
GameWindow::create_sun()
{
    Sun *m = NULL;

    if(level->SunNum[Sun])
    {
        level->SunNum[Sun]--;
        m = new Sun(level->ReturnPath());
    }
    return m;
}*/


void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    game_init();

}


void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map( );


    //al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
   // al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue))
    {

        error = process_event();
    }
    return error;
}
Tower *t ;
int
GameWindow::game_update()
{
    unsigned int i, j;
    std::list<Tower*>::iterator it;
    //key_state[ALLEGRO_KEY_3] = true)

    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    /*for(auto_sun:sunSet){
        if()
    }*/

    for(auto _tower: towerSet)
    {
        for(auto _monster : monsterSet)
        {
            monster->Move();printf("MonsterMove\n");
            if(_tower->DetectAttack(_monster)){
                break;
            }

        }
    }

    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < monsterSet.size(); i++)
    {


        bool isDestroyed = false, isReachEnd = false;

        /*TODO:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/


        for(auto _tower: towerSet){
            isDestroyed=_tower->TriggerAttack(monsterSet[i]);
        }

        for(auto _tower: towerSet)
        {
            if(_tower->DetectAttack(monsterSet[i])){

                towertype=_tower->attack_harm_point;

                if(towertype==7){//¼È°±
                        printf("**\n\n\n\n");
                        break;
                    }
                else{//Move
                    isReachEnd = monsterSet[i]->Move();
                }

            }
        }






        if(isDestroyed)
        {
            Monster *m = monsterSet[i];

            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;

        }
        else if(isReachEnd)
        {
            Monster *m = monsterSet[i];

            if(menu->Subtract_HP())
                return GAME_EXIT;

            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }

    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    for(auto  _tower:towerSet)
    {
        _tower->UpdateAttack();
    }


    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    // reset game and begin
    for(auto&& child : towerSet)
    {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();


    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    Monster_Pro_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i=0; i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;
}


int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    // offset for pause window
    int offsetX = field_width/2 - 200;
    int offsetY = field_height/2 - 200;

    al_wait_for_event(event_queue, &event);
    redraw = false;


    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        if(event.timer.source == timer)
        {
            redraw = true;

            if(Coin_Inc_Count == 0)
                menu->Change_Coin(Coin_Time_Gain);

            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro))
            {
                al_stop_timer(timer);
                return GAME_EXIT;
            }

        }
        else
        {
            if(Monster_Pro_Count == 0)
            {
                Monster *m = create_monster();

                if(m != NULL)
                    monsterSet.push_back(m);
            }
            Monster_Pro_Count = (Monster_Pro_Count + 1) % level->getMonsterSpeed();
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && window == 0)
    {

        switch(event.keyboard.keycode)
        {

        case ALLEGRO_KEY_A:
            window=1;
            break;

        case ALLEGRO_KEY_S:
            window=2;
            break;

        case ALLEGRO_KEY_D:
            window=3;
            break;
        case ALLEGRO_KEY_W:
            return GAME_EXIT;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && window == 1)
    {
        if(event.type == ALLEGRO_EVENT_KEY_DOWN && game_wd == 0)
        {
            switch(event.keyboard.keycode)
            {
            case  ALLEGRO_KEY_1:
                break;
            case  ALLEGRO_KEY_2:
                break;
            case  ALLEGRO_KEY_3:
                break;

            case  ALLEGRO_KEY_4:
                break;

            case ALLEGRO_KEY_ESCAPE:
                game_wd=1;
                break;
            }

        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && game_wd == 1)
        {
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_ENTER:
                game_wd=2;
                break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && game_wd == 2)
        {
            // game code
            switch(event.keyboard.keycode)
            {

            case ALLEGRO_KEY_P:
                /*TODO: handle pause event here*/
                if(al_get_timer_started(timer))
                    al_stop_timer(timer);
                else
                    al_start_timer(timer);

                break;

            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_U:
                //
                break;
            }


        }


    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && window == 2)
    {

        switch(event.keyboard.keycode)
        {

        case ALLEGRO_KEY_ESCAPE:
            window=0;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && window == 3)
    {
        switch(event.keyboard.keycode)
        {

        case ALLEGRO_KEY_ESCAPE:
            window=0;
            break;
        case ALLEGRO_KEY_UP:
            if(now+0.2 >= 1)
                set_attack_volume(1);
            else
                set_attack_volume(now+0.2);
            break;
        case ALLEGRO_KEY_DOWN:
            if(now-0.2 <= 0)
                set_attack_volume(0);
            else
                set_attack_volume(now-0.2);
            break;
        case ALLEGRO_KEY_2:
            al_destroy_sample_instance(backgroundSound);
            sample = al_load_sample("dead.mp3");
            backgroundSound = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
            while(al_get_sample_instance_playing(startSound));
            al_play_sample_instance(backgroundSound);
            break;

        case ALLEGRO_KEY_1:
            al_destroy_sample_instance(backgroundSound);
            sample = al_load_sample("happy.mp3");
            backgroundSound = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
            while(al_get_sample_instance_playing(startSound));
            al_play_sample_instance(backgroundSound);
            break;

        }

    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && window == 4)
    {
        return GAME_EXIT;
    }

    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height))
            {
                Tower *t = create_tower(selectedTower);

                if(t == NULL)
                    printf("Wrong place\n");
                else
                {
                    towerSet.push_back(t);
                    towerSet.sort(compare);
                }
            }
            else if(selectedTower == -1)
            {
                std::list<Tower*>::iterator it = towerSet.begin();
                if(lastClicked != -1)
                {
                    std::advance(it, lastClicked);
                    (*it)->ToggleClicked();
                }
                for(i=0, it = towerSet.begin(); it != towerSet.end(); it++, i++)
                {
                    Circle *circle = (*it)->getCircle();
                    int t_width = (*it)->getWidth();

                    if(mouse_hover(circle->x - t_width/2, circle->y, t_width, t_width/2))
                    {
                        (*it)->ToggleClicked();
                        lastClicked = i;
                        break;
                    }
                    else
                    {
                        lastClicked = -1;
                    }
                }

            }
            // check if user wants to create some kind of tower
            // if so, show tower image attached to cursor
            selectedTower = menu->MouseIn(mouse_x, mouse_y);

        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
       // printf("%d %d\n",mouse_x,mouse_y);
        menu->MouseIn(mouse_x, mouse_y);

    }



    if(redraw)
    {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map( );
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map( )
{
    unsigned int i, j;
    if(window == 0)
    {
        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_bitmap(menu_back, -170, -10, 0);
    }
    else if(window == 1)
    {
        if(game_wd == 0)
        {
            // printf("%f\n",now);
            al_clear_to_color(al_map_rgb(100, 100, 100));
            al_draw_bitmap(shop_back, 0, 0, 0);
        }
        if(game_wd == 1)
        {
            // printf("%f\n",now);
            al_clear_to_color(al_map_rgb(100, 100, 100));
            al_draw_bitmap(gamestart_back, 0, 0, 0);
        }

        else if(game_wd == 2)
        {
            al_clear_to_color(al_map_rgb(100, 100, 100));
            al_draw_bitmap(background, 0, 0, 0);

            for(i=0; i<monsterSet.size(); i++)
            {
                monsterSet[i]->Draw();
            }


            for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
                (*it)->Draw();

            if(selectedTower != -1)
                Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

            al_draw_filled_rectangle(200, -50, 600 ,150, al_map_rgb(200, 200, 100));

            menu->Draw();
        }
    }
    else if(window == 2)
    {
        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_bitmap(menuabout_back, 0, 0, 0);
    }
    else if(window == 3)
    {
        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_bitmap(menuset_back, 0, 0, 0);
    }

    al_flip_display();

}

