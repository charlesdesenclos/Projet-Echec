#include "menu.h"

menu::menu(float width, float height)
{
	if (!font.loadFromFile("donnees/ALGER.ttf"))
	{
		//handle error
	}

	Menu[0].setFont(font);
	Menu[0].setColor(sf::Color::Red);
	Menu[0].setString("Nouvelle Partie");
	Menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	Menu[1].setFont(font);
	Menu[1].setColor(sf::Color::White);
	Menu[1].setString("Instruction");
	Menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	Menu[2].setFont(font);
	Menu[2].setColor(sf::Color::Red);
	Menu[2].setString("Quitter");
	Menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

menu::~menu()
{

}

void menu