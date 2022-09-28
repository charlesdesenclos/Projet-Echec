#include "Instructions.h"


Instructions::Instructions(float width, float height)
{
	if (!font.loadFromFile("donnees/ALGER.ttf"))
	{
		cout << "Police non trouvé";
	}

	instructions[0].setFont(font);
	instructions[0].setFillColor(Color::White);
	instructions[0].setString("Instructions");
	instructions[0].setCharacterSize(40);
	instructions[0].setPosition(350, 200);

	instructions[1].setFont(font);
	instructions[1].setFillColor(Color::White);
	instructions[1].setString("L'échiquier est composé de 64 cases dont 16 pions par joueur.");
	instructions[1].setCharacterSize(20);
	instructions[1].setPosition(40, 300);

	instructions[2].setFont(font);
	instructions[2].setFillColor(Color::White);
	instructions[2].setString("Les pions sont un roi, la dame, deux fous ,deux cavaliers, huit pions.");
	instructions[2].setCharacterSize(20);
	instructions[2].setPosition(40, 330);

	instructions[3].setFont(font);
	instructions[3].setFillColor(Color::White);
	instructions[3].setString("La tour se déplace horizontalement et verticalement, le fou se dépace en diagonale.");
	instructions[3].setCharacterSize(20);
	instructions[3].setPosition(40, 360);

	instructions[4].setFont(font);
	instructions[4].setFillColor(Color::White);
	instructions[4].setString("La dame peut se déplacer horizontalement, verticalement et en diagonale.");
	instructions[4].setCharacterSize(20);
	instructions[4].setPosition(40, 390);

	instructions[5].setFont(font);
	instructions[5].setFillColor(Color::White);
	instructions[5].setString("Le roi peut se déplacer d'une seule case dans toutes les directions.");
	instructions[5].setCharacterSize(20);
	instructions[5].setPosition(40, 420);

	instructions[6].setFont(font);
	instructions[6].setFillColor(Color::White);
	instructions[6].setString("Le chevalier peut se déplacer de deux cases horizontalement ou verticalement,");
	instructions[6].setCharacterSize(20);
	instructions[6].setPosition(40, 450);

	instructions[7].setFont(font);
	instructions[7].setFillColor(Color::White);
	instructions[7].setString("puis fait un pas sur le côté.");
	instructions[7].setCharacterSize(20);
	instructions[7].setPosition(40, 480);

	instructions[8].setFont(font);
	instructions[8].setFillColor(Color::White);
	instructions[8].setString("Les pions avancent d'une case sur la même colone. ");
	instructions[8].setCharacterSize(20);
	instructions[8].setPosition(40, 510);
}

Instructions::~Instructions()
{

}

//afficher le menu

void Instructions::draw(RenderWindow& Instruction)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		Instruction.draw(instructions[i]);
	}
}