#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


#define Max_main_menu 4

class Menu
{
public:
	Menu(float width, float height);
	

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	
	void AfficheI();
	void AfficheO();

	int MenuPressed()
	{
		return MenuSelected;
	}

	~Menu();

private:
	int MenuSelected;
	Font font;
	Text menu[Max_main_menu];
	Text menuNP[Max_main_menu];

};