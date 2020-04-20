#ifndef menu_H
#define menu_H

#include <SFML/Graphics.hpp>

using namespace sf;

Color colBackGround = Color(255, 135, 0 , 255);


short int menu () {
	RenderWindow window1(sf::VideoMode(7*100 + 100, 7*100), "Menu");
	Texture  menuBackground;
	menuBackground.loadFromFile("images/Penguins.jpg");
	Sprite menuBg(menuBackground);

	int sizeFont = 45;

	Font fontKurale;
	fontKurale.loadFromFile("font/10369.ttf");
	Text newGame("New Game 1x1", fontKurale, 45);
	Text newGameComputer("New game with computer", fontKurale, 45);
	Text Exit("Exit", fontKurale, 45);


	bool isMenu = 1;
	int menuNum = 0;
	Vector2i mouse;


	menuBg.setPosition(0, 0);
	newGame.setPosition(0, 0);
	newGameComputer.setPosition(0, sizeFont);
	Exit.setPosition(0, sizeFont * 2);


	//////////////////////////////МЕНЮ///////////////////
	while (window1.isOpen())
	{
		mouse = Mouse::getPosition(window1);



		newGame.setFillColor(Color(255, 255, 255, 255));
		newGameComputer.setFillColor(Color(255, 255, 255, 255));
		Exit.setFillColor(Color::White);
		menuNum = 0;

		if (IntRect(0, 0, 500, sizeFont).contains(Mouse::getPosition(window1))) { newGame.setFillColor(Color(198, 62, 0, 255)); menuNum = 1; }
		if (IntRect(0, sizeFont, 500, sizeFont).contains(Mouse::getPosition(window1))) { newGameComputer.setFillColor(Color(198, 62, 0, 255)); menuNum = 2; }
		if (IntRect(0, sizeFont * 2, 500, sizeFont).contains(Mouse::getPosition(window1))) { Exit.setFillColor(Color(198, 62, 0, 255)); menuNum = 3; }


		Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window1.close();
				return 0;
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window1.close();
					return 0;
				}
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{

					if (menuNum == 1) { return 1; }//1x1//isMenu = false;//если нажали первую кнопку, то выходим из меню 
					if (menuNum == 2) { return 2; }//computer
					if (menuNum == 3) { window1.close(); return 0; }
				}
			}

		}


		window1.clear(colBackGround);//c63e
		//window1.clear(Color(129, 181, 221));
		
	//	window1.draw(menuBg);
		window1.draw(newGame);
		window1.draw(newGameComputer);
		window1.draw(Exit);

		window1.display();
	}
	////////////////////////////////////////////////////
}


void wonWhite()
{
	RenderWindow window1(sf::VideoMode(7 * 100 + 100, 7 * 100), "Menu");
	int sizeFont = 45;

	Font fontKurale;
	fontKurale.loadFromFile("font/10369.ttf");
	Text winText("won WHITE", fontKurale, 45);




	//////////////////////////////МЕНЮ///////////////////
	while (window1.isOpen())
	{


		Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window1.close();
				return;
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window1.close();
					return;
				}
			}

		}


		window1.clear(Color(colBackGround));

		//	window1.draw(menuBg);
		window1.draw(winText);
		window1.display();
	}
	////////////////////////////////////////////////////
}

void wonBlack()
{
	RenderWindow window1(sf::VideoMode(7 * 100 + 100, 7 * 100), "Menu");
	int sizeFont = 45;

	Font fontKurale;
	fontKurale.loadFromFile("font/10369.ttf");
	Text winText("won BLACK", fontKurale, 45);




	//////////////////////////////МЕНЮ///////////////////
	while (window1.isOpen())
	{


		Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window1.close();
				return;
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window1.close();
					return;
				}
			}

		}



		window1.clear(Color(colBackGround));

		//	window1.draw(menuBg);
		window1.draw(winText);
		window1.display();
	}
	////////////////////////////////////////////////////
}

/*
void Nichuya()
{
	
}*/
#endif // !menu_H