/*
=================================================================================================================================================================================
Name        : game.cpp
Author      : Hassan Mustafa
Version     :
Copyright   : (c) Reserved
Description : Basic 2D game of Dodge 'Em...

Project by: Ahmad Arif
Roll No.: i18-1661
Section: CS-A
=================================================================================================================================================================================
*/

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include<iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<ctime> 
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;

//=================================================================================================================================================================================

void GameDisplay();
void SetCanvasSize();
void instruction();
void start();
void scoreDisplay(int score);
void drawingArena();
void userCar();
void opponentCar();
void foodDisplay();
void NonPrintableKeys();
void PrintableKeys();
void Timer(int m);
void MousePressedAndMoved();
void MouseMoved();
void MouseClicked();
string ReadData();
bool WriteData();
void opponentCarMovement();
void carCollision();
void userSpeed();
void opponent2Car();
void opponent2CarMovement();
void funcExit();
void levelClearing();

//=================================================================================================================================================================================

//global for movement of opponent car
float x = 290; 
float y = 40;
float x2 = 290;
float y2 = 750;

//=================================================================================================================================================================================

// car drawing variables
float width; 
float height;
float* color; 
float radius;

//=================================================================================================================================================================================

//global for movement of user car
float ux = 490; 
float uy = 40; 


//=================================================================================================================================================================================

float speed = 5; //for increasing speed of car if [space] is pressed
float opponentSpeed;

//=================================================================================================================================================================================

// number of roads
int numRoads = 4; // modify to ask it from user
int lives = 3, score = 0, level = 1;
int points[900][900] = {0};

//============================================================================

// variables declared for opponent to follow the user
int user_xbox_edge_max = 750, user_xbox_edge_min = 40, user_ybox_edge_max = 750, user_ybox_edge_min = 30, user = 1;
int opponent_xbox_edge_max = 750, opponent_xbox_edge_min = 40, opponent_ybox_edge_max = 750, opponent_ybox_edge_min = 30, opponent = 1;

int opponent2_xbox_edge_max = 750, opponent2_xbox_edge_min = 40, opponent2_ybox_edge_max = 750, opponent2_ybox_edge_min = 30, opponent2 = 1;
	
//=================================================================================================================================================================================

/* 
	Function sets canvas size (drawing area) in pixels... that is what dimensions (x and y) your game will have.
	Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
*/
void SetCanvasSize(int width, int height)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//=================================================================================================================================================================================

/*
	This function is being used to store the highscore of the players
*/
bool WriteData(string sData)
{
	ofstream out;
	out.open("Highscores.txt",ios::app);
	if(out)
	{		
		out << sData;	
		out.close();
		return true;
	}
	return false;
}

//=================================================================================================================================================================================

/*
	This function is being used to read the highscore of the players
*/
string ReadData()
{
	ifstream in("Highscores.txt");
	if (in)
	{
		string sData = " ";
		char arr[50];
		in.getline(arr,49);
		do{
			sData+= (string)arr;
			in.getline(arr,49);
		}while(in);
		return " ";
	}
}

//=================================================================================================================================================================================

/*
	This function checks if the car has collided or not
*/
void carCollision()
{
	if (lives != 0)
	{
		if ((((x <= ux + 10) && (x >= ux - 10)) && ((y <= uy + 10) && (y >= uy - 10))) || ((level == 3 || level == 4) && ((x2 <= ux + 10) && (x2 >= ux - 10)) && ((y2 <= uy + 10) && (y2 >= uy - 10))))
		{
			lives--;
			if (lives == 0)
			{
				speed = 0;
				opponentSpeed = 0;
			}
			ux = 490; 
			uy = 40; 
			x = 290; 
			y = 40;
			x2 = 290;
			y2 = 750;
			sleep(2);
		} 
	}
}

//=================================================================================================================================================================================

