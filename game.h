#ifndef PAOPAOTANG_GAME_H
#define PAOPAOTANG_GAME_H
#include "items.h"
#include <vector>

using namespace std;

const int row = 13;
const int col = 15;
const int win_width = item_width * col;
const int win_height = item_height * row;


void game_init();

void game_control();

void game_show();

#endif //PAOPAOTANG_GAME_H
