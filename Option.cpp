#include "Option.h"

Option::Option(float width, float height)
{
	if (!font.loadFromFile("donnees/ALGER.ttf"))
	{
		cout << "Police non trouvé";
	}

	option[0].setFont(font);
	option[0].setFillColor(Color::White);
	option[0].setString("Option");
	option[0].setCharacterSize(40);
	option[0].setPosition(350, 200);

	option[1].setFont(font);
	option[1].setFillColor(Color::White);
	option[1].setString("Touche");
	option[1].setCharacterSize(30);
	option[1].setPosition(350, 300);

	option[2].setFont(font);
	option[2].setFillColor(Color::White);
	option[2].setString("Utiliser le click gauche pour aller à une autre page");
	option[2].setCharacterSize(20);
	option[2].setPosition(100, 400);

	option[3].setFont(font);
	option[3].setFillColor(Color::White);
	option[3].setString("Rester appuyer sur le click gauche pour déplacer un pion");
	option[3].setCharacterSize(20);
	option[3].setPosition(100, 430);


}

Option::~Option()
{

}

//afficher le menu

void Option::draw(RenderWindow& Instruction)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		Instruction.draw(option[i]);
	}
}
