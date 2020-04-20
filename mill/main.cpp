#include <SFML/Graphics.hpp>

#include<iostream>
#include <string>
#include <cmath>
#include "menu.h"
#include "computer.h"

using namespace sf;

#include "computer.h"

const int sizeMill = 7;
const float sizeShape = 100.0f;

bool isCourseWhite = true;
bool isMouseClick = false;
bool isStepDelete = false;

char helpChar;
short int oldY = 0, oldX = 0;

struct pawn {
	short int numberMove = 9;
	short int amountPawn = 0;

	char update()
	{
		if (numberMove == 0)
		{
			if (amountPawn <= 2)
			{
				if (isCourseWhite)
				{
					return 'B';
				}
				else if (!isCourseWhite)
				{
					return 'W';
				}
			}

		}

		return '0';
	}
};



//prototipe
void check(std::string array[], short int indexHelpChar1, short int indexHelpChar2,
	short int indexIBegin, short int indexIEnd, short int stepI,
	short int indexJBegin, short int indexJEnd, short int stepJ
	, bool redArr[][sizeMill]
);

void drawBuffer(CircleShape s, RenderWindow &win);

void movement(std::string masMill[], bool redArray[][sizeMill], Vector2i mouse);

void basePossibleMoves(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m);

void WhereWeGo(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m);



