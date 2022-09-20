#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class menu
{
public:
	menu(float width, float height);
	~menu();

	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text Menu[MAX_NUMBER_OF_ITEMS];

};

