#pragma once
#ifndef computer_H
#define computer_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <ctime>


namespace mySpace {


	Color colBackGround = Color(255, 135, 0, 255);

	const int sizeMill = 7;
	const float sizeShape = 100.0f;

	bool isCourseWhite = true;
	bool isMouseClick = false;
	bool isStepDelete = false;

	char helpChar;
	short int oldY = 0, oldX = 0;
	short int computerX, computerY;


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

	void drawBuffer(sf::CircleShape s, sf::RenderWindow &win);

	void movement(std::string masMill[], bool redArray[][sizeMill], sf::Vector2i mouse);
	void movement(std::string masMill[], bool redArray[][sizeMill], Vector2i mouse, short int oldComX, short int oldComY, short int newComX, short int newComY);

	void basePossibleMoves(std::string arrStr[], bool arrBool[][sizeMill], sf::Vector2i m);
	void basePossibleMoves(std::string arrStr[], bool arrBool[][sizeMill], sf::Vector2i m, short int newX, short int  newY);

	void WhereWeGo(std::string arrStr[], bool arrBool[][sizeMill], sf::Vector2i m);
	void WhereWeGo(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m, short int newComX, short int newComY);
	
	void computerRandomMove_IF_numberMove_Above0(std::string array[])
	{

		srand(std::time(NULL));
		do
		{
			computerX = rand() % 7;
			computerY = rand() % 7;
		} while (array[computerY][computerX] != '1');
	}

	void computerRandomMove_IF_stepDelete(std::string array[])
	{

		srand(std::time(NULL));
		do
		{
			computerX = rand() % 7;
			computerY = rand() % 7;
		} while (array[computerY][computerX] != 'W');
	
	}

	void computerRandomMove_IF_peresuv(std::string array[])
	{

		srand(std::time(NULL));
		do
		{
			computerX = rand() % 7;
			computerY = rand() % 7;
		} while (array[computerY][computerX] != 'B');
	}


	char regime()
	{

		sf::RenderWindow window(sf::VideoMode(sizeMill*sizeShape + sizeShape, sizeMill*sizeShape), "Game");// размер шашки умножить на количество "полей"

		sf::CircleShape shape(sizeShape / 2.0f - 10);//в параметры функции передаэться радиус поэтому ми 100 делим на 2
												 //и делаем ненамного меньше
		shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

		Texture textBackGround;
		textBackGround.loadFromFile("images/photo/Tile04.bmp");
		Sprite backGround(textBackGround);
		backGround.setScale(0.4375, 0.4375);
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(sizeShape, sizeShape));
		//rect.
		//	shape.setFillColor(sf::Color::Black);
		sf::Vector2i mouse;

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

		Clock delay;
		float maxDelay = 0.08;