char regime1()
{

	RenderWindow window(sf::VideoMode(sizeMill*sizeShape + sizeShape, sizeMill*sizeShape), "Game");// размер шашки умножить на количество "полей"
	
	CircleShape shape(sizeShape / 2.0f - 10);//в параметры функции передаэться радиус поэтому ми 100 делим на 2
											 //и делаем ненамного меньше
	shape.setOrigin(Vector2f(shape.getRadius(), shape.getRadius()));


	Texture textBackGround;
	textBackGround.loadFromFile("images/photo/Tile04.bmp");
	Sprite backGround(textBackGround);
	backGround.setScale(0.4375, 0.4375);

	RectangleShape rect;
	rect.setSize(Vector2f(sizeShape, sizeShape));
	//rect.
	//	shape.setFillColor(sf::Color::Black);
	Vector2i mouse;

	std::string masMill[]
	{
		//	  0123456	
		/*0*/"1001001",
		/*1*/"0101010",
		/*2*/"0011100",
		/*3*/"1110111",
		/*4*/"0011100",
		/*5*/"0101010",
		/*6*/"1001001",
	};//72 -20/10
	bool redArray[sizeMill][sizeMill]
	{
		{ 00000 },
		{ 00000 },
		{ 00000 },
		{ 00000 },
		{ 00000 },
		{ 00000 },
	};

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

	pawn pW;
	pawn pB;



	while (window.isOpen())
	{
		mouse = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return '0';
			}


			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					isMouseClick = true;
				}
			}

		}


		if (isMouseClick)
		{
			if (mouse.x > 0 && mouse.y > 0 && mouse.x < window.getSize().x - 100/*-100*/ && mouse.y < window.getSize().y)
			{
		
				if (isStepDelete)
				{
					if (isCourseWhite)
					{
						if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == 'B')
						{
							masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = '1';
							isCourseWhite = false;
							isStepDelete = false;
							isMouseClick = false;
							pB.amountPawn--;

							for (int i = 0; i < sizeMill; i++)
								for (int j = 0; j < sizeMill; j++)
									redArray[i][j] = 0;

							//	redArray[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 2;
						}
					}
					else if (!isCourseWhite)
					{
						if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == 'W')
						{
							masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = '1';
							isCourseWhite = true;
							isStepDelete = false;
							isMouseClick = false;
							pW.amountPawn--;//зменшуємо к-сть пішаків

							for (int i = 0; i < sizeMill; i++)
								for (int j = 0; j < sizeMill; j++)
									redArray[i][j] = 0;

							//	redArray[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 2;
						}
					}
				}
				else
				{
					if (pB.numberMove > 0)
					{

						if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == '1')//if tudu mozhna postavutu point
						{
							
							if (isCourseWhite)
							{
								masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 'W';

								redArray[oldY][oldX] = 0;
								oldY = int(mouse.y / sizeShape);
								oldX = int(mouse.x / sizeShape);

								redArray[oldY][oldX] = 1;
							
								pW.numberMove--;
								pW.amountPawn++;
								isCourseWhite = false;

								WhereWeGo(masMill, redArray, mouse);

							}
							else
							{
								masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 'B';

								redArray[oldY][oldX] = 0;
								oldY = int(mouse.y / sizeShape);
								oldX = int(mouse.x / sizeShape);

								redArray[oldY][oldX] = 1;
							
								pB.numberMove--;
								pB.amountPawn++;
								isCourseWhite = true;


								WhereWeGo(masMill, redArray, mouse);

							}

						}
					}
					else //peredvuganie
					{
						short int newX = int(mouse.x / sizeShape);
						short int newY = int(mouse.y / sizeShape);


						if (isCourseWhite)
						{

							if (masMill[newY][newX] == 'W' || masMill[newY][newX] == 'w')
							{
								redArray[oldY][oldX] = 0;
								oldX = newX;
								oldY = newY;
								redArray[oldY][oldX] = 1;
							}
							if (masMill[oldY][oldX] == 'W' || masMill[oldY][oldX] == 'w')
							{
								if (masMill[newY][newX] == '1')
								{
									basePossibleMoves(masMill, redArray, mouse);
								}
							}
						}
						else if (!isCourseWhite)
						{

							if (masMill[newY][newX] == 'B' || masMill[newY][newX] == 'b')
							{
								redArray[oldY][oldX] = 0;
								oldX = newX;
								oldY = newY;
								redArray[oldY][oldX] = 1;
							}
							if (masMill[oldY][oldX] == 'B' || masMill[oldY][oldX] == 'b')
							{
								if (masMill[newY][newX] == '1')
								{
									basePossibleMoves(masMill, redArray, mouse);
								}
							}
						}


					}
					isMouseClick = false;//для одноразового срабативания
				}
			}
			isMouseClick = false;
		}


		if (pB.update() == 'W')
		{
			return 'W';
		}
		if (pW.update() == 'B')
		{
			return 'B';
		}
		//draw


		window.clear(sf::Color(colBackGround));
		//		window.clear(Color::White);
		drawBuffer(shape, window);
		window.draw(backGround);
		for (int countX = 0; countX < sizeMill; countX++)
		{
			for (int countY = 0; countY < sizeMill; countY++)
			{
				/*

				if (masMill[countY][countX] == '0')
				{
				rect.setFillColor(sf::Color(250, 250, 250, 255));
				rect.setPosition(countX*sizeShape, countY*sizeShape);
				window.draw(rect);
				}
				else
				{
				rect.setFillColor(sf::Color(187, 187, 187, 255));
				rect.setPosition(countX*sizeShape, countY*sizeShape);
				window.draw(rect);
				}*/
				if (redArray[countY][countX] == 1)
				{
					rect.setFillColor(sf::Color(255, 255, 0, 100));//Yellow
					rect.setPosition(countX*sizeShape, countY*sizeShape);
					window.draw(rect);
				}

				//window.draw(backGround);

				if (masMill[countY][countX] == 'W' || masMill[countY][countX] == 'w')
				{
					shape.setFillColor(sf::Color::White);
					shape.setPosition((countX*sizeShape + sizeShape / 2), countY*sizeShape + (sizeShape / 2));
					window.draw(shape);
				}
				if (masMill[countY][countX] == 'B' || masMill[countY][countX] == 'b')
				{
					shape.setFillColor(sf::Color::Black);
					shape.setPosition(countX*sizeShape + sizeShape / 2, countY*sizeShape + sizeShape / 2);
					window.draw(shape);
				}
			}
		}
		window.display();
	}
}



