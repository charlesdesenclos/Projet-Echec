#include "AfficheNP.h"


AfficheNP::AfficheNP(float width, float height)
{

	if (!font.loadFromFile("donnees/ALGER.ttf"))
	{
		cout << "Police non trouvé";
	}
	// Solo

	menuNP[0].setFont(font);
	menuNP[0].setFillColor(Color::White);
	menuNP[0].setString("Solo");
	menuNP[0].setCharacterSize(40);
	menuNP[0].setPosition(350, 200);

	// Multijoueur

	menuNP[1].setFont(font);
	menuNP[1].setFillColor(Color::White);
	menuNP[1].setString("Multijoueur");
	menuNP[1].setCharacterSize(40);
	menuNP[1].setPosition(350, 300);

	MenuSelected = -1;
}

AfficheNP::~AfficheNP()
{

}

void AfficheNP::draw(RenderWindow& Play)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		Play.draw(menuNP[i]);
	}
}