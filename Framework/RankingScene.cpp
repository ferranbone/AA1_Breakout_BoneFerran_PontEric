#include "RankingScene.h"

void RankingScene::Update()
{
	if (GetAsyncKeyState('R') != 0) {
		finished = true;
	}
}

void RankingScene::Render()
{
    std::ifstream file("scores.dat", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "NO SCORES AVIABLE RIGHT NOW" << std::endl;
        return;
    }

    char nameBuffer[32];
    int scoreBuffer;

    std::cout << "RANKING:\n";
    while (file.read(nameBuffer, sizeof(nameBuffer))) {
        file.read(reinterpret_cast<char*>(&scoreBuffer), sizeof(int));

        std::string name(nameBuffer);
        name.erase(name.find_last_not_of("\0") + 1);  // Remove null spaces

        std::cout << name << ":   " << scoreBuffer << std::endl;
    }

    file.close();
	std::cout << "Press R to go back to the menu;";
}
