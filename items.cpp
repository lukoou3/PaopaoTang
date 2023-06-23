#include "items.h"
#include <iostream>
#include "game.h"

using namespace std;

void Role::Init(Game *game,IMAGE imgs[4][6], int x, int y, int win_width,int win_height){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            this->imgs[i][j] = imgs[i][j];
        }
    }
    this->game = game;
    this->x = x;
    this->y = y;
    this->win_width = win_width;
    this->win_height = win_height;
    dir = DOWN;
    imgIdx = 3;

    cout << "RoleInit, game address:" << this->game << endl;

    SetRowCol();
}

void Role::SetRowCol(){
    row =  (y + (64 / 2)) / item_height;
    col = (x + (48 / 2)) / item_width;
}

void Role::Walk(DIRECTION direction) {
    if(walking){
        return;
    }
    walking = 5;
    dir = direction;
    imgIdx = 0;
}

void Role::WalkIng(vector<vector<int>> &game_map, bool (* fp)(Game *game, Role &role)) {
    if(exploded || !walking){
        return;
    }
    walking--;
    imgIdx++;

    if(! fp(game, * this)) {
        return;
    }

    if(dir == UP){
        if(row > 0 && game_map[row -1][col] != ROAD && y <= item_height * row - 20){
            return;
        }

        y -= speed;
        if(y <  item_height - Img() -> getheight()){
            y = item_height - Img() -> getheight();
        }
    }else if(dir == DOWN){
        if(row < game_map.size() - 1 && game_map[row + 1][col] != ROAD && y >= item_height * row - 20 ){
            return;
        }

        y += speed;
        if(y > win_height - Img()->getheight()){
            y = win_height - Img()->getheight();
        }
    }else if(dir == LEFT){
        if(col > 0 && game_map[row][col-1] != ROAD && x <= item_width * col - 4){
            return;
        }

        x -= speed;
        if(x < 0){
            x = 0;
        }
    }else if(dir == RIGHT){
        if(col < game_map[row].size() -1 && game_map[row][col+1] != ROAD && x >= item_width * col - 4){
            return;
        }
        x += speed;
        if(x > win_width - Img()->getwidth()){
            x = win_width - Img()->getwidth();
        }
    }
    SetRowCol();
}

bool Role::Bubble() {
    unsigned long long ts = GetTickCount();
    if(ts - lastBubble > 200  && bubble < bubbleMax){
        bubble++;
        lastBubble = ts;
        return true;
    }else{
        return false;
    }
}

IMAGE * Role::Img(){
    return & imgs[dir][imgIdx];
}

void Role::Show() {
    if(!exploded){
        putimagePNG2(x, y, Img());
    }
}


void BubbleManager::AddBubble(int x, int y, Role *role) {
    bubbles.push_back(Bubble{x, y, role->Row(), role->Col(), role->attack_distance, 40, 0, 0, role});
}

bool bubble_die(Bubble &bubble){
    return bubble.life <= 0;
}

bool bomb_bubble_die(BombBubble &bombBubble){
    return bombBubble.n > 22;
}

BubbleManager::BubbleManager(Game *game, int win_width, int win_height){
    this->game = game;
    this->win_width = win_width;
    this->win_height = win_height;

    cout << "BubbleManagerInit, game address:" << this->game << endl;
}
IMAGE BubbleManager::popoImgs[3];
IMAGE BubbleManager::bombImgs[2][3 + 6 * 2];
IMAGE BubbleManager::explodeImgs[7];

void BubbleManager::SetPopoImgs(IMAGE _popoImgs[3]) {
    for (int i = 0; i < 3; ++i) {
        popoImgs[i] = _popoImgs[i];
    }
}

bool BubbleManager::HasBubble(int row, int col){
    for (const auto &b: bubbles){
        if(row == (b.y + 20) / item_height && col == (b.x + 20) / item_width){
            return true;
        }
    }
    return false;
}

