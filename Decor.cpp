#include "Decor.h"

Decor::Decor(RenderWindow &fenetre)
{

}

Decor::~Decor()
{

}

void Decor::PositionInitialPions()
{
	//Affichage pion blanc

													//Affichage pion roi

	Texture image_roi;

	image_roi.loadFromFile("./donnees/king.png");

	Sprite sprite_roi;

	image_roi.setSmooth(true);

	sprite_roi.setTexture(image_roi);

	sprite_roi.setScale(0.6f, 0.6f);

	sprite_roi.setPosition(350, 580);

	//Affichage pion reine

	Texture image_reine;

	image_reine.loadFromFile("./donnees/queen.png");

	Sprite sprite_reine;

	image_reine.setSmooth(true);

	sprite_reine.setTexture(image_reine);

	sprite_reine.setScale(0.6f, 0.6f);

	sprite_reine.setPosition(270, 580);

	//Affichage des pions fou 

	Texture image_fou;

	image_fou.loadFromFile("./donnees/fou.png");

	Sprite sprite_fou;

	image_fou.setSmooth(true);

	sprite_fou.setTexture(image_fou);

	sprite_fou.setScale(0.6f, 0.6f);

	sprite_fou.setPosition(190, 580);

	Texture image_fou2;

	image_fou2.loadFromFile("./donnees/fou.png");

	Sprite sprite_fou2;

	image_fou.setSmooth(true);

	sprite_fou2.setTexture(image_fou2);

	sprite_fou2.setScale(0.6f, 0.6f);

	sprite_fou2.setPosition(425, 580);

	//Affichage des pions chevaliers

	Texture image_chavalier;

	image_chavalier.loadFromFile("./donnees/knight.png");

	Sprite sprite_chevalier;

	image_chavalier.setSmooth(true);

	sprite_chevalier.setTexture(image_chavalier);

	sprite_chevalier.setScale(0.6f, 0.6f);

	sprite_chevalier.setPosition(110, 580);

	Texture image_chevalier2;

	image_chevalier2.loadFromFile("./donnees/knight.png");

	Sprite sprite_chevalier2;

	image_chevalier2.setSmooth(true);

	sprite_chevalier2.setTexture(image_chevalier2);

	sprite_chevalier2.setScale(0.6f, 0.6f);

	sprite_chevalier2.setPosition(505, 580);

	//Affichage des pions tours

	Texture image_tour;

	image_tour.loadFromFile("./donnees/rook.png");

	Sprite sprite_tour;

	image_tour.setSmooth(true);

	sprite_tour.setTexture(image_tour);

	sprite_tour.setScale(0.6f, 0.6f);

	sprite_tour.setPosition(30, 580);

	Texture image_tour2;

	image_tour2.loadFromFile("./donnees/rook.png");

	Sprite sprite_tour2;

	image_tour2.setSmooth(true);

	sprite_tour2.setTexture(image_tour2);

	sprite_tour2.setScale(0.6f, 0.6f);

	sprite_tour2.setPosition(585, 580);

	//Affichage des pions 

	Texture image_pion;

	image_pion.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion;

	image_pion.setSmooth(true);

	sprite_pion.setTexture(image_pion);

	sprite_pion.setScale(0.6f, 0.6f);

	sprite_pion.setPosition(30, 500);

	Texture image_pion2;

	image_pion2.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion2;

	image_pion2.setSmooth(true);

	sprite_pion2.setTexture(image_pion2);

	sprite_pion2.setScale(0.6f, 0.6f);

	sprite_pion2.setPosition(110, 500);

	Texture image_pion3;

	image_pion3.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion3;

	image_pion3.setSmooth(true);

	sprite_pion3.setTexture(image_pion3);

	sprite_pion3.setScale(0.6f, 0.6f);

	sprite_pion3.setPosition(190, 500);

	Texture image_pion4;

	image_pion4.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion4;

	image_pion4.setSmooth(true);

	sprite_pion4.setTexture(image_pion4);

	sprite_pion4.setScale(0.6f, 0.6f);

	sprite_pion4.setPosition(270, 500);

	Texture image_pion5;

	image_pion5.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion5;

	image_pion5.setSmooth(true);

	sprite_pion5.setTexture(image_pion5);

	sprite_pion5.setScale(0.6f, 0.6f);

	sprite_pion5.setPosition(350, 500);

	Texture image_pion6;

	image_pion6.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion6;

	image_pion6.setSmooth(true);

	sprite_pion6.setTexture(image_pion6);

	sprite_pion6.setScale(0.6f, 0.6f);

	sprite_pion6.setPosition(425, 500);

	Texture image_pion7;

	image_pion7.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion7;

	image_pion7.setSmooth(true);

	sprite_pion7.setTexture(image_pion7);

	sprite_pion7.setScale(0.6f, 0.6f);

	sprite_pion7.setPosition(505, 500);

	Texture image_pion8;

	image_pion8.loadFromFile("./donnees/pawn.png");

	Sprite sprite_pion8;

	image_pion8.setSmooth(true);

	sprite_pion8.setTexture(image_pion8);

	sprite_pion8.setScale(0.6f, 0.6f);

	sprite_pion8.setPosition(585, 500);
}
