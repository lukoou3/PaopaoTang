#include <iostream>
#include <graphics.h>
#include <vector>
#include "tools.h"

using namespace std;

const int item_width = 40;
const int item_height = 40;

enum ITEM_TYPE {
    ROAD, BLOCK1, BLOCK2, HOUSE1, HOUSE2, HOUSE3, BOX, TREE, WINDMILL, WINDMILL_VIR
};

const int row = 13;
const int col = 15;
const int win_width = item_width * col;
const int win_height = item_height * row;

IMAGE grey_road_img;
IMAGE green_road_img;
IMAGE middle_road_img1;
IMAGE middle_road_img2;
IMAGE middle_road_img3;
IMAGE windmill_ani_img1;
IMAGE windmill_ani_img2;
IMAGE role_imgs1[4][6];
IMAGE role_imgs2[4][6];
IMAGE role_ride_imgs1[4];
IMAGE role_die_imgs1[11];
IMAGE popo_bomb_imgs[4];
IMAGE popo_big_imgs[9];

IMAGE block_red_img;
IMAGE block_yellow_img;
IMAGE house_blue_img;
IMAGE house_red_img;
IMAGE house_yellow_img;
IMAGE box_img;
IMAGE tree_img;
IMAGE windmill_img;

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


int main() {
    initgraph(win_width, win_height);

    // 分隔加载图片
    IMAGE img;
    loadimage(&img, "res/road.png");
    SetWorkingImage(&img);
    getimage(&grey_road_img, 0, 0, 40, 40);
    getimage(&green_road_img, 40, 0, 40, 40);
    getimage(&middle_road_img1, 40 * 6, 0, 40, 40);
    getimage(&middle_road_img2, 40 * 7, 0, 40, 40);
    getimage(&middle_road_img3, 40 * 8, 0, 40, 40);
    loadimage(&img, "res/TownWindmillAni.png");
    SetWorkingImage(&img);
    getimage(&windmill_ani_img1, 0, 0, 120, 118);
    getimage(&windmill_ani_img2, 120, 0, 120, 118);
    loadimage(&img, "res/Role1.png", 48 * 6, 64 * 4, true);
    SetWorkingImage(&img);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; ++j) {
            getimage(&role_imgs1[i][j], 48 * j, 64 * i , 48, 64);
        }

    }
    loadimage(&img, "res/Role2.png");
    SetWorkingImage(&img);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; ++j) {
            getimage(&role_imgs2[i][j], 48 * j, 64 * i , 48, 64);

        }
    }
    loadimage(&img, "res/Popo.png");
    SetWorkingImage(&img);
    IMAGE popoImgs[3];
    for (int i = 0; i < 3; i++) {
        getimage(&popoImgs[i], 44 * i, 0 , 44, 41);
    }
    loadimage(&img, "res/BigPopo.png", 72 * 9, 72, true);
    SetWorkingImage(&img);
    for (int i = 0; i < 9; i++) {
        getimage(&popo_big_imgs[i], 72 * i, 0 , 72, 72);
    }
    loadimage(&img, "res/Role1Ride.png", 40 * 4, 40 , true);
    SetWorkingImage(&img);
    for (int i = 0; i < 4; i++) {
        getimage(&role_ride_imgs1[i], 40 * i, 0 , 40, 40);
    }
    loadimage(&img, "res/Role1Die.png", 48 * 11, 100 , true);
    SetWorkingImage(&img);
    for (int i = 0; i < 11; i++) {
        getimage(&role_die_imgs1[i], 48 * i, 0 , 48, 100);
    }
    loadimage(&img, "res/Explosion.png", 560, 200, true);
    SetWorkingImage(&img);
    IMAGE bomb_imgs[2][3 + 6 * 2];
    getimage(&bomb_imgs[0][0], 0, 0 , 40, 40);
    getimage(&bomb_imgs[0][1], 0, 40 , 40, 40);
    getimage(&bomb_imgs[0][2], 40 * 3, 0 , 40, 40);
    getimage(&bomb_imgs[0][3], 40 * 8, 0 , 40, 40);
    getimage(&bomb_imgs[0][4], 40 * 8, 40 , 40, 40);
    getimage(&bomb_imgs[0][5], 40 * 9, 0 , 40, 40);
    getimage(&bomb_imgs[0][6], 40 * 9, 40 , 40, 40);
    getimage(&bomb_imgs[0][7], 40 * 10, 0 , 40, 40);
    getimage(&bomb_imgs[0][8], 40 * 10, 40 , 40, 40);
    getimage(&bomb_imgs[0][9], 40 * 11, 0 , 40, 40);
    getimage(&bomb_imgs[0][10], 40 * 11, 40 , 40, 40);
    getimage(&bomb_imgs[0][11], 40 * 12, 0 , 40, 40);
    getimage(&bomb_imgs[0][12], 40 * 12, 40 , 40, 40);
    getimage(&bomb_imgs[0][13], 40 * 13, 0 , 40, 40);
    getimage(&bomb_imgs[0][14], 40 * 13, 40 , 40, 40);
    getimage(&bomb_imgs[1][0], 0, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][1], 0, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][2], 40 * 3, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][3], 40 * 8, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][4], 40 * 8, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][5], 40 * 9, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][6], 40 * 9, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][7], 40 * 10, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][8], 40 * 10, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][9], 40 * 11, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][10], 40 * 11, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][11], 40 * 12, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][12], 40 * 12, 40 * 3 , 40, 40);
    getimage(&bomb_imgs[1][13], 40 * 13, 40 * 2 , 40, 40);
    getimage(&bomb_imgs[1][14], 40 * 13, 40 * 3 , 40, 40);
    getimage(&popo_bomb_imgs[0], 0, 40 * 4, 40, 40);
    getimage(&popo_bomb_imgs[1], 40, 40 * 4, 40, 40);
    getimage(&popo_bomb_imgs[2], 40 * 2, 40 * 4, 40, 40);
    getimage(&popo_bomb_imgs[3], 40 * 3, 40 * 4, 40, 40);
    SetWorkingImage();



    // 加载图片
    loadimage(&block_red_img, "res/TownBlockRed.bmp", item_width, item_height, true);
    loadimage(&block_yellow_img, "res/TownBlockYellow.bmp", item_width, item_height, true);
    loadimage(&house_blue_img, "res/TownHouseBlue.png", item_width, item_height + 16, true);
    loadimage(&house_red_img, "res/TownHouseRed.png", item_width, item_height + 16, true);
    loadimage(&house_yellow_img, "res/TownHouseYellow.png", item_width, item_height + 16, true);
    loadimage(&box_img, "res/TownBox.bmp", item_width, item_height, true);
    loadimage(&tree_img, "res/TownTree.png");
    loadimage(&windmill_img, "res/TownWindmill.png", item_width * 3, 62, true);

    int n = 0;
    while (1){
        BeginBatchDraw();

        for (int i = 0; i < row; i++) {
            putimagePNG(item_width * 0, item_height * i, &grey_road_img);
            int j;
            for (j = 1; j < 6; ++j) {
                putimagePNG(item_width * j, item_height * i, &green_road_img);
            }
            putimagePNG(item_width * j++, item_height * i, &middle_road_img1);
            putimagePNG(item_width * j++, item_height * i, &middle_road_img2);
            putimagePNG(item_width * j++, item_height * i, &middle_road_img3);
            for (; j < col - 1; ++j) {
                putimagePNG(item_width * j, item_height * i, &green_road_img);
            }
            putimagePNG(item_width * j, item_height * i, &grey_road_img);
        }

        int windmill_x = 0, windmill_y= 0;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; ++j) {
                ITEM_TYPE item_type = (ITEM_TYPE) game_map[i][j];
                int x = item_width * j, y = item_height * i;
                switch (item_type) {
                    case BLOCK1:
                        putimagePNG(x, y, &block_red_img);
                        break;
                    case BLOCK2:
                        putimagePNG(x, y, &block_yellow_img);
                        break;
                    case BOX:
                        putimagePNG(x, y, &box_img);
                        break;
                    case HOUSE1:
                        putimagePNG2(x, y - 16, &house_red_img);
                        break;
                    case HOUSE2:
                        putimagePNG2(x, y - 16, &house_blue_img);
                        break;
                    case HOUSE3:
                        putimagePNG2(x, y - 16, &house_yellow_img);
                        break;
                    case TREE:
                        putimagePNGY(x, y - (tree_img.getheight() - item_height - 6), win_height, &tree_img);
                        break;
                    case WINDMILL:
                        windmill_x = x;
                        windmill_y= y;
                        putimagePNG(windmill_x - item_width, windmill_y, &windmill_img);
                        break;
                    default:
                        break;
                }
            }
        }

        //putimagePNG(4 * item_width, 7 * item_height - (64 - 40)/2, &role_imgs1[1][0]);
        if(n < 12){
            if( n % 3<=1)
                putimagePNG(4 * item_width - (role_ride_imgs1[1].getwidth()- item_width) / 2, 7 * item_height  - (role_ride_imgs1[1].getheight()- item_height) / 2, &role_ride_imgs1[1]);
            putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, n % 3<=1?&popo_big_imgs[3]:&popo_big_imgs[3]);
            //putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, &popo_big_imgs[7]);
        }
        if(n == 12)
            putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, &popo_big_imgs[4]);
        if(n == 13)
            putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, &popo_big_imgs[6]);
        if(n == 14)
            putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, &popo_big_imgs[7]);
        if(n == 15)
            putimagePNG(4 * item_width - (72- item_width) / 2, 7 * item_height - (72- item_height) / 2, &popo_big_imgs[8]);
        if(n >= 12 && n - 12 < 11){
            putimagePNG(4 * item_width , n - 12 < 3?6 * item_height: 6 * item_height, &role_die_imgs1[n - 12]);
        }
        FlushBatchDraw();

        n++;
        Sleep(200);
    }

    EndBatchDraw();
    Sleep(3000);

    system("pause");
    return 0;
}