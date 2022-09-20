#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

int main(int argc, char **argv)
{


	sf::Window window(sf::VideoMode(800, 600), "Echecs");

	Menu menu(window.getSize().x,window.getSize().y);

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			

			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		menu.draw(window);

		window.display();
	}

	


	return 0;
}