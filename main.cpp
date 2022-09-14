#include <SFML/Graphics.hpp>


int main(int argc, char **argv)
{

	
	sf::RenderWindow window(sf::VideoMode(950, 950), "Jeux d'échec");

	sf::Texture image;

	image.loadFromFile("./Image/echecdamier.gif");

	sf::Sprite sprite;
	image.setSmooth(true);


	

	sprite.setTexture(image);

	sprite.setScale(1.6f, 1.6f);

	sf::Texture image2;

	image2.loadFromFile("./Image/king.png");

	sf::Sprite sprite2;

	sprite2.setTexture(image2);




	


	



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
		window.draw(sprite);
		window.display();
		
		
	}

	return 0;
}