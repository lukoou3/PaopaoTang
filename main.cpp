#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <graphics.h>
#include "game.h"

using namespace std;

void strat(){
    loadimage(0, "res/title.png");
    mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
    while (1){
        if (GetAsyncKeyState(VK_SPACE) & 0x8000){
            break;
        }
        Sleep(1000);
    }
    mciSendString("stop res/bg.mp3", 0, 0, 0);
}

int main() {
    //SetConsoleOutputCP(65001);
    srand(timeGetTime());  //用系统时间初始化随机种子

    initgraph(win_width + 120, win_height);

    //loadimage(0, "res/title.png", 0, 0, true);

    int map_type = 2;
    Game *game = new Game(map_type);
    while (1) {
        game->run();

        loadimage(0, "res/title.png");
        FlushBatchDraw();
        mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
        //system("pause");
        mciSendString("stop res/bg.mp3", 0, 0, 0);

        delete game;

        strat();

        game = new Game(map_type);
        // 使用局部变量有bug，几个类用到*Game，game = Game()设计到；两个Game，一个临时的一个赋值语句
        //game = Game();
    }

    system("pause");
    return 0;
}
