#pragma once
#include "Scene.h"

class CreditsScene : public Scene {
protected:
	
public:
	CreditsScene() {
		nextScene = "Menu";
	}
	void Update() override;
	void Render() override;
};