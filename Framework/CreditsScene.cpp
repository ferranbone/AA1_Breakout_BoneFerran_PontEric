#include "CreditsScene.h"

void CreditsScene::Update()
{
	if (GetAsyncKeyState('R') != 0) {
		finished = true;
	}
}

void CreditsScene::Render()
{
	std::cout << "JOC CREAT PER:" << std::endl;
	std::cout << "Ferran Bone & Eric Pont" << std::endl << std::endl << std::endl;
	std::cout << "Press R to go back to the menu;";
}
