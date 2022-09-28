#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Decor
{
public:
	Decor(RenderWindow &fenetre);
	~Decor();

	
	void PositionInitialPions();
	void SelectionTextures();

};

