#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


#define Max_main_menu 10


class Option
{
public:
	Option(float width, float height);

	void draw(RenderWindow& Instruction);


	int MenuPressed()
	{
		return MenuSelected;
	}

	~Option();

private:
	int MenuSelected;
	Font font;
	Text option[Max_main_menu];


};
