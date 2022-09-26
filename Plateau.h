#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


#define Max_main_menu 4



class Plateau
{

public:
	Plateau(float width, float height);


	void draw(RenderWindow& Plateau);
	


	int MenuPressed()
	{
		return MenuSelected;
	}

	~Plateau();

private:
	int MenuSelected;
	Font font;
	Text plateau[Max_main_menu];
	Texture plateau_echec;
	Sprite sprite;
	
	
};

