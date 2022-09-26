#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


#define Max_main_menu 4


class Instructions
{
public:
	Instructions(float width, float height);

	void draw(RenderWindow& Instruction);
	

	int MenuPressed()
	{
		return MenuSelected;
	}

	~Instructions();

private:
	int MenuSelected;
	Font font;
	Text instructions[Max_main_menu];
	

};

