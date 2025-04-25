#include "Ball.h"

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

	for (auto i = objects.begin(); i != objects.end();) {
		GameObject* go = *i;

		if (go == this) {
			++i;
			continue;
		}

		if (position == go->GetPosition()) {
			// Pared
			if (Wall* wall = dynamic_cast<Wall*>(go)) {
				direction = CalculateCollision(go);
				++i;
				continue;
			}
			// Brick
			else if (Brick* brick = dynamic_cast<Brick*>(go)) {
				direction = CalculateCollision(go);
				brick->Destroy();
				i = objects.erase(i);
				continue;
			}
		}
		// Pala
		if (Pad* pala = dynamic_cast<Pad*>(go)) {
			std::vector<Vector2> posicionesPala = pala->ObtenerPosiciones();

			for (const Vector2& posPala : posicionesPala) {
				if (position == posPala) {
					int desplazamiento = posPala.x - pala->GetPosition().x;

					if (desplazamiento < 0) {
						direction.x = -1;
					}
					else if (desplazamiento > 0) {
						direction.x = 1;
					}
					else {
						direction.x = 0;
					}

					direction.y = -1;
					break;
				}
			}
		}


		++i;
	}
}

