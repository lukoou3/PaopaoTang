#ifndef PAOPAOTANG_GAME_H
#define PAOPAOTANG_GAME_H
#include "items.h"
#include "virtual_items.h"
#include <vector>

using namespace std;
const int row = 13;
const int col = 15;
const int win_width = item_width * col;
const int win_height = item_height * row;

class Game{
    bool running = true;
public:
    IMAGE grey_road_img;
    IMAGE green_road_img;
    IMAGE middle_road_img1;
    IMAGE middle_road_img2;
    IMAGE middle_road_img3;
    IMAGE windmill_ani_img1;
    IMAGE windmill_ani_img2;
    IMAGE role_imgs1[4][6];
    IMAGE role_imgs2[4][6];
    IMAGE popo_bomb_imgs[4];

    IMAGE block_red_img;
    IMAGE block_yellow_img;
    IMAGE house_blue_img;
    IMAGE house_red_img;
    IMAGE house_yellow_img;
    IMAGE box_img;
    IMAGE bush_img;
    IMAGE tree_img;
    IMAGE windmill_img;

    Role role;
    vector<Role*> roles;
    BubbleManager bubbleManager = BubbleManager(this, win_width, win_height);
    VirItemManager virItemManager = VirItemManager(this, win_width, win_height);

    vector<vector<int>> game_map;
    int map_type;

    void init_map();
public:
    Game(int map_type = 1);
    ~ Game(){
        cout << "~Game"  << endl;
    }
    int winWidth(){return win_width;}
    int winHeight(){return win_height;}

    void run();

    void init();

    void control();

    void show();

    void stop();
};


#endif //PAOPAOTANG_GAME_H
