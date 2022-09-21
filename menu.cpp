#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("donnees/ALGER.ttf"))
	{
		cout << "Image non trouvé";
	}



	// Nouvelles parties

	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setString("Nouvelles Parties");
	menu[0].setCharacterSize(40);
	menu[0].setPosition(350, 200);

	// Instructions

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Instructions");
	menu[1].setCharacterSize(40);
	menu[1].setPosition(350, 300);

	//Options
	
	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Options");
	menu[2].setCharacterSize(40);
	menu[2].setPosition(350, 400);

	//Quitter

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("Quitter");
	menu[3].setCharacterSize(40);
	menu[3].setPosition(350, 500);

	MenuSelected = -1;
}

Menu::~Menu()
{

}

//afficher le menu

void Menu::draw(RenderWindow& windows)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		windows.draw(menu[i]);
	}
}

// gère le dépacement vers le haut

void Menu::MoveUp()
{
	if (MenuSelected - 1 >= 0)
	{
		menu[MenuSelected].setFillColor(Color::White);

		MenuSelected--;

		if (MenuSelected == -1)
		{
			MenuSelected = 2;
		}
		menu[MenuSelected].setFillColor(Color::Blue);
	}
}

// gère le dépacement vers le bas

void Menu::MoveDown()
{
	if (MenuSelected + 1 <= Max_main_menu)
	{
		menu[MenuSelected].setFillColor(Color::White);
		MenuSelected++;
		if (MenuSelected == 4)
		{
			MenuSelected = 0;
		}
		menu[MenuSelected].setFillColor(Color::Blue);
	}
}