int main()
{
	short int returnMainMenu = menu();

	if (returnMainMenu == 0)
	{
		return 0;
	}
	else if (returnMainMenu == 1)
	{
		char whoWon;//0==W; 1==B
		whoWon = regime1();

		if (whoWon == '0')
		{
			//Nichuya();
		}
		else if (whoWon =='W')
		{
			wonWhite();
		}
		else {
			wonBlack();
		}
		return 1;


	}
	else if (returnMainMenu == 2)
	{
		char whoWon;
		whoWon = mySpace::regime();

		if (whoWon == '0')
		{
			//Nichuya();
		}
		else if (whoWon == 'W')
		{
			wonWhite();
		}
		else {
			wonBlack();
		}

		return 2;
	}
}


//funct
void check(std::string array[], short int indexHelpChar1, short int indexHelpChar2,
	short int indexIBegin, short int indexIEnd, short int stepI,
	short int indexJBegin, short int indexJEnd, short int stepJ
	, bool redArr[][sizeMill]
)
{
	bool isRed = false;
	helpChar = array[indexHelpChar1][indexHelpChar2];

	int k = 0;

	for (int i = indexIBegin; i <= indexIEnd; i += stepI)
	{
		for (int j = indexJBegin; j <= indexJEnd; j += stepJ)
		{
	
			if (array[i][j] == helpChar && array[i][j] != '1' )
			{
				if (array[i][j] == 'W' || array[i][j] == 'B')
				{
					k++;
				//	if(redArr[i][j] == 1) isRed = true;
				}
			}
		}
	}
	
	if (k == 3)
	{
		isStepDelete = true;
		isCourseWhite = !isCourseWhite;

		//isEjectPawn=true; isCourseWhite = !isCourseWhite;
		for (int i = indexIBegin; i <= indexIEnd; i += stepI)
		{
			for (int j = indexJBegin; j <= indexJEnd; j += stepJ)
			{
				if (isCourseWhite)
				{
			//		array[i][j] = 'w';
				}
				else if (!isCourseWhite)
				{
			//		array[i][j] = 'b';
				}
			}
		}
	}
}

void drawBuffer(CircleShape s, RenderWindow &win)
{
	if (isCourseWhite)
	{
		s.setFillColor(Color::White);
	}
	else
	{
		s.setFillColor(Color::Black);
	}
	s.setPosition(7*sizeShape + +sizeShape / 2, +sizeShape / 2);
	win.draw(s);
}

void movement(std::string masMill[], bool redArray[][sizeMill], Vector2i mouse)
{
	//iif '1' exit

	masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = masMill[oldY][oldX];
	masMill[oldY][oldX] = '1';

	redArray[oldY][oldX] = 0;
	oldY = int(mouse.y / sizeShape);
	oldX = int(mouse.x / sizeShape);
	redArray[oldY][oldX] = 1;

	isCourseWhite = !isCourseWhite;

}


