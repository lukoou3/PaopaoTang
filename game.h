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
    IMAGE tree_img;
    IMAGE windmill_img;

    Role role;
    vector<Role*> roles;
    BubbleManager bubbleManager = BubbleManager(this, win_width, win_height);
    VirItemManager virItemManager;

    vector<vector<int>>  game_map = {
            {0, HOUSE1, BLOCK1, HOUSE1, BLOCK1, TREE, 0, TREE, 0, TREE, BLOCK1, HOUSE2, BLOCK1, HOUSE2, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, BLOCK1, BLOCK2, BLOCK1, BLOCK2, 0, 0},
            {0, HOUSE1, BLOCK1, HOUSE1, BLOCK1, TREE, BOX, TREE, 0, TREE, BLOCK1, HOUSE2, BLOCK1, HOUSE2, 0},
            {0, BLOCK1, BLOCK2, BLOCK1, TREE, BOX, BOX, BLOCK1, 0, BOX, TREE, BLOCK1, BLOCK2, BLOCK1, BLOCK2},
            {0, TREE, BLOCK1, TREE, BOX, BOX, TREE, 0, 0, 0, 0, TREE, BLOCK1, TREE, BLOCK1},
            {0, 0, BOX, 0, 0, TREE, BLOCK1, 0, 0, TREE, 0, 0, BOX, 0, BLOCK2},
            {0, TREE, BLOCK1, TREE, 0, BLOCK2, WINDMILL_VIR, WINDMILL, WINDMILL_VIR, BLOCK2, 0, TREE, BLOCK1, TREE, BLOCK2},
            {0, 0, 0, 0, 0, TREE, BLOCK1, BLOCK1, BLOCK1, TREE, 0, 0, BOX, 0, BLOCK2},
            {BLOCK1, TREE, BLOCK1, TREE, BOX, BOX, TREE, BLOCK2, TREE, 0, 0, TREE, BLOCK1, TREE, BLOCK1},
            {BLOCK2, BLOCK1, BLOCK2, BLOCK1, TREE, BOX, BOX, BLOCK1, 0, 0, TREE, BLOCK1, BLOCK2, BLOCK1, BLOCK2},
            {0, HOUSE2, BLOCK1, HOUSE2, BLOCK1, TREE, BOX, TREE, 0, TREE, BLOCK1, HOUSE3, BLOCK1, HOUSE3, 0},
            {0, 0, BLOCK2, BLOCK1, BLOCK2, BLOCK1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, HOUSE2, BLOCK1, HOUSE2, BLOCK1, TREE, 0, TREE, 0, TREE, BLOCK1, HOUSE3, BLOCK1, HOUSE3, 0},
    };
public:
    ~ Game(){
        cout << "~Game"  << endl;
    }
    void run();

    void init();

    void control();

    void show();

    void stop();
};


#endif //PAOPAOTANG_GAME_H