void BubbleManager::SetBombImgs(IMAGE _bombImgs[2][3 + 6 * 2]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3 + 6 * 2; ++j) {
            bombImgs[i][j] = _bombImgs[i][j];
        }
    }
}

void BubbleManager::PutBombImg(int  x, int y, IMAGE* picture){
    if(x < 0 || y < 0){
        return;
    }
    if(x >= win_width || y >= win_height){
        return;
    }
    putimagePNG(x,  y, picture);
}

bool explode_bubble_die(ExplodeBubble &bombBubble){
    return bombBubble.died == 2;
}

void BubbleManager::ExplodeShow() {
    for (auto &b: explodeBubbles){
        if(b.died == 0){
            b.n++;
            int i = (b.n -1) / 12;
            if(i % 2 == 0){
                IMAGE *ride_imgs1 = b.role->ride_imgs1;
                putimagePNG(b.col * item_width - (ride_imgs1[1].getwidth()- item_width) / 2,
                            b.row * item_height  - (ride_imgs1[1].getheight()- item_height) / 2,
                            &ride_imgs1[1]);
            }
            PutBombImg(b.x,  b.y, i % 2 == 0?&explodeImgs[1]:&explodeImgs[1]);
            if(b.n > 120){
                b.role->Die();
                b.died = 1;
                b.n = 0;
                mciSendString("play res/snd/die.mp3", 0, 0, 0);
            }
        }else if(b.died == 1){
            b.n++;
            int i = (b.n -1) / 12;
            if(i == 0){
                putimagePNG(b.x,  b.y, &explodeImgs[2]);
            }
            if(i == 1){
                putimagePNG(b.x,  b.y, &explodeImgs[4]);
            }
            if(i == 2){
                putimagePNG(b.x,  b.y, &explodeImgs[5]);
            }
            if(i == 3){
                putimagePNG(b.x,  b.y, &explodeImgs[6]);
            }
            if(i < 11){
                putimagePNG(b.x , b.y - 40, &b.role->die_imgs1[i]);
            }else{
                b.died = 2;
                game -> stop();
            }
        }

    }

    explodeBubbles.remove_if(explode_bubble_die);
}

void BubbleManager::ExplodeRole(int row, int col, vector<Role*> &roles) {
    for (auto &role: roles){
        if(!role -> Exploded() && role -> Row() == row && role -> Col() == col){
            role -> Explode();
            explodeBubbles.push_back(ExplodeBubble{
                col * item_width - (explodeImgs[1].getwidth()- item_width) / 2,
                row * item_height- (explodeImgs[1].getheight()- item_height) / 2,
                row, col ,0, 0, role
            });
        }
    }
}