/*
	This is the instruction display of the game
*/
void instruction()
{
	DrawString(100, 750, "INSTRUCTIONS:", colors[MISTY_ROSE]);
	DrawString(100, 650, "1. MOVE THE CAR BETWEEN THE THE BOXES THROuGH GAPS BY USING THE ARROW KEYS.", colors[MISTY_ROSE]);
	DrawString(100, 550, "2. YOU CANNOT GO IN THE REVERSE DIRECTION.", colors[MISTY_ROSE]);
	DrawString(100, 450, "3. YOU CAN SCORE BY EATING AS MUCH FOOD AS POSSIBLE.", colors[MISTY_ROSE]);
	DrawString(100, 350, "4. THERE AARE FOUR LEVELS TO THIS GAME, EACH LEVEL HAVING ITS OWN DIFFICULTY.", colors[MISTY_ROSE]);
	DrawString(100, 250, "5. COLLECT ALL THE FOOD TO CLEAR A LEVEL.", colors[MISTY_ROSE]);
	DrawString(100, 150, "6. SPPED OF THE OPPONENT WILL INCREASE AFTER EVERY LEVEL.", colors[MISTY_ROSE]);
	DrawString(100, 50, "7. THERE ARE TWO OPPONENTS IN LEVEL 3 AND 4.", colors[MISTY_ROSE]);
	sleep(10);
	glutDisplayFunc(start);
	glutSwapBuffers();
}

//=================================================================================================================================================================================

/*
	This is the start screen of the game
*/
void start()
{
	DrawString(350, 850, "Dodge 'em", colors[MISTY_ROSE]);
	DrawString(100, 550, "START (1)", colors[MISTY_ROSE]);
	DrawString(100, 500, "INSTRUCTIONS (2)", colors[MISTY_ROSE]);
	DrawString(100, 450, "EXIT (3)", colors[MISTY_ROSE]);
	glutSwapBuffers();
}

//=================================================================================================================================================================================

void funcExit()
{
	exit (1);
}

//=================================================================================================================================================================================

void scoreDisplay(int score)
{
	string printScore;
	printScore = to_string(score);
	//Display current score
	DrawString(50, 850, "Current Score: ", colors[MISTY_ROSE]);
	DrawString(200, 850, printScore, colors[MISTY_ROSE]);
}

//=================================================================================================================================================================================

void livesDisplay()
{
	string printLives;
	printLives = to_string(lives);
	// Displaying lives of the  user
	DrawString(270, 850, "Lives: ", colors[MISTY_ROSE]);
	DrawString(340, 850, printLives, colors[MISTY_ROSE]);
}

//=================================================================================================================================================================================

/*
	This function is called everytime the arena is to be displayed.
*/
void drawingArena()
{
for(int repeat = 1, gap_turn = 80, sx = 20, sy = 10, changeWidth = 800; repeat <= numRoads; repeat++)
	{
		int swidth = changeWidth/2 - gap_turn/2; // half width
		int sheight = 10;
		float *scolor = colors[BROWN];
		DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
		DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
		DrawRectangle(sx + swidth * 2 + gap_turn, sy + sheight, sheight * 2, swidth, scolor); // right down
		DrawRectangle(sx + swidth * 2+ gap_turn, sy + sheight + swidth+ gap_turn, sheight * 2, swidth, scolor); // right up
		DrawRectangle(sx + swidth + gap_turn, sy + changeWidth + 10, swidth, sheight, scolor); // top left
		DrawRectangle(sx, sy + changeWidth + 10, swidth, sheight, scolor); // top right
		DrawRectangle(sx - sheight * 2, sy + sheight +swidth + gap_turn, sheight * 2, swidth, scolor); // left up	
		DrawRectangle(sx - sheight * 2, sy + sheight, sheight * 2, swidth, scolor); // left down
		
		sx += 100;
		sy += 100;
		changeWidth -= 200;	
	}
	DrawSquare( 400 , 400 , 40,colors[BROWN]);
}

//=================================================================================================================================================================================

