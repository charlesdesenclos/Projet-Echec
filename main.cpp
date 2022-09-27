#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "AfficheNP.h"
#include "Instructions.h"
#include "Plateau.h"

using namespace sf;

void main(int argc, char **argv)
{


	RenderWindow window(sf::VideoMode(960, 720), "Echecs", Style::Default);
	window.setFramerateLimit(60);

	Menu menu(window.getSize().x, window.getSize().y);

	
	// Affichage du thème à la page d'accueil

	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture texture;
	texture.loadFromFile("donnees/imagefond.jpg");
	background.setTexture(&texture);

	// Affichage du thème à la page du choix solo ou multi

	RectangleShape Pbackground;
	Pbackground.setSize(Vector2f(960, 720));
	Texture Play_texture;
	Play_texture.loadFromFile("donnees/imagefond.jpg");
	Pbackground.setTexture(&Play_texture);

	// Affichage du thème à la page d'Instructions

	RectangleShape Ibackground;
	Ibackground.setSize(Vector2f(960, 720));
	Texture Instructions_texture;
	Instructions_texture.loadFromFile("donnees/imagefond.jpg");
	Ibackground.setTexture(&Instructions_texture);

	// Affichage du thème à la page d'options

	RectangleShape Obackground;
	Obackground.setSize(Vector2f(960, 720));
	Texture Options_texture;
	Options_texture.loadFromFile("donnees/imagefond.jpg");
	Obackground.setTexture(&Options_texture);


	//Affichage général
	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}

				if (event.key.code == Keyboard::Return)
				{
					RenderWindow Play(VideoMode(960, 720), "Echecs");
					Play.setFramerateLimit(60);

					AfficheNP AfficheNP(Play.getSize().x, Play.getSize().y);
					RenderWindow Instructions(VideoMode(960, 720), "Instructions");
					RenderWindow Options(VideoMode(960, 720), "Options");


					int x = menu.MenuPressed();
					if (x == 0)
					{
						while (Play.isOpen())
						{
							Event aevent;
							while (Play.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Play.close();

								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Play.close();
									}
								}
							}
							Instructions.close();
							Options.close();
							Play.clear();

							Play.draw(Pbackground);

							AfficheNP.draw(Play);

							Play.display();
						}

					}
					if (x == 1)
					{
						while (Instructions.isOpen())
						{
							Event aevent;
							while (Instructions.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Instructions.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Instructions.close();
									}
								}
							}
							Play.close();
							Instructions.clear();
							Options.close();

							Instructions.draw(Ibackground);

							Instructions.display();


						}
					}
					if (x == 2)
					{
						while (Options.isOpen())
						{
							Event aevent;
							while (Options.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Options.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Options.close();
									}
								}
							}
							Play.close();
							Instructions.clear();
							Options.clear();

							Options.draw(Obackground);

							Options.display();

						}
					}

					if (x == 3)
					{
						window.close();
						break;
					}

				}

			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					
					//printf("%d %d\n", event.mouseButton.x, event.mouseButton.y);
					
					if (event.mouseButton.x >= 337 && event.mouseButton.y >= 199)
					{
						if (event.mouseButton.x <= 750 && event.mouseButton.y <= 245)
						{
							window.close();
							RenderWindow Play(VideoMode(960, 720), "Echecs");
							Play.setFramerateLimit(60);

							AfficheNP AfficheNP(Play.getSize().x, Play.getSize().y);

							
							

							while (Play.isOpen())
							{
								
								Event aevent;
								while (Play.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Play.close();

									}

									if (aevent.type == Event::MouseButtonPressed)
									{
										if (aevent.mouseButton.button == Mouse::Left)
										{
											if (aevent.mouseButton.x >= 337 && aevent.mouseButton.y >= 199)
											{
												if (aevent.mouseButton.x <= 750 && aevent.mouseButton.y <= 245)
												{

													
													Play.close();
													RenderWindow Plateaux(VideoMode(960, 720), "Plateau");
													Plateaux.setFramerateLimit(30);

													// Affichage Plateau

													Texture image;

													image.loadFromFile("./donnees/board.png");

													Sprite sprite;
													image.setSmooth(true);
													sprite.setTexture(image);

													sprite.setScale(1.4f, 1.4f);

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

													//Affichage pion noir

													//Affichage pion roi

													Texture image_roin;

													image_roin.loadFromFile("./donnees/king.png");

													Sprite sprite_roin;

													image_roin.setSmooth(true);

													sprite_roin.setTexture(image_roin);

													sprite_roin.setColor(Color::Black);

													sprite_roin.setScale(0.6f, 0.6f);

													sprite_roin.setPosition(350, 30);

													//Affichage pion reine

													Texture image_reinen;

													image_reinen.loadFromFile("./donnees/queen.png");

													Sprite sprite_reinen;

													image_reinen.setSmooth(true);

													sprite_reinen.setTexture(image_reinen);

													sprite_reinen.setColor(Color::Black);

													sprite_reinen.setScale(0.6f, 0.6f);

													sprite_reinen.setPosition(270, 30);

													//Affichage des pions fou 

													Texture image_foun;

													image_foun.loadFromFile("./donnees/fou.png");

													Sprite sprite_foun;

													image_foun.setSmooth(true);

													sprite_foun.setTexture(image_foun);

													sprite_foun.setColor(Color::Black);

													sprite_foun.setScale(0.6f, 0.6f);

													sprite_foun.setPosition(190, 30);

													Texture image_fou2n;

													image_fou2n.loadFromFile("./donnees/fou.png");

													Sprite sprite_fou2n;

													image_foun.setSmooth(true);

													sprite_fou2n.setTexture(image_fou2n);

													sprite_fou2n.setColor(Color::Black);

													sprite_fou2n.setScale(0.6f, 0.6f);

													sprite_fou2n.setPosition(425, 30);

													//Affichage des pions chevaliers

													Texture image_chavaliern;

													image_chavaliern.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevaliern;

													image_chavaliern.setSmooth(true);

													sprite_chevaliern.setTexture(image_chavaliern);

													sprite_chevaliern.setColor(Color::Black);

													sprite_chevaliern.setScale(0.6f, 0.6f);

													sprite_chevaliern.setPosition(110, 30);

													Texture image_chevalier2n;

													image_chevalier2n.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevalier2n;

													image_chevalier2n.setSmooth(true);

													sprite_chevalier2n.setTexture(image_chevalier2n);

													sprite_chevalier2n.setColor(Color::Black);

													sprite_chevalier2n.setScale(0.6f, 0.6f);

													sprite_chevalier2n.setPosition(505, 30);

													//Affichage des pions tours

													Texture image_tourn;

													image_tourn.loadFromFile("./donnees/rook.png");

													Sprite sprite_tourn;

													image_tourn.setSmooth(true);

													sprite_tourn.setTexture(image_tourn);

													sprite_tourn.setColor(Color::Black);

													sprite_tourn.setScale(0.6f, 0.6f);

													sprite_tourn.setPosition(30, 30);

													Texture image_tour2n;

													image_tour2n.loadFromFile("./donnees/rook.png");

													Sprite sprite_tour2n;

													image_tour2n.setSmooth(true);

													sprite_tour2n.setTexture(image_tour2n);

													sprite_tour2n.setColor(Color::Black);

													sprite_tour2n.setScale(0.6f, 0.6f);

													sprite_tour2n.setPosition(585, 30);

													//Affichage des pions 

													Texture image_pionn;

													image_pionn.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pionn;

													image_pionn.setSmooth(true);

													sprite_pionn.setTexture(image_pionn);

													sprite_pionn.setColor(Color::Black);

													sprite_pionn.setScale(0.6f, 0.6f);

													sprite_pionn.setPosition(30, 110);

													Texture image_pion2n;

													image_pion2n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion2n;

													image_pion2n.setSmooth(true);

													sprite_pion2n.setTexture(image_pion2n);

													sprite_pion2n.setColor(Color::Black);

													sprite_pion2n.setScale(0.6f, 0.6f);

													sprite_pion2n.setPosition(110, 110);

													Texture image_pion3n;

													image_pion3n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion3n;

													image_pion3n.setSmooth(true);

													sprite_pion3n.setTexture(image_pion3n);

													sprite_pion3n.setColor(Color::Black);

													sprite_pion3n.setScale(0.6f, 0.6f);

													sprite_pion3n.setPosition(190, 110);

													Texture image_pion4n;

													image_pion4n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion4n;

													image_pion4n.setSmooth(true);

													sprite_pion4n.setTexture(image_pion4n);

													sprite_pion4n.setColor(Color::Black);

													sprite_pion4n.setScale(0.6f, 0.6f);

													sprite_pion4n.setPosition(270, 110);

													Texture image_pion5n;

													image_pion5n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion5n;

													image_pion5n.setSmooth(true);

													sprite_pion5n.setTexture(image_pion5n);

													sprite_pion5n.setColor(Color::Black);

													sprite_pion5n.setScale(0.6f, 0.6f);

													sprite_pion5n.setPosition(350, 110);

													Texture image_pion6n;

													image_pion6n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion6n;

													image_pion6n.setSmooth(true);

													sprite_pion6n.setTexture(image_pion6n);

													sprite_pion6n.setColor(Color::Black);

													sprite_pion6n.setScale(0.6f, 0.6f);

													sprite_pion6n.setPosition(425, 110);

													Texture image_pion7n;

													image_pion7n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion7n;

													image_pion7n.setSmooth(true);

													sprite_pion7n.setTexture(image_pion7n);

													sprite_pion7n.setColor(Color::Black);

													sprite_pion7n.setScale(0.6f, 0.6f);

													sprite_pion7n.setPosition(505, 110);

													Texture image_pion8n;

													image_pion8n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion8n;

													image_pion8n.setSmooth(true);

													sprite_pion8n.setTexture(image_pion8n);

													sprite_pion8n.setColor(Color::Black);

													sprite_pion8n.setScale(0.6f, 0.6f);

													sprite_pion8n.setPosition(585, 110);
													
													
													while (Plateaux.isOpen())
													{
														




														
														
														Event aevent;
														while (Plateaux.pollEvent(aevent))
														{
															if (aevent.type == Event::Closed)
															{
																Plateaux.close();
															}

														}

														Plateaux.clear();


														Plateaux.draw(sprite);

														Plateaux.draw(sprite_roi);

														Plateaux.draw(sprite_reine);

														Plateaux.draw(sprite_fou);

														Plateaux.draw(sprite_fou2);

														Plateaux.draw(sprite_chevalier);

														Plateaux.draw(sprite_chevalier2);

														Plateaux.draw(sprite_tour);

														Plateaux.draw(sprite_tour2);

														Plateaux.draw(sprite_pion);

														Plateaux.draw(sprite_pion2);

														Plateaux.draw(sprite_pion3);

														Plateaux.draw(sprite_pion4);

														Plateaux.draw(sprite_pion5);

														Plateaux.draw(sprite_pion6);

														Plateaux.draw(sprite_pion7);

														Plateaux.draw(sprite_pion8);

														Plateaux.draw(sprite_roin);

														Plateaux.draw(sprite_reinen);

														Plateaux.draw(sprite_foun);

														Plateaux.draw(sprite_fou2n);

														Plateaux.draw(sprite_chevaliern);

														Plateaux.draw(sprite_chevalier2n);

														Plateaux.draw(sprite_tourn);

														Plateaux.draw(sprite_tour2n);

														Plateaux.draw(sprite_pionn);

														Plateaux.draw(sprite_pion2n);

														Plateaux.draw(sprite_pion3n);

														Plateaux.draw(sprite_pion4n);

														Plateaux.draw(sprite_pion5n);

														Plateaux.draw(sprite_pion6n);

														Plateaux.draw(sprite_pion7n);

														Plateaux.draw(sprite_pion8n);

														Plateaux.display();

														
													}
													
												}
											}
											if (aevent.mouseButton.x >= 343 && aevent.mouseButton.y >= 305)
											{
												if (aevent.mouseButton.x <= 623 && aevent.mouseButton.y <= 341)
												{
													Play.close();
													RenderWindow Multi(VideoMode(960, 720), "Multi");
													Multi.setFramerateLimit(30);

													// Affichage Plateau

													Texture image;

													image.loadFromFile("./donnees/board.png");

													Sprite sprite;
													image.setSmooth(true);
													sprite.setTexture(image);

													sprite.setScale(1.4f, 1.4f);

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

													//Affichage pion noir

													//Affichage pion roi

													Texture image_roin;

													image_roin.loadFromFile("./donnees/king.png");

													Sprite sprite_roin;

													image_roin.setSmooth(true);

													sprite_roin.setTexture(image_roin);

													sprite_roin.setColor(Color::Black);

													sprite_roin.setScale(0.6f, 0.6f);

													sprite_roin.setPosition(350, 30);

													//Affichage pion reine

													Texture image_reinen;

													image_reinen.loadFromFile("./donnees/queen.png");

													Sprite sprite_reinen;

													image_reinen.setSmooth(true);

													sprite_reinen.setTexture(image_reinen);

													sprite_reinen.setColor(Color::Black);

													sprite_reinen.setScale(0.6f, 0.6f);

													sprite_reinen.setPosition(270, 30);

													//Affichage des pions fou 

													Texture image_foun;

													image_foun.loadFromFile("./donnees/fou.png");

													Sprite sprite_foun;

													image_foun.setSmooth(true);

													sprite_foun.setTexture(image_foun);

													sprite_foun.setColor(Color::Black);

													sprite_foun.setScale(0.6f, 0.6f);

													sprite_foun.setPosition(190, 30);

													Texture image_fou2n;

													image_fou2n.loadFromFile("./donnees/fou.png");

													Sprite sprite_fou2n;

													image_foun.setSmooth(true);

													sprite_fou2n.setTexture(image_fou2n);

													sprite_fou2n.setColor(Color::Black);

													sprite_fou2n.setScale(0.6f, 0.6f);

													sprite_fou2n.setPosition(425, 30);

													//Affichage des pions chevaliers

													Texture image_chavaliern;

													image_chavaliern.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevaliern;

													image_chavaliern.setSmooth(true);

													sprite_chevaliern.setTexture(image_chavaliern);

													sprite_chevaliern.setColor(Color::Black);

													sprite_chevaliern.setScale(0.6f, 0.6f);

													sprite_chevaliern.setPosition(110, 30);

													Texture image_chevalier2n;

													image_chevalier2n.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevalier2n;

													image_chevalier2n.setSmooth(true);

													sprite_chevalier2n.setTexture(image_chevalier2n);

													sprite_chevalier2n.setColor(Color::Black);

													sprite_chevalier2n.setScale(0.6f, 0.6f);

													sprite_chevalier2n.setPosition(505, 30);

													//Affichage des pions tours

													Texture image_tourn;

													image_tourn.loadFromFile("./donnees/rook.png");

													Sprite sprite_tourn;

													image_tourn.setSmooth(true);

													sprite_tourn.setTexture(image_tourn);

													sprite_tourn.setColor(Color::Black);

													sprite_tourn.setScale(0.6f, 0.6f);

													sprite_tourn.setPosition(30, 30);

													Texture image_tour2n;

													image_tour2n.loadFromFile("./donnees/rook.png");

													Sprite sprite_tour2n;

													image_tour2n.setSmooth(true);

													sprite_tour2n.setTexture(image_tour2n);

													sprite_tour2n.setColor(Color::Black);

													sprite_tour2n.setScale(0.6f, 0.6f);

													sprite_tour2n.setPosition(585, 30);

													//Affichage des pions 

													Texture image_pionn;

													image_pionn.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pionn;

													image_pionn.setSmooth(true);

													sprite_pionn.setTexture(image_pionn);

													sprite_pionn.setColor(Color::Black);

													sprite_pionn.setScale(0.6f, 0.6f);

													sprite_pionn.setPosition(30, 110);

													Texture image_pion2n;

													image_pion2n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion2n;

													image_pion2n.setSmooth(true);

													sprite_pion2n.setTexture(image_pion2n);

													sprite_pion2n.setColor(Color::Black);

													sprite_pion2n.setScale(0.6f, 0.6f);

													sprite_pion2n.setPosition(110, 110);

													Texture image_pion3n;

													image_pion3n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion3n;

													image_pion3n.setSmooth(true);

													sprite_pion3n.setTexture(image_pion3n);

													sprite_pion3n.setColor(Color::Black);

													sprite_pion3n.setScale(0.6f, 0.6f);

													sprite_pion3n.setPosition(190, 110);

													Texture image_pion4n;

													image_pion4n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion4n;

													image_pion4n.setSmooth(true);

													sprite_pion4n.setTexture(image_pion4n);

													sprite_pion4n.setColor(Color::Black);

													sprite_pion4n.setScale(0.6f, 0.6f);

													sprite_pion4n.setPosition(270, 110);

													Texture image_pion5n;

													image_pion5n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion5n;

													image_pion5n.setSmooth(true);

													sprite_pion5n.setTexture(image_pion5n);

													sprite_pion5n.setColor(Color::Black);

													sprite_pion5n.setScale(0.6f, 0.6f);

													sprite_pion5n.setPosition(350, 110);

													Texture image_pion6n;

													image_pion6n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion6n;

													image_pion6n.setSmooth(true);

													sprite_pion6n.setTexture(image_pion6n);

													sprite_pion6n.setColor(Color::Black);

													sprite_pion6n.setScale(0.6f, 0.6f);

													sprite_pion6n.setPosition(425, 110);

													Texture image_pion7n;

													image_pion7n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion7n;

													image_pion7n.setSmooth(true);

													sprite_pion7n.setTexture(image_pion7n);

													sprite_pion7n.setColor(Color::Black);

													sprite_pion7n.setScale(0.6f, 0.6f);

													sprite_pion7n.setPosition(505, 110);

													Texture image_pion8n;

													image_pion8n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion8n;

													image_pion8n.setSmooth(true);

													sprite_pion8n.setTexture(image_pion8n);

													sprite_pion8n.setColor(Color::Black);

													sprite_pion8n.setScale(0.6f, 0.6f);

													sprite_pion8n.setPosition(585, 110);

													while (Multi.isOpen())
													{
														Event aevent;
														while (Multi.pollEvent(aevent))
														{
															if (aevent.type == Event::Closed)
															{
																Multi.close();
															}

														}

														Multi.clear();


														Multi.draw(sprite);

														Multi.draw(sprite_roi);

														Multi.draw(sprite_reine);

														Multi.draw(sprite_fou);

														Multi.draw(sprite_fou2);

														Multi.draw(sprite_chevalier);

														Multi.draw(sprite_chevalier2);

														Multi.draw(sprite_tour);

														Multi.draw(sprite_tour2);

														Multi.draw(sprite_pion);

														Multi.draw(sprite_pion2);

														Multi.draw(sprite_pion3);

														Multi.draw(sprite_pion4);

														Multi.draw(sprite_pion5);

														Multi.draw(sprite_pion6);

														Multi.draw(sprite_pion7);

														Multi.draw(sprite_pion8);

														Multi.draw(sprite_roin);

														Multi.draw(sprite_reinen);

														Multi.draw(sprite_foun);

														Multi.draw(sprite_fou2n);

														Multi.draw(sprite_chevaliern);

														Multi.draw(sprite_chevalier2n);

														Multi.draw(sprite_tourn);

														Multi.draw(sprite_tour2n);

														Multi.draw(sprite_pionn);

														Multi.draw(sprite_pion2n);

														Multi.draw(sprite_pion3n);

														Multi.draw(sprite_pion4n);

														Multi.draw(sprite_pion5n);

														Multi.draw(sprite_pion6n);

														Multi.draw(sprite_pion7n);

														Multi.draw(sprite_pion8n);

														Multi.display();
													}
												}
											}
										}

									}

								}
								Play.clear();

								Play.draw(Pbackground);



								AfficheNP.draw(Play);

								Play.display();
							}
							
						}

					if (event.mouseButton.x >= 343 && event.mouseButton.y >= 305)
					{
						if (event.mouseButton.x <= 623 && event.mouseButton.y <= 341)
						{
							window.close();
							RenderWindow Instruction(VideoMode(960, 720), "Instructions");

							Instructions Instructions(Instruction.getSize().x, Instruction.getSize().y);

							while (Instruction.isOpen())
							{
								Event aevent;
								while (Instruction.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Instruction.close();
									}


										
								}
									
								Instruction.clear();
									

								Instruction.draw(Ibackground);

								Instructions.draw(Instruction);

								Instruction.display();
							}
						}
					}
					if (event.mouseButton.x >= 340 && event.mouseButton.y >= 400)
					{
						if (event.mouseButton.x <= 513 && event.mouseButton.y <= 443)
						{
							window.close();
							RenderWindow Options(VideoMode(960, 720), "Options");

							while (Options.isOpen())
							{
								Event aevent;
								while (Options.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Options.close();
									}
									
								}
								Options.clear();

								Options.draw(Obackground);

								Options.display();

							}
						}

					}

					if (event.mouseButton.x >= 342 && event.mouseButton.y >= 503)
					{
						if (event.mouseButton.x <= 524 && event.mouseButton.y <= 545)
						{
							window.close();
							break;
						}

					}
				}
					
					
			}
			}

			window.clear();
			window.draw(background);
			menu.draw(window);
			window.display();

			


		}





	}
}