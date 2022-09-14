#include <SFML/Graphics.hpp>


int main(int argc, char **argv)
{

	
	sf::RenderWindow window(sf::VideoMode(950, 950), "Jeux d'�chec");

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




	


	



	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		
		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(sprite);
		window.display();
		
		
	}

	return 0;
}