/*
	This function is called to display user car
*/
void userCar()
{
	// Drawing user car
	width = 15; 
	height = 10;
	color = colors[BROWN]; 
	radius = 5.0;
	DrawRoundRect(ux, uy, width, height, color, radius); // bottom left tyre
	DrawRoundRect(ux + width * 3, uy, width, height, color, radius); // bottom right tyre
	DrawRoundRect(ux + width * 3, uy + height * 4, width, height, color, radius); // top right tyre
	DrawRoundRect(ux, uy + height * 4, width, height, color, radius); // top left tyre
	DrawRoundRect(ux, uy + height * 2, width, height, color, radius / 2); // body left rect
	DrawRoundRect(ux + width, uy + height, width * 2, height * 3, color, radius / 2); // body center rect
	DrawRoundRect(ux + width * 3, uy + height * 2, width, height, color, radius / 2); // body right rect
	
//=================================================================================================================================================================================

	/*
		Automatic movement of user car
	*/
	for (int check_1 = 30, check_2 = 750, check_3 = 40; check_1 <= 330; check_1 += 100, check_2 -= 100, check_3 += 100)
	{	
		if(ux >= check_1 && ux <= check_2 && uy == check_3)
		{
			ux += speed;
		}
	}
	for (int check_1 = 40, check_2 = 750, check_3 = 750; check_1 <= 340; check_1 += 100, check_2 -= 100, check_3 -= 100)
	{
			if (uy >= check_1 && ux == check_2 && uy <= check_3)
		{
			uy += speed;
		}
	}
	for (int check_1 = 750, check_2 = 30, check_3 = 750; check_2 <= 330; check_1 -= 100, check_2 += 100, check_3 -= 100)
	{
		if (uy == check_1 && ux >= check_2 && ux <= check_3)
		{
			ux -= speed;
		}
	}
	for (int check_1 = 30, check_2 = 40, check_3 = 750; check_1 <= 330; check_1 += 100, check_2 += 100, check_3 -= 100)
	{
		if(ux == check_1 && uy >= check_2 && uy <= check_3)
		{
			uy -= speed;
		}
	}
}

//=================================================================================================================================================================================

/*
	This function is called to display opponent car
*/
void opponentCar()
{
	// Drawing opponent car
	width = 15; 
	height = 10;
	color = colors[BLUE]; 
	radius = 5.0;
	DrawRoundRect(x, y, width, height, color, radius); // bottom left tyre
	DrawRoundRect(x + width * 3, y, width, height, color, radius); // bottom right tyre
	DrawRoundRect(x + width * 3, y + height * 4, width, height, color, radius); // top right tyre
	DrawRoundRect(x, y + height * 4, width, height, color, radius); // top left tyre
	DrawRoundRect(x, y + height * 2, width, height, color, radius / 2); // body left rect
	DrawRoundRect(x + width, y + height, width * 2, height * 3, color, radius / 2); // body center rect
	DrawRoundRect(x + width * 3, y + height * 2, width, height, color, radius / 2); // body right rect

	opponentCarMovement();
}	

//=================================================================================================================================================================================

