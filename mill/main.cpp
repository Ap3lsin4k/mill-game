#include <SFML/Graphics.hpp>

#include<iostream>
#include <string>

using namespace sf;

const int sizeMill = 7;
const float sizeShape = 100.0f;
bool isCourseWhite = true;
bool isMouseClick = false;


void drawBuffer(CircleShape s,RenderWindow &win)
{
	if (isCourseWhite)
	{
		s.setFillColor(Color::White);
	}
	else
	{
		s.setFillColor(Color::Black);
	}
	s.setPosition(700.0f, 0.0f);
	win.draw(s);
}


int main()
{
	RenderWindow window(sf::VideoMode(sizeMill*sizeShape+sizeShape, sizeMill*sizeShape), "Mell ver.0.2.0");// размер шашки умножить на количество "полей"
	CircleShape shape(sizeShape/2.0f - 5);//в параметры функции передаэться радиус поэтому ми 100 делим на 2
										//и делаем ненамного меньше
//	shape.setFillColor(sf::Color::Black);
	Vector2i mouse;

	std::string masMill[]
	{
		"1001001",
		"0101010",
		"0011100",
		"1110111",
		"0011100",
		"0101010",
		"1001001",
	};//72 -20/10
	/*
	{
		"0011100",
		"0011100",
		"0011100",
		"1110111",
		"0011100",
		"0011100",
		"0011100",
	};//72 -20/10
	*/
	int k = 0;
	char helpChar;

	while (window.isOpen())
	{
		mouse = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();


			if (event.mouseButton.button == Mouse::Left)
			{
				isMouseClick = true;
			}

		}


		if (isMouseClick)
		{
			if (mouse.x > 0 && mouse.y > 0 && mouse.x < window.getSize().x - 100/*-100*/ && mouse.y < window.getSize().y)
			{
				//mouse / sizeMill == perevodum v massuv coordinate
				std::cout << int(mouse.y / sizeShape) << "\n";
				if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == '1')//if tudu mozhna postavutu point
				{
					//std::cout << << std::endl;
					std::cout << "\'1\'" << std::endl;
					if (isCourseWhite)
					{
						masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 'W';
						std::cout << 'W' << std::endl;
						isCourseWhite = false;
					}
					else
					{
						masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 'B';
						std::cout << 'B' << std::endl;
						isCourseWhite = true;
					}
				}
				else//if tudu ne mozhna postavutut point
				{

					std::cout << " \'0\'" << std::endl;
				}
			}
			isMouseClick = false;//для одноразового срабативания
		}
//if 3 pidrad
		///gorizontally 0;0 -> 0;6
			helpChar = masMill[0][0];
			
			k = 0;
			
				for (int i = 0; i < 6; i += 3)
				{
					if (masMill[0][i] == helpChar && masMill[0][i] != '1')
						k++;
				}
				if (k == 3)
				{
					std::cout << "YES!" << std::endl;
					//isEjectPawn=true; isCourseWhite = !isCourseWhite;
				}
		
			
		///vertically
			helpChar = masMill[1][1];
			k = 0;
			for (int i = 1; i < 5; i += 2)
			{
				if (masMill[0][i] == helpChar && masMill[0][i] != '1')
				{
					k++;
				}
			}
			if (k == 3)
			{
				std::cout << "YES!" << std::endl;
				//isEjectPawn=true; isCourseWhite = !isCourseWhite;
			}


		window.clear(Color(187,187,187,255));

		drawBuffer(shape, window);

		for (int countX=0; countX < sizeMill; countX++)
		{
			for (int countY=0; countY < sizeMill; countY++)
			{
				if (masMill[countY][countX] == 'W')
				{
					shape.setFillColor(Color::White);
					shape.setPosition(countX*sizeShape, countY*sizeShape);
					window.draw(shape);
				}
				if (masMill[countY][countX] == 'B')
				{
					shape.setFillColor(Color::Black);
					shape.setPosition(countX*sizeShape, countY*sizeShape);
					window.draw(shape);
				}
			}
		}
		window.display();
	}

	return 0;
}