void basePossibleMoves(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m)
{
	short int newX = int(m.x / sizeShape), newY = int(m.y / sizeShape);
	/*
	if (!isStepDelete)
	{
	//gorisontalli up
	//	check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
	//	check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
	//	check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);

	//verticalli right
	//	check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
	//	check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
	//	check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);

	//gorisontal down
	//	check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
	//	check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
	//	check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);

	//verticalli left
	//	check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
	//	check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
	//	check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);

	//verticalli middle up
	//		check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);

	//verticalli middle right
	//		check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);

	//verticalli middle down
	//		check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);

	//verticalli middle left
	//		check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
	}
	*/
	//1 row
	if (newX == 0 && newY == 0)
	{
		if (oldX == 0 && oldY == 3 || oldX == 3 && oldY == 0)
		{
			movement(arrStr, arrBool, m);
			check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
			check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);

		}
	}

	if (newX == 3 && newY == 0)
	{
		if (oldX == 3 && oldY == 1 || oldX == 0 && oldY == 0 || oldX == 6 && oldY == 0)
		{
			movement(arrStr, arrBool, m);
			check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
			check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
		}
	}

	if (newX == 6 && newY == 0)
	{
		if (oldX == 6 && oldY == 3 || oldX == 3 && oldY == 0)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
			check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
		}
	}

	//2 row
	if (newX == 1 && newY == 1)
	{
		if (oldX == 3 && oldY == 1 || oldX == 1 && oldY == 3)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
			check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
		}
	}

	if (newX == 3 && newY == 1)
	{
		if (oldX == 3 && oldY == 2 || oldX == 1 && oldY == 1 || oldX == 3 && oldY == 0 || oldX == 5 && oldY == 1)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
			check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
		}
	}

	if (newX == 5 && newY == 1)
	{
		if (oldX == 5 && oldY == 3 || oldX == 3 && oldY == 1)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
			check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);

		}
	}

	//3 row
	if (newX == 2 && newY == 2)
	{
		if (oldX == 2 && oldY == 3 || oldX == 3 && oldY == 2)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
			check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);

		}
	}

	if (newX == 3 && newY == 2)
	{
		if (oldX == 2 && oldY == 2 || oldX == 3 && oldY == 1 || oldX == 4 && oldY == 2)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
			check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);

		}
	}

	if (newX == 4 && newY == 2)
	{
		if (oldX == 4 && oldY == 3 || oldX == 3 && oldY == 2)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
			check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
		}
	}

	//4 row
	if (newX == 0 && newY == 3)
	{
		if (oldX == 1 && oldY == 3 || oldX == 0 && oldY == 6 || oldX == 0 && oldY == 0)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
			check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
		}
	}

	if (newX == 1 && newY == 3)
	{
		if (oldX == 0 && oldY == 3 || oldX == 2 && oldY == 3 || oldX == 1 && oldY == 5 || oldX == 1 && oldY == 1)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
			check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
		}
	}

	if (newX == 2 && newY == 3)
	{
		if (oldX == 2 && oldY == 4 || oldX == 1 && oldY == 3 || oldX == 2 && oldY == 2)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
			check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
		}
	}

	if (newX == 4 && newY == 3)
	{
		if (oldX == 4 && oldY == 4 || oldX == 4 && oldY == 2 || oldX == 5 && oldY == 3)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
			check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
		}
	}

	if (newX == 5 && newY == 3)
	{
		if (oldX == 4 && oldY == 3 || oldX == 6 && oldY == 3 || oldX == 5 && oldY == 5 || oldX == 5 && oldY == 1)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
			check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
		}
	}

	if (newX == 6 && newY == 3)
	{
		if (oldX == 5 && oldY == 3 || oldX == 6 && oldY == 6 || oldX == 6 && oldY == 0)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
			check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
		}
	}

	//5 row

	if (newX == 2 && newY == 4)
	{
		if (oldX == 2 && oldY == 3 || oldX == 3 && oldY == 4)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
			check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
		}
	}

	if (newX == 3 && newY == 4)
	{
		if (oldX == 3 && oldY == 5 || oldX == 2 && oldY == 4 || oldX == 4 && oldY == 4)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
		}
	}

	if (newX == 4 && newY == 4)
	{
		if (oldX == 3 && oldY == 4 || oldX == 4 && oldY == 3)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
			check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
		}
	}

	//6 row
	if (newX == 1 && newY == 5)
	{
		if (oldX == 1 && oldY == 3 || oldX == 3 && oldY == 5)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
			check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
		}
	}

	if (newX == 3 && newY == 5)
	{
		if (oldX == 3 && oldY == 6 || oldX == 1 && oldY == 5 || oldX == 3 && oldY == 4 || oldX == 5 && oldY == 5)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
		}
	}

	if (newX == 5 && newY == 5)
	{
		if (oldX == 3 && oldY == 5 || oldX == 5 && oldY == 3)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
			check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
		}
	}

	//7 row
	if (newX == 0 && newY == 6)
	{
		if (oldX == 0 && oldY == 3 || oldX == 3 && oldY == 6)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
			check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
		}
	}

	if (newX == 3 && newY == 6)
	{
		if (oldX == 0 && oldY == 6 || oldX == 3 && oldY == 5 || oldX == 6 && oldY == 6)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
		}
	}

	if (newX == 6 && newY == 6)
	{
		if (oldX == 3 && oldY == 6 || oldX == 6 && oldY == 3)
		{
			movement(arrStr, arrBool, m);

			check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
			check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
		}
	}


}