		while (window.isOpen())
		{
			mouse = sf::Mouse::getPosition(window);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return '0';
				}


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						isMouseClick = true;
					}
				}

			}


			if (isCourseWhite)
			{

				if (isMouseClick)
				{

					for (int i = 0; i < sizeMill; i++)
						for (int j = 0; j < sizeMill; j++)
							redArray[i][j] = 0;
					if (mouse.x > 0 && mouse.y > 0 && mouse.x < window.getSize().x - 100/*-100*/ && mouse.y < window.getSize().y)
					{
						//mouse / sizeMill == perevodum v massuv coordinate
					
						if (isStepDelete)
						{
							
							if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == 'B')								{
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
						else
						{
							if (pB.numberMove > 0)
							{

								if (masMill[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] == '1')
									//if tudu mozhna postavutu point
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
								}
							}
							else //peredvuganie
							{
								short int newX = int(mouse.x / sizeShape);
								short int newY = int(mouse.y / sizeShape);


								if (isCourseWhite)
								{

									if (masMill[newY][newX] == 'W')
									{
										redArray[oldY][oldX] = 0;
										oldX = newX;
										oldY = newY;
										redArray[oldY][oldX] = 1;
									}
									if (masMill[oldY][oldX] == 'W')
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

			}
			else if (!isCourseWhite)
			{

				for (int i = 0; i < sizeMill; i++)
					for (int j = 0; j < sizeMill; j++)
						redArray[i][j] = 0;

				if (isStepDelete)
				{
					delay.restart();

						computerRandomMove_IF_stepDelete(masMill);

	

					masMill[computerY][computerX] = '1';
					isCourseWhite = true;
					isStepDelete = false;
					isMouseClick = false;
					pW.amountPawn--;

					for (int i = 0; i < sizeMill; i++)
						for (int j = 0; j < sizeMill; j++)
							redArray[i][j] = 0;

					//	redArray[int(mouse.y / sizeShape)][int(mouse.x / sizeShape)] = 2;


				}
				else
				{
					if (pB.numberMove > 0)
					{

						delay.restart();
			
						computerRandomMove_IF_numberMove_Above0(masMill);




						if (masMill[computerY][computerX] == '1')//if tudu mozhna postavutu point
						{
					
							if (!isCourseWhite)
							{
								masMill[computerY][computerX] = 'B';

								redArray[oldY][oldX] = 0;
								oldY = computerY;
								oldX = computerX;

								redArray[oldY][oldX] = 1;
							
								pB.numberMove--;
								pB.amountPawn++;
								isCourseWhite = true;

								WhereWeGo(masMill, redArray, mouse, computerX, computerY);

							}
						}
					}
					else //peredvuganie
					{
						delay.restart();
						computerRandomMove_IF_peresuv(masMill);

	
						oldX = computerX;
						oldY = computerY;

						basePossibleMoves(masMill, redArray, mouse, computerX, computerY);
					}
				}
				isMouseClick = false;//для одноразового срабативания

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



	//funct
	void check(std::string array[], short int indexHelpChar1, short int indexHelpChar2,
		short int indexIBegin, short int indexIEnd, short int stepI,
		short int indexJBegin, short int indexJEnd, short int stepJ
		, bool redArr[][sizeMill]
	)
	{
	//	bool isRed = false;
		helpChar = array[indexHelpChar1][indexHelpChar2];

		int k = 0;

		for (int i = indexIBegin; i <= indexIEnd; i += stepI)
		{
			for (int j = indexJBegin; j <= indexJEnd; j += stepJ)
			{
				
				if (array[i][j] == helpChar && array[i][j] != '1')
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
			//for (int i = indexIBegin; i <= indexIEnd; i += stepI)
			//{
			//	for (int j = indexJBegin; j <= indexJEnd; j += stepJ)
			//	{
			//		if (isCourseWhite)
			//		{
			//			//		array[i][j] = 'w';
			//		}
			//		else if (!isCourseWhite)
			//		{
			//			//		array[i][j] = 'b';
			//		}
			//	}
			//}
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
		s.setPosition(7 * sizeShape + +sizeShape / 2, +sizeShape / 2);
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

		isCourseWhite = false;

	}
	void movement(std::string masMill[], bool redArray[][sizeMill], Vector2i mouse, short int oldComX, short int oldComY,short int newComX, short int newComY)
	{
		//iif '1' exit
		//checks
		if (masMill[newComY][newComX] == 'B')
		{
			redArray[oldComY][oldComX] = 0;
			oldComX = newComX;
			oldComY = newComY;
			redArray[oldComY][oldComX] = 1;
		}
		if (masMill[oldComY][oldComX] == 'B')
		{
			if (masMill[newComY][newComX] == '1')
			{
				masMill[newComY][newComX] = masMill[oldComY][oldComX];
				masMill[oldComY][oldComX] = '1';

				redArray[oldComY][oldComX] = 0;
				oldComY = newComY;
				oldComX = newComX;
				redArray[oldComY][oldComX] = 1;

				isCourseWhite = true;
			//	basePossibleMoves(masMill, redArray, mouse);
			}
		}
		///checks

		//void basePossibleMoves(std::string arrStr, bool arrBool[][sizeMill], Vector2i m);


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
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
				check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
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
	void basePossibleMoves(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m, short int newX, short int  newY)
	{
		/*
		if (!isStepDelete)
		{
		//gorisontalli up
			check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
			check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
			check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);

		//verticalli right
			check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
			check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
			check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);

		//gorisontal down
			check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
			check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
			check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);

		//verticalli left
			check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
			check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
			check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);

		//verticalli middle up
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);

		//verticalli middle right
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);

		//verticalli middle down
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);

		//verticalli middle left
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
		}
		*/


		if (newX == 0 && newY == 0)
		{
			bool whereGoComputer = rand() % 2;

			if (whereGoComputer)
			{
				computerX = 0;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);

			}
			else
			{
				computerX = 3; 
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 0)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 3;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
				break;

			case 1:
				computerX = 0;
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
				break;
			case 2:
				computerX = 6;
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
				break;
			}
		}

		if (newX == 6 && newY == 0)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 6;
				computerY = 3;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 0;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
		}

		//2 row
		if (newX == 1 && newY == 1)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 3;
				computerY = 1;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
			else
			{
				computerX = 1;
				computerY = 3;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 1)
		{
			__int8 whereGoComputer = rand() % 4;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 3;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
				break;
			case 1:
				computerX = 1;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
				break;
			case 2:
				computerX = 3;
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
				break;
			case 3:
				computerX = 5;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
				break;
			} 
		}

		if (newX == 5 && newY == 1)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 5;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
		}

		//3 row
		if (newX == 2 && newY == 2)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 2;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 2)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 2;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
				break;
			case 1:
				computerX = 3;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
				break;
			case 2:
				computerX = 4;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
				break;
			}
		}

		if (newX == 4 && newY == 2)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 4;
				computerY = 3;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 2;

				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);
			}
		}

		//4 row
		if (newX == 0 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 1;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
				break;
			case 1:
				computerX = 0;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
				break;
			case 2:
				computerX = 0;
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
				break;
			}
		}

		if (newX == 1 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 4;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 0;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
				break;
			case 1:
				computerX = 2;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
				break;
			case 2:
				computerX = 1;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
				break;
			case 3:
				computerX = 1;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
				break;
			}
		}

		if (newX == 2 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 2;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
				break;
			case 1:
				computerX = 1;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
				break;
			case 2:
				computerX = 2;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
				break;
			}
		}

		if (newX == 4 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 4;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
				break;
			case 1:
				computerX = 4;
				computerY = 2;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);
				break;
			case 2:
				computerX = 5;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
				break;
			}
		}

		if (newX == 5 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 4;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 4;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
				break;
			case 1:
				computerX = 6;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
				break;
			case 2:
				computerX = 5;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
				break;
			case 3:
				computerX = 5;
				computerY = 1;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
				break;
			}

		}

		if (newX == 6 && newY == 3)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 5;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
				break;
			case 1:
				computerX = 6;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
				break;
			case 2:
				computerX = 6;
				computerY = 0;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
				break;
			}

			

		}

		//5 row

		if (newX == 2 && newY == 4)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 2;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 4)
		{
			__int8 whereGoComputer = rand() % 3;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 3;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
				break;
			case 1:
				computerX = 2;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);
				break;
			case 2:
				computerX = 4;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);
				break;
			}
		}

		if (newX == 4 && newY == 4)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 3;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
			else
			{
				computerX = 4;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
		}

		//6 row
		if (newX == 1 && newY == 5)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 1;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 5)
		{
			__int8 whereGoComputer = rand() % 4;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 3;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
				break;
			case 1:
				computerX = 1;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
				break;
			case 2:
				computerX = 3;
				computerY = 4;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);
				break;
			case 3:
				computerX = 5;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
				break;
			}
		}

		if (newX == 5 && newY == 5)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 3;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
			else
			{
				computerX = 5;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
		}

		//7 row
		if (newX == 0 && newY == 6)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 0;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
			}
			else
			{
				computerX = 3;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
		}

		if (newX == 3 && newY == 6)
		{
			__int8 whereGoComputer = rand() % 4;
			switch (whereGoComputer)
			{
			case 0:
				computerX = 0;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
				break;
			case 1:
				computerX = 3;
				computerY = 5;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
				break;
			case 2:
				computerX = 6;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
				break;
			}
		}

		if (newX == 6 && newY == 6)
		{
			bool whereGoComputer = rand() % 2;
			if (whereGoComputer)
			{
				computerX = 3;
				computerY = 6;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);
			}
			else
			{
				computerX = 6;
				computerY = 3;
				movement(arrStr, arrBool, m, newX, newY, computerX, computerY);
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);
			}
		}

		/*
		if (!isStepDelete)
		{
		//gorisontalli up
		//	check(arrStr, 0, 0, 0, 0, 1, 0, 6, 3, arrBool);
		//	check(arrStr, 1, 1, 1, 1, 1, 1, 5, 2, arrBool);
		//	check(arrStr, 2, 2, 2, 2, 1, 2, 4, 1, arrBool);

		//verticalli right
			check(arrStr, 0, 6, 0, 6, 3, 6, 6, 1, arrBool);
			check(arrStr, 1, 5, 1, 5, 2, 5, 5, 1, arrBool);
		//	check(arrStr, 2, 4, 2, 4, 1, 4, 4, 1, arrBool);

		//gorisontal down
			check(arrStr, 6, 0, 6, 6, 1, 0, 6, 3, arrBool);
			check(arrStr, 5, 1, 5, 5, 1, 1, 5, 2, arrBool);
			check(arrStr, 4, 2, 4, 4, 1, 2, 4, 1, arrBool);

		//verticalli left
			check(arrStr, 0, 0, 0, 6, 3, 0, 0, 1, arrBool);
			check(arrStr, 1, 1, 1, 5, 2, 1, 1, 1, arrBool);
		//	check(arrStr, 2, 2, 2, 4, 1, 2, 2, 1, arrBool);

		//verticalli middle up
		//		check(arrStr, 0, 3, 0, 2, 1, 3, 3, 1, arrBool);

		//verticalli middle right
				check(arrStr, 3, 4, 3, 3, 1, 4, 6, 1, arrBool);

		//verticalli middle down
				check(arrStr, 4, 3, 4, 6, 1, 3, 3, 1, arrBool);

		//verticalli middle left
				check(arrStr, 3, 0, 3, 3, 1, 0, 2, 1, arrBool);
		}
		*/
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
	void WhereWeGo(std::string arrStr[], bool arrBool[][sizeMill], Vector2i m, short int newComX, short int newComY)
	{
		short int newX = newComX, newY = newComY;

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


}

#endif
