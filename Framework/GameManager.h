#pragma once


class GameManager {
public:
	short score = 0; //Puntuación del jugador
	short combo = 0; //Combo de los ladrillos
	short hp = 3; //Vidas del jugador
	short bricksCounter = 0;

	//SCORE
	void AddScore(int quantity) {
		score += quantity;
	}
	
	void AddScoreWithCombo(int quantity) {
		int bonus = combo * 5; //Bonus de puntos de combo, cada combo suma 5 puntos extra
		score += quantity + bonus; //Puntos base mas los puntos extra del combo
	}

	short ObtainScore() const {
		return score; //Da la puntuacion actual
	}

	//COMBO
	void ResetCombo() {
		combo = 0; //Vuelve a poner el combo en 0
	}

	void IncrementCombo() {
		combo++; //Aumenta el combo actual
	}

	short ObtainCombo() const {
		return combo; //Da el combo actual
	}

	//HP
	void LoseHp() {
		hp--; //Resta una vida
	}

	short ObtainHp() const {
		return hp; //Da las vidas actuales
	}

	//BRICKS
	void AddBricksCounter() {
		bricksCounter++;
	}
	void SubtractBricksCounter() {
		bricksCounter--;
	}
	short ObtainBrickCounter() {
		return bricksCounter;
	}
};

extern GameManager gameManager;