void WhereWeGo(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m)
{
	short int newX = int(m.x / sizeShape), newY = int(m.y / sizeShape);

	//1 row
	if (newX == 0 && newY == 0)
	{
		check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
		check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
	}

	if (newX == 3 && newY == 0)
	{
		check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
		check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
	}

	if (newX == 6 && newY == 0)
	{
		check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
		check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
	}

	//2 row
	if (newX == 1 && newY == 1)
	{
		check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
		check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
	}

	if (newX == 3 && newY == 1)
	{
		check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
		check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
	}

	if (newX == 5 && newY == 1)
	{
		check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
		check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
	}

	//3 row
	if (newX == 2 && newY == 2)
	{
		check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
		check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
	}

	if (newX == 3 && newY == 2)
	{
		check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
		check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
	}

	if (newX == 4 && newY == 2)
	{
		check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
		check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
	}

	//4 row
	if (newX == 0 && newY == 3)
	{
		check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
		check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
	}

	if (newX == 1 && newY == 3)
	{
		check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
		check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
	}

	if (newX == 2 && newY == 3)
	{
		check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
		check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
	}

	if (newX == 4 && newY == 3)
	{
		check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
		check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
	}

	if (newX == 5 && newY == 3)
	{
		check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
		check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
	}

	if (newX == 6 && newY == 3)
	{
		check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
		check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
	}

	//5 row

	if (newX == 2 && newY == 4)
	{
		check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
		check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
	}

	if (newX == 3 && newY == 4)
	{
		check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
		check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
	}

	if (newX == 4 && newY == 4)
	{
		check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
		check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
	}

	//6 row
	if (newX == 1 && newY == 5)
	{
		check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
		check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
	}

	if (newX == 3 && newY == 5)
	{
		check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
		check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
	}

	if (newX == 5 && newY == 5)
	{
		check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
		check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
	}

	//7 row
	if (newX == 0 && newY == 6)
	{

		check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
		check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
	}

	if (newX == 3 && newY == 6)
	{

		check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
		check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
	}

	if (newX == 6 && newY == 6)
	{
		check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
		check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
	}

}


/*
///1)Написати перевірку, для всіх варіантів, чи 3 фішки ідуть підряд
//2)Створити клас
//3)Якщо 3 фішки ідуть підряд гравець викидає одну фішку
//4)Написати щоб гравці використовували до 9 фішок
//5)Якщо 9 фішок гравці витратили то вони починають пересувати їх
6)Коректно видаляти фішки
5)----Режим проти людини готовий----

//1)Додати функцію яка викликає головне меню
//2)Зробити кнопки(Грати проти людини на 1 компютері, Грати проти компютера, настройки, вийти робочими)
3)Додати режим компютера (?)Можливо через клас(?)
	//4)щоб компютер Ставив у випадкові місця фішки
	5)щоб компютер ставив у вигідні фипадкові місця фішки
	6)коли 3 фішки комп. підрят, щоб компютер видаляв випадкову фішку
	7)коли 2 фішки підряд бажано зробити щоб комп. ставив на 3 місце свою фішку
	8)коли в комп.
	9)комп пересуває фішки
*/