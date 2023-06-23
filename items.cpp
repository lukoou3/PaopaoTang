#include "items.h"
#include <iostream>

using namespace std;

void Role::Init(IMAGE imgs[4][6], int x, int y, int win_width,int win_height){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            this->imgs[i][j] = imgs[i][j];
        }
    }
    this->x = x;
    this->y = y;
    this->win_width = win_width;
    this->win_height = win_height;
    dir = DOWN;
    imgIdx = 3;

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

void Role::WalkIng(vector<vector<int>> &game_map, bool (* fp)(Role &role)) {
    if(!walking){
        return;
    }
    walking--;
    imgIdx++;

    if(! fp(* this)) {
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
    putimagePNG2(x, y, Img());
}


void BubbleManager::AddBubble(int x, int y, Role *role) {
    bubbles.push_back(Bubble{x, y, 40, 0, 0, role});
}

bool bubble_die(Bubble &bubble){
    return bubble.life <= 0;
}

bool bomb_bubble_die(BombBubble &bombBubble){
    return bombBubble.n > 22;
}

bool explode_bubble_die(ExplodeBubble &bombBubble){
    return bombBubble.n > 60;
}

BubbleManager::BubbleManager(int win_width, int win_height){
    this->win_width = win_width;
    this->win_height = win_height;
}
IMAGE BubbleManager::popoImgs[3];
IMAGE BubbleManager::bombImgs[2][3 + 6 * 2];
IMAGE BubbleManager::explodeImgs[5][2];

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

void BubbleManager::ExplodeShow() {
    for (auto &b: explodeBubbles){
        b.n++;
        int i = (b.n -1) / 12;
        if(i < 2){
            PutBombImg(b.x,  b.y, &explodeImgs[i][0]);
        }else{
            PutBombImg(b.x,  b.y, &explodeImgs[i][0]);
            PutBombImg(b.x,  b.y, &explodeImgs[i][1]);
        }
        if(explode_bubble_die(b)){
            b.role->Die();
        }
    }

    explodeBubbles.remove_if(explode_bubble_die);
}

void BubbleManager::ExplodeRole(int row, int col, vector<Role*> &roles) {
    for (auto &role: roles){
        if(!role -> Exploded() && role -> Row() == row && role -> Col() == col){
            role -> Explode();
            explodeBubbles.push_back(ExplodeBubble{col * item_width, row * item_height, 0, role});
        }
    }
}

void BubbleManager::Bomb(vector<vector<int>> &game_map, vector<Role*> &roles) {
    for (auto &b: bombBubbles){
        b.n++;
        if(b.n <= 3){
            PutBombImg(b.x,  b.y, &BubbleManager::bombImgs[0][2]);
            PutBombImg(b.x,  b.y, &BubbleManager::bombImgs[1][2]);
        }else{
            int row = b.y / item_width;
            int col = b.x / item_height;
            int row_min = max(row - 2, 0) ;
            int row_max = min(row + 3, (int)game_map.size()) ;
            int col_min = max(col - 2, 0) ;
            int col_max = min(col + 3, (int)game_map[0].size()) ;
            int i = row;
            while (i >= row_min && game_map[i][col] >= ROAD && game_map[i][col] < TREE){
                ExplodeRole(i, col, roles);
                game_map[i][col] = ROAD;
                i --;
            }
            row_min = i + 1;
            i = row;
            while (i < row_max && game_map[i][col] >= ROAD && game_map[i][col] < TREE){
                ExplodeRole(i, col, roles);
                game_map[i][col] = ROAD;
                i ++;
            }
            row_max = i;
            i = col;
            while (i >= col_min && game_map[row][i] >= ROAD && game_map[row][i] < TREE){
                ExplodeRole(row, i, roles);
                game_map[row][i] = ROAD;
                i --;
            }
            col_min = i + 1;
            i = col;
            while (i < col_max && game_map[row][i] >= ROAD && game_map[row][i] < TREE){
                ExplodeRole(row, i, roles);
                game_map[row][i] = ROAD;
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
                b->role->BubbleDie();
                int x = ( (b->x + popoImgs[b->imgIdx].getwidth()/2) / item_width) * item_width;
                int y = ( (b->y+ popoImgs[b->imgIdx].getheight()/2) / item_height) * item_height;
                bombBubbles.push_back(BombBubble{x, y, 0, b->role});
            }
        }
    }

    bubbles.remove_if(bubble_die);
}
