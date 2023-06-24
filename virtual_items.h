#ifndef PAOPAOTANG_VIRTUAL_ITEMS_H
#define PAOPAOTANG_VIRTUAL_ITEMS_H
#include "items.h"
#include <iostream>
using namespace std;

class VirItem {
public:
    int x, y;
    int row, col;
    int n = 0;
public:
    VirItem(int x, int y, int row, int col);
    virtual ~VirItem(){
        cout << "~VirItem:" << "row:" << row << "col:" << col << endl;
    }
    virtual void Show(int winWidth, int winHeight) = 0;
    virtual void Effect(Role *role) = 0;
};

class PowerItem : public VirItem {
public:
    const static int img_len = 3;
    static IMAGE imgs[img_len];
public:
    PowerItem(int x, int y, int row, int col);
    ~PowerItem(){
        cout << "~PowerItem:" << "row:" << row << "col:" << col << endl;
    }
    void Show(int winWidth, int winHeight);
    void Effect(Role *role);
};

class PoPoItem : public VirItem {
public:
    const static int img_len = 3;
    static IMAGE imgs[img_len];
public:
    PoPoItem(int x, int y, int row, int col);
    ~PoPoItem(){
        cout << "~PoPoItem:" << "row:" << row << "col:" << col << endl;
    }
    void Show(int winWidth, int winHeight);
    void Effect(Role *role);
};

class RunItem: public VirItem {
public:
    const static int img_len = 3;
    static IMAGE imgs[img_len];
public:
    RunItem(int x, int y, int row, int col);
    ~RunItem(){
        cout << "~RunItem:" << "row:" << row << "col:" << col << endl;
    }
    void Show(int winWidth, int winHeight);
    void Effect(Role *role);
};

class PrickItem: public VirItem {
public:
    const static int img_len = 3;
    static IMAGE imgs[img_len];
public:
    PrickItem(int x, int y, int row, int col);
    ~PrickItem(){ }
    void Show(int winWidth, int winHeight);
    void Effect(Role *role);
};

class GuardItem: public VirItem {
public:
    const static int img_len = 3;
    static IMAGE imgs[img_len];
public:
    GuardItem(int x, int y, int row, int col);
    ~GuardItem(){ }
    void Show(int winWidth, int winHeight);
    void Effect(Role *role);
};

class VirItemManager {
    int win_width, win_height;
    list<VirItem*> virItems;
    int count = 0;
public:
    Game *game;
    VirItemManager(Game *game, int win_width, int win_height);
    void Add(VirItem* virItem);
    void Show(int row, vector<Role*> &roles);
    void Clear();
};

#endif //PAOPAOTANG_VIRTUAL_ITEMS_H
