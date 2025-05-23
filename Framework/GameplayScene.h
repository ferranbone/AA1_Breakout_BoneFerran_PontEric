#pragma once
#include "Scene.h"
#include "GameManager.h"

#include "Wall.h"
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"

#define MAP_SIZE 15

class GameplayScene : public Scene {
private:
	void SaveScore(const std::string& name, int score);
public:
	GameplayScene() {
		nextScene = "Menu";
	}
	
	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnExit() override;
};

