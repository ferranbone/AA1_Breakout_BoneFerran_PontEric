#pragma once


class GameManager {
public:
	int puntuacion = 0;
	int combo = 0;
	int vidas = 3;
	
	void SumarPuntos(int cantidad) {
		puntuacion += cantidad;
	}

	void SumarPuntosConCombo(int cantidad) {
		int bonus = combo * 5;
		puntuacion += cantidad + bonus;
	}

	int ObtenerPuntuacion() const {
		return puntuacion;
	}

	void ResetearCombo() {
		combo = 0;
	}

	void IncrementarCombo() {
		combo++;
	}

	int ObtenerCombo() const {
		return combo;
	}

	void PerderVida() {
		vidas--;
	}

	int ObtenerVidas() const {
		return vidas;
	}
};

extern GameManager gameManager;