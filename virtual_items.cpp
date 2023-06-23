#include "virtual_items.h"


VirItem::VirItem(int x, int y, int row, int col){
    this -> x = x;
    this -> y = y;
    this -> row = row;
    this -> col = col;
}

IMAGE PowerItem::imgs[PowerItem::img_len];

PowerItem::PowerItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void PowerItem::Show() {
    n++;
    int i = n / 12;
    putimagePNG2(x, y , &imgs[i % img_len]);
}

void PowerItem::Effect(Role *role) {
    if(role->attack_distance < 4) {
        role->attack_distance += 1;
    }
}

IMAGE PoPoItem::imgs[PoPoItem::img_len];

PoPoItem::PoPoItem(int x, int y, int row, int col): VirItem(x, y, row, col){}

void PoPoItem::Show() {
    n++;
    int i = n / 12;
    putimagePNG2(x, y , &imgs[i % img_len]);
}

void PoPoItem::Effect(Role *role) {
    if(role->bubbleMax < 5) {
        role->bubbleMax += 1;
    }
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

void VirItemManager::Show(vector<Role*> &roles) {
    for (auto it=virItems.begin(); it!=virItems.end();) {
        VirItem * item = *it;
        item->Show();
        if (item_effect_role(item, roles)) {
            it = virItems.erase(it);
            count--;
            cout << "item_effect_role:" << "row:" << item->row << "col:" << item->col << " count:" << count << endl;
            delete item;
        } else {
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