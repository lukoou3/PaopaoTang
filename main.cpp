#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <graphics.h>
#include "game.h"

using namespace std;

int main() {
    //Init();
    srand(timeGetTime());  //用系统时间初始化随机种子
    game_init();

    while (1) {
        game_control();
        game_show();


        Sleep(30);
    }

    system("pause");
    return 0;
}
