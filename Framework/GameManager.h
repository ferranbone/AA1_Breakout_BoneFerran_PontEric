#pragma once


class GameManager {
public:
	int puntuacion = 0; //Puntuación del jugador
	int combo = 0; //Combo de los ladrillos
	int vidas = 3; //Vidas del jugador

	void SumarPuntos(int cantidad) {
		puntuacion += cantidad;
	}
	
	void SumarPuntosConCombo(int cantidad) {
		int bonus = combo * 5; //Bonus de puntos de combo, cada combo suma 5 puntos extra
		puntuacion += cantidad + bonus; //Puntos base mas los puntos extra del combo
	}

	int ObtenerPuntuacion() const {
		return puntuacion; //Da la puntuacion actual
	}

	void ResetearCombo() {
		combo = 0; //Vuelve a poner el combo en 0
	}

	void IncrementarCombo() {
		combo++; //Aumenta el combo actual
	}

	int ObtenerCombo() const {
		return combo; //Da el combo actual
	}

	void PerderVida() {
		vidas--; //Resta una vida
	}

	int ObtenerVidas() const {
		return vidas; //Da las vidas actuales
	}
};

extern GameManager gameManager;