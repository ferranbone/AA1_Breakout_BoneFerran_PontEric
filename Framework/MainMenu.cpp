#include "MenuScene.h"
#include <iostream>
#include <windows.h>

void MenuScene::Update()
{
    if (GetAsyncKeyState('1') != 0) {
        nextScene = "Gameplay";
        finished = true;
    }
    else if (GetAsyncKeyState('2') != 0) {
        nextScene = "Ranking";
        finished = true;
    }
    else if (GetAsyncKeyState('3') != 0) {
        nextScene = "Credits";
        finished = true;
    }
    else if (GetAsyncKeyState('0') != 0) {
        nextScene = "Exit";
        finished = true;
    }
}

void MenuScene::Render()
{
    system("cls"); // Neteja la pantalla (només Windows)
    std::cout << "===== MAIN MENU =====\n";
    std::cout << "1. Play\n";
    std::cout << "2. Ranking\n";
    std::cout << "3. Credits\n";
    std::cout << "0. Exit\n";
}
