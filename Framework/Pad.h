#pragma once
#include "GameObject.h"
#include <Windows.h>
#include <vector>

class Pad : public GameObject {
protected:
	int width;
	int mapSize;
public:


	Pad(Vector2 _pos, ConsoleColor c, int w, int _mapSize)
		:GameObject(_pos, '_', c), width(w), mapSize(_mapSize) {}
	int GetWidth()  { return width; }
	
    void Update() override;
	void Render() override;
	
	std::vector<Vector2> ObtenerPosiciones() {
		//Vector para almacenar las posiciones
		std::vector<Vector2> posiciones;

		for (int desplazamiento = -width; desplazamiento <= width; desplazamiento++) {
			//Calcula la nueva posicion sumando el desplazamiento al centro del objeto
			posiciones.push_back(position + Vector2(desplazamiento, 0));
		}

		return posiciones; //Devuelve las posiciones generadas
	}

};