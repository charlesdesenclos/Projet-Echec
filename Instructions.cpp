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