/*
	This function is called everytime for the movement of opponent
*/
void opponentCarMovement()
{
	/*
		Movement of opponent
	*/
	if (opponent < user)
	{
		if((y >= 370 && y <= 420) && (x == 750 ||x == 650 || x == 550))
		{
			x -= 100;
			opponent_xbox_edge_max -= 100;
			opponent_xbox_edge_min += 100;
			opponent_ybox_edge_max -= 100;
			opponent_ybox_edge_min += 100;
			y -= 100;
			opponent++;
		}
		else if ((y >= 370 && y <= 420) && (x == 30 || x == 130 || x == 230))
		{
			x += 100;
			opponent_xbox_edge_max -= 100;
			opponent_xbox_edge_min += 100;
			opponent_ybox_edge_max -= 100;
			opponent_ybox_edge_min += 100;
			y += 100;
			opponent++;
		}
		else if ((x >= 350 && x <= 400) && (y == 40 || y == 140 || y == 240))
		{
			y += 100;
			opponent_xbox_edge_max -= 100;
			opponent_xbox_edge_min += 100;
			opponent_ybox_edge_max -= 100;
			opponent_ybox_edge_min += 100;
			x -= 100;
			opponent++;
		}
		else if((x >= 350 && x <=400) && (y == 750 || y == 650 || y == 550))
		{
			y -= 100;
			opponent_xbox_edge_max -= 100;
			opponent_xbox_edge_min += 100;
			opponent_ybox_edge_max -= 100;
			opponent_ybox_edge_min += 100;
			x += 100;
			opponent++;
		}
	}
	else if (opponent > user)
	{
		if ((y >= 370 && y <= 420) && (x == 130 ||x == 230 || x == 330))
		{
			x -= 100;
			opponent_xbox_edge_max += 100;
			opponent_xbox_edge_min -= 100;
			opponent_ybox_edge_max += 100;
			opponent_ybox_edge_min -= 100;
			y += 100;
			opponent--;
		}
		else if ((y >= 370 && y <= 420) && (x == 650 || x == 550 || x == 450))
		{
			x += 100;
			opponent_xbox_edge_max += 100;
			opponent_xbox_edge_min -= 100;
			opponent_ybox_edge_max += 100;
			opponent_ybox_edge_min -= 100;
			y -= 100;
			opponent--;
		}
		else if ((x >= 370 && x <= 420) && (y == 650 || y == 550 || y == 450))
		{
			y += 100;
			opponent_xbox_edge_max += 100;
			opponent_xbox_edge_min -= 100;
			opponent_ybox_edge_max += 100;
			opponent_ybox_edge_min -= 100;
			x += 100;
			opponent--;
		}
		else if ((x >= 370 && x <= 420) && (y == 140 || y == 240 || y == 340))
		{
			y -= 100;
			opponent_xbox_edge_max += 100;
			opponent_xbox_edge_min -= 100;
			opponent_ybox_edge_max += 100;
			opponent_ybox_edge_min -= 100;
			x -= 100;
			opponent--;
		}
	}

//=================================================================================================================================================================================

	if ((x >= 30 && x <= 750 && y == 40) || (x >= 130 && x <= 650 && y == 140) || (x >= 230 && x <= 550 && y == 240) || (x >= 330 && x <= 450 && y == 340))
	{
		x -= opponentSpeed;
	}
	if ((y >= 40 && x == 750 && y <= 750) || (y >= 140 && x == 650 && y <= 650) || (y >= 240 && x == 550 && y <= 550) || (y >= 340 && x == 450 && y <= 450))
	{
		y -= opponentSpeed;
	}
	if ((y == 750 && x >= 30 && x <= 750) || (y == 650 && x >= 130 && x <= 650) || (y == 550 && x >= 230 && x <= 550) || (y == 450 && x >= 330 && x <= 450))
	{
		x += opponentSpeed;
	}
	if((x == 30 && y >= 40 && y <= 750) || (x == 130 && y >= 140 && y <= 650) || (x == 230 && y >= 240 && y <= 550) || (x == 330 && y >= 340 && y <= 450))
	{
		y += opponentSpeed;
	}
}

//=================================================================================================================================================================================

/*
	This function is called to display opponent car
*/
void opponent2Car()
{
	// Drawing opponent car
	width = 15; 
	height = 10;
	color = colors[BLUE]; 
	radius = 5.0;
	DrawRoundRect(x2, y2, width, height, color, radius); // bottom left tyre
	DrawRoundRect(x2 + width * 3, y2, width, height, color, radius); // bottom right tyre
	DrawRoundRect(x2 + width * 3, y2 + height * 4, width, height, color, radius); // top right tyre
	DrawRoundRect(x2, y2 + height * 4, width, height, color, radius); // top left tyre
	DrawRoundRect(x2, y2 + height * 2, width, height, color, radius / 2); // body left rect
	DrawRoundRect(x2 + width, y2 + height, width * 2, height * 3, color, radius / 2); // body center rect
	DrawRoundRect(x2 + width * 3, y2 + height * 2, width, height, color, radius / 2); // body right rect

	opponent2CarMovement();
}	

//=================================================================================================================================================================================