void BubbleManager::Bomb(vector<vector<int>> &game_map, vector<Role*> &roles, void (* fp)(Game *game, int row, int col)) {
    for (auto &b: bombBubbles){
        b.n++;
        if(b.n <= 3){
            PutBombImg(b.x,  b.y, &BubbleManager::bombImgs[0][2]);
            PutBombImg(b.x,  b.y, &BubbleManager::bombImgs[1][2]);
        }else{
            int distance = b.attack_distance;
            int row = b.y / item_width;
            int col = b.x / item_height;
            int row_min = max(row - distance, 0) ;
            int row_max = min(row + distance + 1, (int)game_map.size()) ;
            int col_min = max(col - distance, 0) ;
            int col_max = min(col + distance + 1, (int)game_map[0].size()) ;
            int i = row;
            while (i >= row_min && game_map[i][col] >= ROAD && game_map[i][col] < HOUSE1){
                ExplodeRole(i, col, roles);
                // 修改成只能破一个墙
                if(game_map[i][col] != ROAD){
                    // 最后再打破，否则下次刷新画面会打破隔壁的
                    if(bomb_bubble_die(b)){
                        game_map[i][col] = ROAD;
                        fp(game, b.row, b.col); // 回调函数
                    }
                    i --;
                    break;
                }
                i --;
            }
            row_min = i + 1;
            i = row;
            while (i < row_max && game_map[i][col] >= ROAD && game_map[i][col] < HOUSE1){
                ExplodeRole(i, col, roles);
                // 修改成只能破一个墙
                if(game_map[i][col] != ROAD){
                    if(bomb_bubble_die(b)) {
                        game_map[i][col] = ROAD;
                        fp(game, b.row, b.col); // 回调函数
                    }
                    i ++;
                    break;
                }
                i ++;
            }
            row_max = i;
            i = col;
            while (i >= col_min && game_map[row][i] >= ROAD && game_map[row][i] < HOUSE1){
                ExplodeRole(row, i, roles);
                if(game_map[row][i] != ROAD){
                    if(bomb_bubble_die(b)) {
                        game_map[row][i] = ROAD;
                        fp(game, b.row, b.col); // 回调函数
                    }
                    i --;
                    break;
                }
                i --;
            }
            col_min = i + 1;
            i = col;
            while (i < col_max && game_map[row][i] >= ROAD && game_map[row][i] < HOUSE1){
                ExplodeRole(row, i, roles);
                if(game_map[row][i] != ROAD){
                    if(bomb_bubble_die(b)) {
                        game_map[row][i] = ROAD;
                        fp(game, b.row, b.col); // 回调函数
                    }
                    i ++;
                    break;
                }
                i ++;
            }
            col_max = i;

            if(b.n <= 12){
                for (i = row_min; i < row_max; ++i) {
                    PutBombImg(item_width * col,  item_height * i, &bombImgs[0][2]);
                }
                for (i = col_min; i < col_max; ++i) {
                    PutBombImg(item_width * i,  item_height * row, &bombImgs[1][2]);
                }
            }else if(b.n <= 17){
                for (i = row_min; i < row_max; ++i) {
                    PutBombImg(item_width * col,  item_height * i, i >= row? &bombImgs[0][3]:&bombImgs[0][4]);
                }
                for (i = col_min; i < col_max; ++i) {
                    PutBombImg(item_width * i,  item_height * row, i >= row? &bombImgs[1][3]:&bombImgs[1][4]);
                }
            }else if(b.n <= 22){
                int j = b.n - 18;
                for (i = row_min; i < row_max; ++i) {
                    PutBombImg(item_width * col,  item_height * i, i >= row? &bombImgs[0][5 + j * 2]:&bombImgs[0][6 + j * 2]);
                }
                for (i = col_min; i < col_max; ++i) {
                    PutBombImg(item_width * i,  item_height * row, i >= row? &bombImgs[1][5 + j * 2]:&bombImgs[1][6 + j * 2]);
                }
            }
        }

    }

    bombBubbles.remove_if(bomb_bubble_die);

    for (auto &b: bombBubbles){
        if(b.n > 3){

        }
    }
}

void BubbleManager::Show() {
    for (auto b = bubbles.begin(); b != bubbles.end(); b++) {
        putimagePNG2(b -> x, b -> y , &popoImgs[b->imgIdx]);
        b->stop++;
        if(b->stop >= 3){
            b->stop = 0;
            b->imgIdx++;
            if(b->imgIdx >= 3){
                b->imgIdx = 0;
            }
            b->life --;
            if(bubble_die(*b)){
                mciSendString("play res/snd/explode.mp3", 0, 0, 0);
                b->role->BubbleDie();
                int x = ( (b->x + popoImgs[b->imgIdx].getwidth()/2) / item_width) * item_width;
                int y = ( (b->y+ popoImgs[b->imgIdx].getheight()/2) / item_height) * item_height;
                bombBubbles.push_back(BombBubble{x, y, b->row, b->col, b->attack_distance, 0, b->role});
            }
        }
    }

    bubbles.remove_if(bubble_die);
}
