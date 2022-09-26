#include "Plateau.h"

Plateau::Plateau(float width, float height)
{
	plateau_echec.loadFromFile("donnees/board.png");

	sprite.setTexture(plateau_echec);
}

Plateau::~Plateau()
{

}

//afficher le menu

void Plateau::draw(RenderWindow& Instruction)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		Instruction.draw(plateau[i]);
	}
}