/*
	This function is called everytime for the movement of opponent
*/
void opponent2CarMovement()
{
	/*
		Movement of opponent
	*/
	if (opponent2 < user)
	{
		if((y2 >= 370 && y2 <= 420) && (x2 == 750 ||x2 == 650 || x2 == 550))
		{
			x2 -= 100;
			opponent2_xbox_edge_max -= 100;
			opponent2_xbox_edge_min += 100;
			opponent2_ybox_edge_max -= 100;
			opponent2_ybox_edge_min += 100;
			y2 -= 100;
			opponent2++;
		}
		else if ((y2 >= 370 && y2 <= 420) && (x2 == 30 || x2 == 130 || x2 == 230))
		{
			x2 += 100;
			opponent2_xbox_edge_max -= 100;
			opponent2_xbox_edge_min += 100;
			opponent2_ybox_edge_max -= 100;
			opponent2_ybox_edge_min += 100;
			y2 += 100;
			opponent2++;
		}
		else if ((x2 >= 350 && x2 <= 400) && (y2 == 40 || y2 == 140 || y2 == 240))
		{
			y2 += 100;
			opponent2_xbox_edge_max -= 100;
			opponent2_xbox_edge_min += 100;
			opponent2_ybox_edge_max -= 100;
			opponent2_ybox_edge_min += 100;
			x2 -= 100;
			opponent2++;
		}
		else if((x2 >= 350 && x2 <=400) && (y2 == 750 || y2 == 650 || y2 == 550))
		{
			y2 -= 100;
			opponent2_xbox_edge_max -= 100;
			opponent2_xbox_edge_min += 100;
			opponent2_ybox_edge_max -= 100;
			opponent2_ybox_edge_min += 100;
			x2 += 100;
			opponent2++;
		}
	}
	else if (opponent2 > user)
	{
		if ((y2 >= 370 && y2 <= 420) && (x2 == 130 ||x2 == 230 || x2 == 330))
		{
			x2 -= 100;
			opponent2_xbox_edge_max += 100;
			opponent2_xbox_edge_min -= 100;
			opponent2_ybox_edge_max += 100;
			opponent2_ybox_edge_min -= 100;
			y2 += 100;
			opponent2--;
		}
		else if ((y2 >= 370 && y2 <= 420) && (x2 == 650 || x2 == 550 || x2 == 450))
		{
			x2 += 100;
			opponent2_xbox_edge_max += 100;
			opponent2_xbox_edge_min -= 100;
			opponent2_ybox_edge_max += 100;
			opponent2_ybox_edge_min -= 100;
			y2 -= 100;
			opponent2--;
		}
		else if ((x2 >= 370 && x2 <= 420) && (y2 == 650 || y2 == 550 || y2 == 450))
		{
			y2 += 100;
			opponent2_xbox_edge_max += 100;
			opponent2_xbox_edge_min -= 100;
			opponent2_ybox_edge_max += 100;
			opponent2_ybox_edge_min -= 100;
			x2 += 100;
			opponent2--;
		}
		else if ((x2 >= 370 && x2 <= 420) && (y2 == 140 || y2 == 240 || y2 == 340))
		{
			y2 -= 100;
			opponent2_xbox_edge_max += 100;
			opponent2_xbox_edge_min -= 100;
			opponent2_ybox_edge_max += 100;
			opponent2_ybox_edge_min -= 100;
			x2 -= 100;
			opponent2--;
		}
	}

//=================================================================================================================================================================================

	if ((x2 >= 30 && x2 <= 750 && y2 == 40) || (x2 >= 130 && x2 <= 650 && y2 == 140) || (x2 >= 230 && x2 <= 550 && y2 == 240) || (x2 >= 330 && x2 <= 450 && y2 == 340))
	{
		x2 -= opponentSpeed;
	}
	if ((y2 >= 40 && x2 == 750 && y2 <= 750) || (y2 >= 140 && x2 == 650 && y2 <= 650) || (y2 >= 240 && x2 == 550 && y2 <= 550) || (y2 >= 340 && x2 == 450 && y2 <= 450))
	{
		y2 -= opponentSpeed;
	}
	if ((y2 == 750 && x2 >= 30 && x2 <= 750) || (y2 == 650 && x2 >= 130 && x2 <= 650) || (y2 == 550 && x2 >= 230 && x2 <= 550) || (y2 == 450 && x2 >= 330 && x2 <= 450))
	{
		x2 += opponentSpeed;
	}
	if((x2 == 30 && y2 >= 40 && y2 <= 750) || (x2 == 130 && y2 >= 140 && y2 <= 650) || (x2 == 230 && y2 >= 240 && y2 <= 550) || (x2 == 330 && y2 >= 340 && y2 <= 450))
	{
		y2 += opponentSpeed;
	}
}

//=================================================================================================================================================================================

