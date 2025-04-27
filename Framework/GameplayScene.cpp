#include "GameplayScene.h"

void GameplayScene::OnEnter()
{
	gameManager.ResetGameManager();
	finished = false;
	//Wall generation
	for (int i = 0; i < MAP_SIZE; i++) {
		Wall* topWall = new Wall(Vector2(i, 0), YELLOW, false);
		Wall* bottomWall = new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true);
		if (i > 0 && i < MAP_SIZE - 1) {
			Wall* leftSideWall = new Wall(Vector2(0, i), YELLOW, false);
			Wall* rightSideWall = new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false);
			objects.push_back(leftSideWall);
			objects.push_back(rightSideWall);
		}
		objects.push_back(topWall);
		objects.push_back(bottomWall);
	}

	//Bricks
	bool createBrick = false;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j < MAP_SIZE - 1; j++) {
			if (createBrick) {
				objects.push_back(new Brick(Vector2(j, i), CYAN));
				gameManager.AddBricksCounter();
				createBrick = false;
			}
			else {
				createBrick = true;
			}
			
		}
	}

	//PAD
	objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
	
	//BALL
	objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
}

void GameplayScene::Update()
{
	if (gameManager.ObtainHp() == 0 || gameManager.ObtainBrickCounter() == 0) {
		finished = true;

	}
	Scene::Update();
}

void GameplayScene::Render()
{
	Scene::Render();
	if (!finished) {
		int scoreX = 0;
		int scoreY = MAP_SIZE - 0;

		//Muestra la puntuacion, combo y vidas en pantalla
		ConsoleXY(scoreX, scoreY);
		std::cout << "Score: " << gameManager.ObtainScore() << "  Combo: " << gameManager.ObtainCombo() << std::endl;
		std::cout << "HP: " << gameManager.ObtainHp() << "   Bricks remaining: " << gameManager.ObtainBrickCounter() << std::endl;
	}
	else {
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); //Referencia CHATGPT, serveix per borrar els darrers inputs dels GetAsyncKeyState
		system("cls");
		std::cout << "Congratulations you made an score of " << gameManager.ObtainScore() << std::endl << std::endl;
		std::cout << "Please enter your name so we can save your score:" << std::endl;
		std::string name;
		std::cin >> name;

		SaveScore(name, gameManager.ObtainScore());
	}
	
}

void GameplayScene::OnExit()
{
	for (GameObject* o : objects)
		delete o;

	objects.clear();
}

void GameplayScene::SaveScore(const std::string& name, int score) {
	std::vector<std::pair<std::string, int>> scores;

	std::ifstream file("scores.dat", std::ios::binary);
	if (file.is_open()) {
		char nameBuffer[32];
		int scoreBuffer;

		while (file.read(nameBuffer, sizeof(nameBuffer))) {
			file.read(reinterpret_cast<char*>(&scoreBuffer), sizeof(int));
			std::string nameRead(nameBuffer);
			nameRead.erase(nameRead.find_last_not_of("\0") + 1);  // Clean up null spaces
			scores.push_back({ nameRead, scoreBuffer });
		}
		file.close();
	}

	scores.push_back({ name, score });

	for (size_t i = scores.size() - 1; i > 0; --i) {
		if (scores[i].second > scores[i - 1].second) {
			// Swap the scores
			std::swap(scores[i], scores[i - 1]);
		}
		else {
			break;
		}
	}

	std::ofstream outputFile("scores.dat", std::ios::binary | std::ios::trunc);  
	size_t maxScores = scores.size() < 5 ? scores.size() : 5;  

	for (size_t i = 0; i < maxScores; ++i) {
		char nameBuffer[32] = {};
		std::string currentName = scores[i].first;
		for (size_t j = 0; j < currentName.size() && j < 31; ++j) {
			nameBuffer[j] = currentName[j];
		}

		outputFile.write(nameBuffer, sizeof(nameBuffer));  
		outputFile.write(reinterpret_cast<const char*>(&scores[i].second), sizeof(int));  
	}

	outputFile.close();
	std::cout << "Score saved successfully!" << std::endl;
}
