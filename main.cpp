#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;

void main(int argc, char **argv)
{


	RenderWindow window(sf::VideoMode(960, 720), "Echecs", Style::Default);

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

				if (event.type == Event::MouseButtonPressed)
				{

					if (event.mouseButton.button == Mouse::Left)
					{
						RenderWindow Play(VideoMode(960, 720), "Echecs");
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
									if (aevent.type == Event::MouseButtonReleased)
									{
										if (aevent.mouseButton.button == Mouse::Left)
										{
											Play.close();
										}
									}
								}
								Instructions.close();
								Options.close();
								Play.clear();

								Play.draw(Pbackground);

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
									if (aevent.type == Event::MouseButtonReleased)
									{
										if (aevent.mouseButton.button == Mouse::Left)
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
									if (aevent.type == Event::MouseButtonReleased)
									{
										if (aevent.mouseButton.button == Mouse::Left)
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

							while (Play.isOpen())
							{
								Event aevent;
								while (Play.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Play.close();

									}

								}
								Play.clear();

								Play.draw(Pbackground);

								Play.display();
							}
						}

					if (event.mouseButton.x >= 343 && event.mouseButton.y >= 305)
					{
						if (event.mouseButton.x <= 623 && event.mouseButton.y <= 341)
						{
							window.close();
							RenderWindow Instructions(VideoMode(960, 720), "Instructions");

							while (Instructions.isOpen())
							{
								Event aevent;
								while (Instructions.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Instructions.close();
									}
										
								}
									
								Instructions.clear();
									

								Instructions.draw(Ibackground);

								Instructions.display();
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