/*	
	This function is called to draw food
*/
void foodDisplay()
{
	for (int i = 60; i <= 760; i += 100)
	{
		for (int j = 60; j <= 760; j += 100)
		{
			if (i >= 400 && i <= 450)
			{
				i += 10;
			}
			if (points[i][j] == 0 || points[i][j] == 1)
			{
				if (((i <= ux + 30) && (i >= ux - 10)) && ((j <= uy + 30) && (j >= uy - 10)))
				{
					points[i][j]++;
				}
				if (points[i][j] == 0)
				{
					DrawCircle( i, j, 10, colors[YELLOW]);
				}
				if (points[i][j] == 1)
				{
					score++;
				}
			}
		}
	}
}

//=================================================================================================================================================================================

void levelClearing()
{
	if (lives == 0)
	{
		DrawString(330, 450, "G A M E  O V E R !", colors[WHITE]);
		sleep(3);
		
	}
	if (score == 64 || score == 128 || score == 192)
	{
		DrawString(330, 450, "Congratulations! Proceed to next level.", colors[WHITE]);	
		level++;
		for (int i = 60; i <= 760; i += 100)
		{
			for (int j = 60; j <= 760; j += 100)
			{
				points[i][j] = 0;
			}
		}
		sleep(3);
		/*
		ux = 490; 
		uy = 40; 
		x = 290; 
		y = 40;
		x2 = 290;
		y2 = 750;
		*/
	}
	if (level == 5 || score == 256)
	{
		DrawString(330, 450, "Congratulations! You have won the game.", colors[WHITE]);	
		sleep(3);
		exit (1);
	}
	if (level == 1)
	{
		opponentSpeed = 1;
	}
	if (level == 2)
	{
		opponentSpeed = 2;
	}
	if (level == 3)
	{
		opponentSpeed = 5;
		opponent2Car();
	}
	if (level == 4)
	{
		opponentSpeed = 10;
		opponent2Car();
	}
}

//=================================================================================================================================================================================

/*
	Main Canvas drawing function.
*/
//Board *b;
void GameDisplay()/**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors


	// calling some functions from util.cpp file to help students

	levelClearing();
	scoreDisplay(score);
	carCollision();
	livesDisplay();
	drawingArena();
	foodDisplay();
	opponentCar();
	userCar();	

	Timer(1000);

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

//=================================================================================================================================================================================

/*
	This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arrow)
	is pressed from the keyboard
	You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
	This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
	program coordinates of mouse pointer when key was pressed.
*/
void NonPrintableKeys(int key, int x, int y) 
{
	//Car of user
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) 
	{
		// what to do when left key is pressed...
		if (ux >= 40 && (uy >= 370 && uy <= 420))
		{
			if(ux == 750 || ux == 650 || ux == 550)
			{
				ux -= 100;
				user_xbox_edge_max -= 100;
				user_xbox_edge_min += 100;
				user_ybox_edge_max -= 100;
				user_ybox_edge_min += 100;
				user++;
			}
			if (ux == 130 || ux == 230 || ux == 330)
			{
				ux -= 100;
				user_xbox_edge_max += 100;
				user_xbox_edge_min -= 100;
				user_ybox_edge_max += 100;
				user_ybox_edge_min -= 100;
				user--;
			}
			else if (ux == 40 || ux == 140 || ux == 240)
			{
				ux = 750;
			}
		}
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{
		if (ux <= 750 && (uy >= 370 && uy <= 420))
	 	{
			if (ux == 30 || ux == 130 || ux == 230)
			{
				ux += 100;
				user_xbox_edge_max -= 100;
				user_xbox_edge_min += 100;
				user_ybox_edge_max -= 100;
				user_ybox_edge_min += 100;
				user++;
			}
			if (ux==650 || ux==550 || ux==450)
			{
				ux += 100;
				user_xbox_edge_max += 100;
				user_xbox_edge_min -= 100;
				user_ybox_edge_max += 100;
				user_ybox_edge_min -= 100;
				user--;	
			}
			else if (ux == 750)
			{
				ux = 30;
			}
		}	
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
		if (uy <= 750 && (ux >= 350 && ux <= 400))
		{
			if (uy == 40 || uy==140 || uy==240)
			{
				uy += 100;
				user_xbox_edge_max -= 100;
				user_xbox_edge_min += 100;
				user_ybox_edge_max -= 100;
				user_ybox_edge_min += 100;
				user++;	
			}
			if (uy == 450 || uy==550 || uy==650)
			{
				uy += 100;
				user_xbox_edge_max += 100;
				user_xbox_edge_min -= 100;
				user_ybox_edge_max += 100;
				user_ybox_edge_min -= 100;
				user--;
			}
			else if (uy == 750)
			{
				uy = 40;
			}
		}
	}
	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		if (uy >= 40 && (ux >= 350 && ux <= 400))
		{
			if(uy == 550 || uy == 650 || uy == 750)
			{
				uy -= 100;
				user_xbox_edge_max -= 100;
				user_xbox_edge_min += 100;
				user_ybox_edge_max += 100;
				user_ybox_edge_min -= 100;
				user++;	
			}
			if (uy == 140 || uy == 240 || uy == 340)
			{
				uy -= 100;
				user_xbox_edge_max -= 100;
				user_xbox_edge_min -= 100;
				user_ybox_edge_max -= 100;
				user_ybox_edge_min += 100;
				user++;	
			}
			else if (uy == 30)
			{
				uy = 750;
			}
		}	
	}
}

