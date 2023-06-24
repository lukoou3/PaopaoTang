#include "virtual_items.h"


VirItem::VirItem(int x, int y, int row, int col){
    this -> x = x;
    this -> y = y;
    this -> row = row;
    this -> col = col;
}

IMAGE PowerItem::imgs[PowerItem::img_len];

PowerItem::PowerItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void PowerItem::Show(int winWidth, int winHeight) {
    n++;
    int i = n / 12;
    putimagePNGXY(x, y, winWidth, winHeight, &imgs[i % img_len]);
}

void PowerItem::Effect(Role *role) {
    if(role->attack_distance < 4) {
        role->attack_distance += 1;
    }
}

IMAGE PoPoItem::imgs[PoPoItem::img_len];

PoPoItem::PoPoItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void PoPoItem::Show(int winWidth, int winHeight) {
    n++;
    int i = n / 12;
    putimagePNGXY(x, y, winWidth, winHeight, &imgs[i % img_len]);
}

void PoPoItem::Effect(Role *role) {
    if(role->bubbleMax < 5) {
        role->bubbleMax += 1;
    }
}

IMAGE RunItem::imgs[RunItem::img_len];

RunItem::RunItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void RunItem::Show(int winWidth, int winHeight) {
    n++;
    int i = n / 12;
    putimagePNGXY(x, y, winWidth, winHeight, &imgs[i % img_len]);
}

void RunItem::Effect(Role *role) {
    if(role->speed < item_width / 5) {
        role->speed += item_width / 20;
    }
}

IMAGE PrickItem::imgs[PrickItem::img_len];

PrickItem::PrickItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void PrickItem::Show(int winWidth, int winHeight) {
    n++;
    int i = n / 12;
    putimagePNGXY(x, y, winWidth, winHeight, &imgs[i % img_len]);
}

void PrickItem::Effect(Role *role) {
    role->prick_count+=2;
}

IMAGE GuardItem::imgs[PrickItem::img_len];

GuardItem::GuardItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void GuardItem::Show(int winWidth, int winHeight) {
    n++;
    int i = n / 12;
    putimagePNGXY(x, y, winWidth, winHeight, &imgs[i % img_len]);
}

void GuardItem::Effect(Role *role) {
    role->guard_count+=1;
}

VirItemManager::VirItemManager(Game *game, int win_width, int win_height){
    this->game = game;
    this->win_width = win_width;
    this->win_height = win_height;

    cout << "VirItemManagerInit, game address:" << this->game << endl;
}

void VirItemManager::Add(VirItem* virItem) {
    count++;
    cout << "AddVirItem row:" << virItem->row << "col:" << virItem->col << " count:" << count<< endl;
    virItems.push_back(virItem);
}

bool item_effect_role(VirItem * item, vector<Role*> &roles) {
    for (auto &role: roles){
        if(item->row == role->Row() && item->col == role->Col()){
            mciSendString("play res/snd/get.mp3", 0, 0, 0);
            item -> Effect(role);
            return true;
        }
    }
    return false;
}

void VirItemManager::Show(int row, vector<Role*> &roles) {
    for (auto it=virItems.begin(); it!=virItems.end();) {
        VirItem * item = *it;
        if(row == item->row){
            item->Show(win_width, win_height);
            if (item_effect_role(item, roles)) {
                it = virItems.erase(it);
                count--;
                cout << "item_effect_role:" << "row:" << item->row << "col:" << item->col << " count:" << count << endl;
                delete item;
            } else {
                it++;
            }
        }else {
            it++;
        }
    }
}

void VirItemManager::Clear() {
    for (auto it=virItems.begin(); it!=virItems.end();) {
        VirItem * item = *it;
        it = virItems.erase(it);
        count--;
        cout << "clear_item:" << "row:" << item->row << "col:" << item->col << " count:" << count << endl;
        delete item;
    }
}