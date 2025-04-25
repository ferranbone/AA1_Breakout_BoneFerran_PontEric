#include "Ball.h"
GameManager gameManager;

Vector2 Ball::CalculateCollision( GameObject* other)
{
	int vertical = 0;
	int horizontal = 0;

	for ( int i=0;i < objects.size();i++) {
		//Check verticals
		bool top = (other->GetPosition() + Vector2(0, -1)) == objects[i]->GetPosition();
		bool bottom = (other->GetPosition() + Vector2(0, 1)) == objects[i]->GetPosition();
		vertical += (int)top + (int)bottom;

		//Check horizontals
		bool left = (other->GetPosition() + Vector2(-1, 0)) == objects[i]->GetPosition();
		bool right = (other->GetPosition() + Vector2(1, 0)) == objects[i]->GetPosition();
		horizontal += (int)left + (int)right;
	}

	Vector2 outDir = direction;

	//isolated
	if (vertical == 0 && horizontal == 0) {
		vertical = rand() % 2 > 0;
		horizontal = rand() % 2 > 0;
	}

	if (vertical >= horizontal)
		outDir.x = -outDir.x;
	if (horizontal > vertical)
		outDir.y = -outDir.y;

	return outDir;
}

void Ball::Update() {
	position = position + direction;

	//Si la pelota toca la pared de abajo, pierde una vida
	int paredInferiorY = 14;
	if (position.y >= paredInferiorY) {
		gameManager.PerderVida();
	}

	//Detecta colisiones
	for (auto i = objects.begin(); i != objects.end();) {
		GameObject* go = *i;

		if (go == this) {
			++i;
			continue;
		}

		//Verifica si la bola colisiona
		if (position == go->GetPosition()) {
			// Pared
			if (Wall* wall = dynamic_cast<Wall*>(go)) {
				direction = CalculateCollision(go);
				++i;
				continue;
			}
			// Brick
			//Si es un ladrillo, lo rompe, aumenta el combo y suma puntos
			else if (Brick* brick = dynamic_cast<Brick*>(go)) {
				direction = CalculateCollision(go);
				brick->Destroy();
				if (gameManager.ObtenerCombo() > 0) {
					gameManager.SumarPuntosConCombo(15);
				}
				else {
					gameManager.SumarPuntos(15);
				}

				gameManager.IncrementarCombo();

				i = objects.erase(i);
				continue;
			}
		}
		// Pala
		//Verifica si la bola colisiona con la pala
		if (Pad* pala = dynamic_cast<Pad*>(go)) {
			
			std::vector<Vector2> posicionesPala = pala->ObtenerPosiciones();

			for (const Vector2& posPala : posicionesPala) {
				if (position == posPala) {
					gameManager.ResetearCombo();
					int desplazamiento = posPala.x - pala->GetPosition().x;

					if (desplazamiento < 0) {
						direction.x = -1; //Si toca el lado izquierdo de la pala rebota hacia la izquierda
					}
					else if (desplazamiento > 0) {
						direction.x = 1; //Si toca el lado derecho de la pala rebota hacia la derecha
					}
					else {
						direction.x = 0; //Si toca el centro de la pala rebota recto
					}

					//Hace rebotar la pelota hacia arriba
					direction.y = -1;
					break;
				}
			}
		}


		++i;
	}
}