//=================================================================================================================================================================================

/*
	This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
	is pressed from the keyboard
	This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
	program coordinates of mouse pointer when key was pressed.
*/
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27/* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'b' || key == 'B')
	{
		//do something if b is pressed
		cout << "b pressed" << endl;
	}
	if (key == 'p' || key == 'P')
	{
		DrawString(330, 450, "P A U S E D", colors[WHITE]);	
		glutSwapBuffers();
		sleep(1);
	}
	/*
	speed = 5;
	while (key == 32)
	{
		speed = 10;
	}
	*/
	if (key == 49)
	{
		glutDisplayFunc(GameDisplay);
	}
	else if (key == 50)
	{
		instruction();
	}
	else if (key == 51)
	{
		funcExit();
	}

	glutPostRedisplay();
}

//=================================================================================================================================================================================

/*   
	This function is called after every 1000.0/FPS milliseconds
	(FPS is defined on in the beginning).
	You can use this function to animate objects and control the
	speed of different moving objects by varying the constant FPS.
*/
void Timer(int m) 
{
	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
	glutPostRedisplay();
		
}

//=================================================================================================================================================================================

/*
	This function is called (automatically) whenever your mouse moves witin inside the game window
	You will have to add the necessary code here for finding the direction of shooting
	This function has two arguments: x & y that tells the coordinate of current position of move mouse
*/
void MousePressedAndMoved(int x, int y) 
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

//=================================================================================================================================================================================

void MouseMoved(int x, int y) 	
{
	glutPostRedisplay();
}

//=================================================================================================================================================================================

/*
	This function is called (automatically) whenever your mouse button is clicked witin inside the game window
	You will have to add the necessary code here for shooting, etc.
	This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
	x & y that tells the coordinate of current position of move mouse
*/
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && (x >= 80 && x <= 170) && (y >= 500 && y <= 570)) // dealing only with left button
	{
		//cout << GLUT_DOWN << " " << GLUT_UP << endl;
		//glutDisplayFunc(GameDisplay);
	} 
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		//write here.
	}
	glutPostRedisplay();
}

//=================================================================================================================================================================================

/*
	our gateway main function
*/
int main(int argc, char *argv[])
{
		srand(time(NULL)); // seed the random numbers generator by current time (see the documentation of srand for further help)...
		//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	
//=================================================================================================================================================================================
	
	int width = 850, height = 900; // i have set my window size to be 800 x 600, New window size 850 x 900
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge 'em"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

//=================================================================================================================================================================================
	
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

//=================================================================================================================================================================================	
			
	glutDisplayFunc(start);
	//glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characte
	glutTimerFunc(1000.0, Timer, 0); // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...

//=================================================================================================================================================================================

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

//=================================================================================================================================================================================

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
}
#endif /*Dodge 'em_CPP_ */

//=================================================================================================================================================================================

/*

	"Utilities for drawing"
	
	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString(50, 850, "Current Score: 0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50, 670, 10, colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
*/