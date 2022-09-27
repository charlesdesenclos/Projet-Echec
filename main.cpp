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

													Texture image;

													image.loadFromFile("./donnees/board.png");

													Sprite sprite;
													image.setSmooth(true);
													sprite.setTexture(image);

													sprite.setScale(1.4f, 1.4f);

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