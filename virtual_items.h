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
    virtual void Show() = 0;
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
    void Show();
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
    void Show();
    void Effect(Role *role);
};

class VirItemManager {
    list<VirItem*> virItems;
    int count = 0;
public:
    void Add(VirItem* virItem);
    void Show(vector<Role*> &roles);
    void Clear();
};

#endif //PAOPAOTANG_VIRTUAL_ITEMS_H