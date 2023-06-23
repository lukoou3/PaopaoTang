#ifndef PAOPAOTANG_ITEMS_H
#define PAOPAOTANG_ITEMS_H

#include <graphics.h>
#include <vector>
#include <list>
#include "tools.h"

using namespace std;

const int item_width = 40;
const int item_height = 40;


enum ITEM_TYPE {
    ROAD, BLOCK1, BLOCK2, HOUSE1, HOUSE2, HOUSE3, BOX, TREE, WINDMILL, WINDMILL_VIR
};
enum DIRECTION {
    UP, DOWN, LEFT, RIGHT
};

class Role {
private:
    int x, y;
    int win_width, win_height;
    int speed = item_width / 5;
    DIRECTION dir;
    IMAGE imgs[4][6];
    int imgIdx;
    int walking = 0;
    int row, col;
    int bubble = 0;
    int bubbleMax = 5;
    unsigned long long lastBubble = 0;
    int exploded = 0;
    int died = 0;
public:
    IMAGE ride_imgs1[4];
    IMAGE die_imgs1[11];
public:
    void Init(IMAGE imgs[4][6], int x, int y, int win_width, int win_height);

    void SetRowCol();

    void Walk(DIRECTION direction);

    void WalkIng(vector<vector<int>> &game_map, bool (* fp)(Role &role));

    bool Bubble();

    void BubbleDie(){bubble--;}

    int X() { return x; }

    int Y() { return y; }

    int Row() { return row; }

    int Col() { return col; }

    int WX() { return win_width; }

    int WY() { return win_height; }
    DIRECTION Dir() { return dir; }

    int Exploded() { return exploded; }

    int Died() { return died; }

    void Explode() { exploded = 1; }
    void Die() { died = 1; }

    void Show();

    IMAGE *Img();
};

struct Bubble {
    int x;
    int y;
    int row;
    int col;
    int life;
    int stop;
    int imgIdx;
    Role *role;
};

struct BombBubble {
    int x;
    int y;
    int row;
    int col;
    int n; // 第几次显示
    Role *role;
};

struct ExplodeBubble {
    int x;
    int y;
    int row;
    int col;
    int n; // 第几次显示
    int died;
    Role *role;
};

class BubbleManager {
    int win_width, win_height;
    list<Bubble> bubbles;
    list<BombBubble> bombBubbles;
    list<ExplodeBubble> explodeBubbles;
public:
    BubbleManager(int win_width, int win_height);
    static IMAGE popoImgs[3];
    static IMAGE bombImgs[2][3 + 6 * 2];
    static IMAGE explodeImgs[7];
public:
    void AddBubble(int x, int y, Role *role);
    bool HasBubble(int row, int col);
    void Show();
    void ExplodeShow();
    void ExplodeRole(int row, int col, vector<Role*> &roles);
    void Bomb(vector<vector<int>> &game_map, vector<Role*> &roles);
    void PutBombImg(int  x, int y, IMAGE* picture);
    static void SetPopoImgs(IMAGE _popoImgs[3]);
    static void SetBombImgs(IMAGE bomb_imgs[2][3 + 6 * 2]);
};

#endif //PAOPAOTANG_ITEMS_H
