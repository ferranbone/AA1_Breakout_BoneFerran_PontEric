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
	
	std::vector<Vector2> ObtainPositions() {
		//Vector para almacenar las posiciones
		std::vector<Vector2> positions;

		for (int movement = -width; movement <= width; movement++) {
			//Calcula la nueva posicion sumando el desplazamiento al centro del objeto
			positions.push_back(position + Vector2(movement, 0));
		}

		return positions; //Devuelve las posiciones generadas
	}

};