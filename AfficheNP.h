#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


#define Max_main_menu 4

class AfficheNP
{





public:
	AfficheNP(float width, float height);


	void draw(RenderWindow& window);
	


	int MenuPressed()
	{
		return MenuSelected;
	}

	~AfficheNP();

private:
	int MenuSelected;
	Font font;
	
	Text menuNP[Max_main_menu];

};