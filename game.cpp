//============================================================================
// Name        : game.cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


// seed the random numbers generator by current time (see the documentation of srand for further help)...


 
int buildings[20][20] = {
		{0},
};
int score, individual_score[10] = {0};
int timeSeconds, timeMinutes, speed = 0;
bool isPassenger = false;
string name = "", names[10];

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
/*
 *This function will check for buildings, obstacles, passengers
 *for the car. This is used for collision detection.
*/
void buildingCheckFunc(int x_axis, int y_axis, bool check[]){
	 if((buildings[y_axis][x_axis-1] >= 1) && (buildings[y_axis][x_axis-1] <= 5)){
		 check[0] = false;
	 }
	 if((buildings[y_axis][x_axis+1] >= 1) && (buildings[y_axis][x_axis+1] <= 5)){
		 check[1] = false;
	 }
	 if((buildings[y_axis+1][x_axis] >= 1) && (buildings[y_axis+1][x_axis] <= 5)){
		 check[2] = false;
	 }
	 if((buildings[y_axis-1][x_axis] >= 1) && (buildings[y_axis-1][x_axis] <= 5)){
		 check[3] = false;
	 }
}
/*
 *This function is made for other cars for their purpose
 *of checking buildings, obstacles, passengers and destination
*/
void RandomCarCheckingFunc(int x_axis, int y_axis, bool check[]){
	if((buildings[y_axis][x_axis-1] >= 1) && (buildings[y_axis][x_axis-1] <= 6)){
		 check[0] = false;
	 }
	 if((buildings[y_axis][x_axis+1] >= 1) && (buildings[y_axis][x_axis+1] <= 6)){
		 check[1] = false;
	 }
	 if((buildings[y_axis+1][x_axis] >= 1) && (buildings[y_axis+1][x_axis] <= 6)){
		 check[2] = false;
	 }
	 if((buildings[y_axis-1][x_axis] >= 1) && (buildings[y_axis-1][x_axis] <= 6)){
		 check[3] = false;
	 }
}
/*
 *This function is called everytime from gamedisplay() and will
 *Buildings, obstacles, cars, passengers and also destination with
 *respect to the global array buildings[]
*/
void DrawMap(){
	int i, j;
	for(i = 0; i < 20; i++){
		for(j = 0; j < 20; j++){
			if (buildings[i][j] == 1){
				DrawSquare(j * 40, i * 40, 41, colors[BLACK]);
			} else if (buildings[i][j] == 2){
				DrawCircle((j * 40) + 14, (i * 40) + 20, 8, colors[GREEN]);
				DrawCircle((j * 40) + 19, (i * 40) + 31, 8, colors[GREEN]);
				DrawCircle((j * 40) + 24, (i * 40) + 20, 8, colors[GREEN]);
				DrawRectangle((j * 40) + 14, (i * 40), 10, 20, colors[BROWN]);
			} else if(buildings[i][j] == 3){
				DrawSquare((j * 40) + 14, (i * 40) + 14, 14, colors[SADDLE_BROWN]);
				DrawSquare((j * 40) + 9, (i * 40) + 9, 14, colors[SANDY_BROWN]);
				DrawLine((j * 40) + 9, (i * 40) + 21, (j * 40) + 14, (i * 40) + 26, 2, colors[BLACK]);
				DrawLine((j * 40) + 21, (i * 40) + 9, (j * 40) + 26, (i * 40) + 14, 2, colors[BLACK]);
				DrawLine((j * 40) + 21, (i * 40) + 21, (j * 40) + 26, (i * 40) + 26, 2, colors[BLACK]);
			} else if(buildings[i][j] == 4){
				DrawLine((j * 40) + 10, (i * 40), (j * 40) + 20, (i * 40) + 15, 4, colors[BLACK]);
				DrawLine((j * 40) + 30, (i * 40), (j * 40) + 20, (i * 40) + 15, 4, colors[BLACK]);
				DrawLine((j * 40) + 10, (i * 40) + 15, (j * 40) + 20, (i * 40) + 30, 4, colors[BLACK]);
				DrawLine((j * 40) + 30, (i * 40) + 15, (j * 40) + 20, (i * 40) + 30, 4, colors[BLACK]);
				DrawLine((j * 40) + 20, (i * 40) + 15, (j * 40) + 20, (i * 40) + 30, 6, colors[BLACK]);
				DrawCircle((j * 40) + 20, (i * 40) + 35, 5, colors[BLACK]);
			} else if(buildings[i][j] == 6){
				DrawCircle((j * 40) + 20, (i * 40) + 20, 20, colors[GREEN]);
			} else if(buildings[i][j] == 5){
				DrawRoundRect((j * 40)+10, (i * 40)+2, 20, 36, colors[BLACK], 5);
				DrawRoundRect((j * 40)+12, (i * 40)+4, 16, 32, colors[BLUE], 5);
				DrawRoundRect((j * 40)+14, (i * 40)+8, 12, 24, colors[BLACK], 5);
				DrawRoundRect((j * 40)+16, (i * 40)+8, 8, 18, colors[BLUE], 2);
				DrawLine	 ((j * 40)+17, (i * 40)+10, (j*40)+23, (i * 40)+10, 3, colors[BLACK]);
				DrawCircle	 ((j * 40)+14, (i * 40)+34, 1, colors[BLACK]);
				DrawCircle	 ((j * 40)+26, (i * 40)+34, 1, colors[BLACK]);
				DrawLine	 ((j * 40)+14, (i * 40)+8, (j*40)+16, (i * 40)+6, 3, colors[RED]);
				DrawLine 	 ((j * 40)+26, (i * 40)+8, (j*40)+24, (i * 40)+6, 3, colors[RED]);
			}
		}
	}
	/*DrawLine(0, 39, 800, 39, 1,   colors[LIGHT_GRAY]);
	DrawLine(0, 79, 800, 79, 1,   colors[LIGHT_GRAY]);
	DrawLine(0, 119, 800, 119, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 159, 800, 159, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 199, 800, 199, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 239, 800, 239, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 279, 800, 279, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 319, 800, 319, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 359, 800, 359, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 399, 800, 399, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 439, 800, 439, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 479, 800, 479, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 519, 800, 519, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 559, 800, 559, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 599, 800, 599, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 639, 800, 639, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 679, 800, 679, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 719, 800, 719, 1, colors[LIGHT_GRAY]);
	DrawLine(0, 759, 800, 759, 1, colors[LIGHT_GRAY]);
	DrawLine(39 , 0, 39 , 800, 1, colors[LIGHT_GRAY]);
	DrawLine(79 , 0, 79 , 800, 1, colors[LIGHT_GRAY]);
	DrawLine(119, 0, 119, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(159, 0, 159, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(199, 0, 199, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(239, 0, 239, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(279, 0, 279, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(319, 0, 319, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(359, 0, 359, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(399, 0, 399, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(439, 0, 439, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(479, 0, 479, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(519, 0, 519, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(559, 0, 559, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(599, 0, 599, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(639, 0, 639, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(679, 0, 679, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(719, 0, 719, 800, 1, colors[LIGHT_GRAY]);
	DrawLine(759, 0, 759, 800, 1, colors[LIGHT_GRAY]);*/
}
int xI = 0, yI = 760;
int x_axis_car1, y_axis_car1, x_axis_car2, y_axis_car2;

float* taxi_color;
/*
 * This function will draw a car at the given xI and yI
 * according to the taxi_color.
 **/
void drawCar() {
	if(taxi_color == colors[ORANGE]){
		DrawRoundRect(xI+10, yI+2, 20, 36, colors[BLACK], 5);
		DrawRoundRect(xI+12, yI+4, 16, 32, taxi_color, 5);
		DrawRoundRect(xI+14, yI+8, 12, 24, colors[BLACK], 5);
		DrawRoundRect(xI+16, yI+8, 8, 18, taxi_color, 2);
		DrawLine(xI+17, yI+10, xI+23, yI+10, 3, colors[BLACK]);
		DrawCircle(xI+14, yI+34, 1, colors[BLACK]);
		DrawCircle(xI+26, yI+34, 1, colors[BLACK]);
		DrawLine(xI+14, yI+8, xI+16, yI+6, 3, colors[RED]);
		DrawLine(xI+26, yI+8, xI+24, yI+6, 3, colors[RED]);
	} else if(taxi_color == colors[RED]){
		DrawRoundRect(xI+10, yI+2, 20, 36, colors[BLACK], 5);
		DrawRoundRect(xI+12, yI+4, 16, 32, taxi_color, 5);
		DrawRoundRect(xI+14, yI+8, 12, 24, colors[GRAY], 5);
		DrawRoundRect(xI+16, yI+8, 8, 18, taxi_color, 2);
		DrawLine(xI+17, yI+10, xI+23, yI+10, 3, colors[GRAY]);
		DrawCircle(xI+14, yI+34, 1, colors[GRAY]);
		DrawCircle(xI+26, yI+34, 1, colors[GRAY]);
		DrawLine(xI+14, yI+8, xI+16, yI+6, 3, colors[ORANGE]);
		DrawLine(xI+26, yI+8, xI+24, yI+6, 3, colors[ORANGE]);
	}
	/*DrawRoundRect(xI+7, yI, 26, 40, taxi_color, 10);
	DrawCircle(xI+5, yI+5, 5, colors[BLACK]);
	DrawCircle(xI+5, yI+35, 5, colors[BLACK]);
	DrawCircle(xI+35, yI+5, 5, colors[BLACK]);
	DrawCircle(xI+35, yI+35, 5, colors[BLACK]);*/
	glutPostRedisplay();
}
/*
 * This function is called when the game finishes
 * by Timer() and will update the leaderboard 
 * according to the name and scores by file
 * handling.
 **/
void leaderBoardFileHandling(){
	string tempS;
	int i = 0, j, tempI;
	fstream leaderboard;
	leaderboard.open("leaderboard.txt", ios::in | ios::out);
	while(i < 10){
		getline(leaderboard, names[i]);
		leaderboard >> individual_score[i];
		getline(leaderboard, tempS);
		i++;
	}
	for(i = 0; i < 10; i++){
		cout << names[i] << endl << individual_score[i] << endl;
	}
	for(i = 0; i < 10; i++){
		for(j = i+1; j < 10; j++){
			if(individual_score[i] < individual_score[j]){
				tempI = individual_score[i];
				individual_score[i] = individual_score[j];
				individual_score[j] = tempI;
				tempS = names[i];
				names[i] = names[j];
				names[j] = tempS;
			}
		}
	}

	if(individual_score[9] < score && score >= 20){
		individual_score[9] = score;
		names[9] = name;
	}
	for(i = 0; i < 10; i++){
		for(j = i+1; j < 10; j++){
			if(individual_score[i] < individual_score[j]){
				tempI = individual_score[i];
				individual_score[i] = individual_score[j];
				individual_score[j] = tempI;
				tempS = names[i];
				names[i] = names[j];
				names[j] = tempS;
			}
		}
	}
	leaderboard.clear();
	leaderboard.seekg(0, ios::beg);
	for(i = 0; i < 10; i++){
		if(individual_score[i] > 20){
			leaderboard << names[i] << endl;
			leaderboard << individual_score[i] << endl;
		}
	}
	leaderboard.close();
}

bool flag = true, flag2 = true;
int screens = 0;
/*
 * This function is called every second by
 * Timer function. This is the AI of random
 * cars generated on board.
 **/
void moveCar() {
	bool checkObstacle_1[4] = {1,1,1,1};
	bool checkObstacle_2[4] = {1,1,1,1};
	RandomCarCheckingFunc(x_axis_car1/40, y_axis_car1/40, checkObstacle_1);
	RandomCarCheckingFunc(x_axis_car2/40, y_axis_car2/40, checkObstacle_2);
	//Car1
	if (x_axis_car1 >= 80 && flag && checkObstacle_1[0]) {
		x_axis_car1 -= 40;
		buildings[y_axis_car1/40][x_axis_car1/40] = 5;
		buildings[y_axis_car1/40][x_axis_car1/40 + 1] = 0;
		if(x_axis_car1 < 80)
			flag = false;
	} else if (x_axis_car1 < 760 && !flag && checkObstacle_1[1]) {
		x_axis_car1 += 40;
		buildings[y_axis_car1/40][x_axis_car1/40] = 5;
		buildings[y_axis_car1/40][x_axis_car1/40 - 1] = 0;
		if (x_axis_car1 >= 720)
			flag = true;
	} else if (y_axis_car1 >= 80 && checkObstacle_1[3]) {
		y_axis_car1 -= 40;
		buildings[y_axis_car1/40][x_axis_car1/40] = 5;
		buildings[y_axis_car1/40+1][x_axis_car1/40] = 0;
		if (y_axis_car1 >= 80 && !checkObstacle_1[3]) {
			y_axis_car1 -= 40;
			buildings[y_axis_car1/40][x_axis_car1/40] = 5;
			buildings[y_axis_car1/40+1][x_axis_car1/40] = 0;
		}
	} else if (y_axis_car1 < 760 && checkObstacle_1[2]) {
		y_axis_car1 += 40;
		buildings[y_axis_car1/40][x_axis_car1/40] = 5;
		buildings[y_axis_car1/40-1][x_axis_car1/40] = 0;
		if (y_axis_car1 < 760 && !checkObstacle_1[2]) {
			y_axis_car1 += 40;
			buildings[y_axis_car1/40][x_axis_car1/40] = 5;
			buildings[y_axis_car1/40-1][x_axis_car1/40] = 0;
		}
	}
	
	//Car 2
	
	if (y_axis_car2 >= 80 && flag2 && checkObstacle_2[3]) {
		y_axis_car2 -= 40;
		buildings[y_axis_car2/40][x_axis_car2/40] = 5;
		buildings[y_axis_car2/40+1][x_axis_car2/40] = 0;
		if(y_axis_car2 < 80)
			flag2 = false;
	} else if (y_axis_car2 < 760 && !flag2 && checkObstacle_2[2]) {
		y_axis_car2 += 40;
		buildings[y_axis_car2/40][x_axis_car2/40] = 5;
		buildings[y_axis_car2/40-1][x_axis_car2/40] = 0;
		if (y_axis_car2 >= 720)
			flag2 = true;
	} else if (x_axis_car2 >= 80 && checkObstacle_2[0]) {
		x_axis_car2 -= 40;
		buildings[y_axis_car2/40][x_axis_car2/40] = 5;
		buildings[y_axis_car2/40][x_axis_car2/40 + 1] = 0;
		if (x_axis_car2 >= 80 && !checkObstacle_2[0]) {
			x_axis_car2 -= 40;
			buildings[y_axis_car2/40][x_axis_car2/40] = 5;
			buildings[y_axis_car2/40][x_axis_car2/40 + 1] = 0;
		}
	} else if (x_axis_car2 < 760 && checkObstacle_2[1]) {
		x_axis_car2 += 40;
		buildings[y_axis_car2/40][x_axis_car2/40] = 5;
		buildings[y_axis_car2/40][x_axis_car2/40 - 1] = 0;
		if (x_axis_car2 < 760 && !checkObstacle_2[1]) {
			x_axis_car2 += 40;
			buildings[y_axis_car2/40][x_axis_car2/40] = 5;
			buildings[y_axis_car2/40][x_axis_car2/40 - 1] = 0;
		}
	}
}

/*
 * This function is called every time the player
 * drops a passenger. This will check the number 
 * of passengers on the board and will generate
 * random passengers accordingly.
 * Min passenger 3, Max passenger 5.
 **/
void RandomPassenger(){
	int i, j, k, x_axis_car, y_axis_car, counts = 0;
	for(k = 0; k < 20; k++){
		for(j = 0; j < 20; j++){
			if(buildings[k][j] == 4){
				counts++;
			}
		}
	}
	if(counts < 3)
		for(i = 0; i < 3; i++){
			x_axis_car = GetRandInRange(1, 19);
			y_axis_car = GetRandInRange(0, 18);
			if(buildings[y_axis_car][x_axis_car] == 0)
				buildings[y_axis_car][x_axis_car] = 4;
		}
}
void OtherCarGenFunc(){
	// Random Input for Other cars
	int x_axis_car, y_axis_car;
	x_axis_car = GetRandInRange(0, 19);
	y_axis_car = GetRandInRange(0,19);
	if(buildings[y_axis_car][x_axis_car] == 0){
		buildings[y_axis_car][x_axis_car] = 5;
		y_axis_car1 = y_axis_car*40;
		x_axis_car1 = x_axis_car*40;
	}
	x_axis_car = GetRandInRange(0, 19);
	y_axis_car = GetRandInRange(0,19);
	if(buildings[y_axis_car][x_axis_car] == 0){
		buildings[y_axis_car][x_axis_car] = 5;
		y_axis_car2 = y_axis_car*40;
		x_axis_car2 = x_axis_car*40;
	}
}
/*
 * This is start game funtion which is called whenever
 * the start button is pressed. This will generate random
 * map everytime.
 **/
void StartGame(){
	int i, j, x_axis_tree, y_axis_tree, count;
	score = 0;
	timeMinutes = 2;
	timeSeconds = 59;
	// Random Input for Other cars
	OtherCarGenFunc();
	//	Random Input for Buildings
	for(i = 0; i < 20; i++){
		for(j = 0; j < 8; j++){
			x_axis_tree = GetRandInRange(0, 19);
			y_axis_tree = i;
			count = GetRandInRange(1, 100);
			if((buildings[x_axis_tree][y_axis_tree] == 0) && (buildings[x_axis_tree - 2][y_axis_tree] == 0) && (buildings[x_axis_tree - 1][y_axis_tree - 1] == 0) && (buildings[x_axis_tree - 1][y_axis_tree + 1] == 0) && (y_axis_tree != 0 && x_axis_tree != 19)){
				buildings[x_axis_tree][y_axis_tree] = 1;
			}
			if(count > 85){
				break;
			}
		}
	}
	//	Random Input for Trees
	for(i = 0; i < 5; i++){
		x_axis_tree = GetRandInRange(0, 18);
		y_axis_tree = GetRandInRange(1, 19);
		if(buildings[x_axis_tree][y_axis_tree] == 0 && (buildings[x_axis_tree - 2][y_axis_tree] == 0) && (buildings[x_axis_tree - 1][y_axis_tree - 1] == 0) && (buildings[x_axis_tree - 1][y_axis_tree + 1] == 0 && y_axis_tree != 0 && x_axis_tree != 19)){
			buildings[x_axis_tree][y_axis_tree] = 2;
		}
	}
	//	Random Input for Blocks
	for(i = 0; i < 5; i++){
		x_axis_tree = GetRandInRange(0, 18);
		y_axis_tree = GetRandInRange(1, 19);
		if( buildings[x_axis_tree][y_axis_tree] == 0 && (buildings[x_axis_tree - 2][y_axis_tree] == 0) && (buildings[x_axis_tree - 1][y_axis_tree - 1] == 0) && (buildings[x_axis_tree - 1][y_axis_tree + 1] == 0 && y_axis_tree != 0 && x_axis_tree != 19)){
			buildings[x_axis_tree][y_axis_tree] = 3;
		}
	}
	
	// Random Input for people
	RandomPassenger();
}
/*
 * Main Canvas drawing function.
 * This function will display content
 * according to the value of screen.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	int i, j;
	if(screens == 0){
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.25/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT);
	for(int i = 1; i <= 1050; i += 80){
		for(int j = 1; j <= 850; j += 80){
			DrawCircle(j, i, 5, colors[BLUE]);
		}
	}
	DrawRoundRect(250, 600, 300, 150, colors[BLACK], 20);
	DrawRoundRect(250, 400, 300, 150, colors[BLACK], 20);
	DrawRoundRect(250, 200, 300, 150, colors[BLACK], 20);
	DrawString(370, 665, "PLAY", colors[WHITE]);
	DrawString(315, 465, "LEADERBOARD", colors[WHITE]);
	DrawString(370, 265, "EXIT", colors[WHITE]);

	} else if(screens == 2){
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.25/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT);
		for(int i = 1; i <= 1050; i += 80){
			for(int j = 1; j <= 850; j += 80){
				DrawCircle(j, i, 5, colors[BLUE]);
			}
		}
		DrawRoundRect(225, 500, 150, 150, colors[LIGHT_BLUE], 20);
		DrawRoundRect(425, 500, 150, 150, colors[LIGHT_BLUE], 20);
		if(taxi_color == colors[RED]){
			DrawTriangle(300, 520, 290, 510, 310, 510, colors[BLACK]);			
		} else if(taxi_color == colors[ORANGE]){
			DrawTriangle(500, 520, 490, 510, 510, 510, colors[BLACK]);
		}
		DrawRoundRect(280+10, 555+2, 20, 36, colors[BLACK], 5);
		DrawRoundRect(280+12, 555+4, 16, 32, colors[RED], 5);
		DrawRoundRect(280+14, 555+8, 12, 24, colors[GRAY], 5);
		DrawRoundRect(280+16, 555+8, 8, 18, colors[RED], 2);
		DrawLine	 (280+17, 555+10, 280+23, 555+10, 3, colors[GRAY]);
		DrawCircle	 (280+14, 555+34, 1, colors[GRAY]);
		DrawCircle	 (280+26, 555+34, 1, colors[GRAY]);
		DrawLine	 (280+14, 555+8, 280+18, 555+6, 2, colors[GRAY]);
		DrawLine	 (280+26, 555+8, 280+22, 555+6, 2, colors[GRAY]);

		DrawRoundRect(480+10, 555+2, 20, 36, colors[BLACK], 5);
		DrawRoundRect(480+12, 555+4, 16, 32, colors[ORANGE], 5);
		DrawRoundRect(480+14, 555+8, 12, 24, colors[BLACK], 5);
		DrawRoundRect(480+16, 555+8, 8, 18, colors[ORANGE], 2);
		DrawLine	 (480+17, 555+10, 480+23, 555+10, 3, colors[BLACK]);
		DrawCircle	 (480+14, 555+34, 1, colors[BLACK]);
		DrawCircle	 (480+26, 555+34, 1, colors[BLACK]);
		DrawLine	 (480+14, 555+8, 480+16, 555+6, 3, colors[RED]);
		DrawLine	 (480+26, 555+8, 480+24, 555+6, 3, colors[RED]);
		DrawRoundRect(250,   400, 300, 50, colors[WHITE], 10);
		DrawString(265, 	 415, name, colors[BLACK]);
		DrawRoundRect(250,   250, 300, 100, colors[WHITE], 10);
		DrawString(360, 	 295, "START", colors[BLACK]);
		DrawRoundRect(100, 80, 225, 40, colors[LIGHT_BLUE], 20);
		DrawString(140, 90, "MAIN MENU", colors[BLACK]);
	} else if(screens == 1){
		glClearColor(255/*Red Component*/, 255,	//148.0/255/*Green Component*/,
				255/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawMap();
		drawCar();
		DrawRectangle(0, 805, 800, 200, colors[BLACK]);
		DrawString(50, 850, "SCORE: ", colors[WHITE]);
		DrawString(150, 850, Num2Str(score), colors[WHITE]);
		DrawString(400, 850, "TIME REMAINING: ", colors[WHITE]);
		DrawString(625, 850, Num2Str(timeMinutes), colors[WHITE]);
		DrawString(633, 850, " : ", colors[WHITE]);
		DrawString(650, 850, Num2Str(timeSeconds), colors[WHITE]);
	} else if(screens == 3){
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.25/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT);
		for(int i = 1; i <= 1050; i += 80){
			for(int j = 1; j <= 850; j += 80){
				DrawCircle(j, i, 5, colors[BLACK]);
			}
		}
		DrawString(100, 800, "LEADERBOARD", colors[WHITE]);
		for(i = 720, j = 0; j < 10; i -= 50, j++){
			if(individual_score[j] >= 20){
			DrawString(100, i, names[j], colors[WHITE]);
			DrawString(400, i, Num2Str(individual_score[j]), colors[WHITE]);
			}
		}
		DrawRoundRect(100, 100, 225, 40, colors[LIGHT_BLUE], 20);
		DrawString(140, 110, "MAIN MENU", colors[BLACK]);
	} else if(screens == 4){
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.25/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT);
		for(int i = 1; i <= 1050; i += 80){
			for(int j = 1; j <= 850; j += 80){
				DrawCircle(j, i, 5, colors[BLACK]);
			}
		}
		//Y
		DrawLine(50, 600, 100, 500, 20, colors[WHITE]);
		DrawLine(150, 600, 100, 500, 20, colors[WHITE]);
		DrawLine(100, 500, 100, 400, 20, colors[WHITE]);
		//O
		Torus2d(225, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		Torus2d(225, 555, 0, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(190, 445, 190, 555, 20, colors[WHITE]);
		DrawLine(260, 445, 260, 555, 20, colors[WHITE]);
		//U
		Torus2d(330, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(295, 445, 295, 600, 20, colors[WHITE]);
		DrawLine(365, 445, 365, 600, 20, colors[WHITE]);
		//W
		DrawLine(455, 600, 490, 400, 20, colors[WHITE]);
		DrawLine(490, 400, 525, 500, 20, colors[WHITE]);
		DrawLine(525, 500, 560, 400, 20, colors[WHITE]);
		DrawLine(560, 400, 595, 600, 20, colors[WHITE]);
		//I
		DrawLine(625, 600, 625, 400, 20, colors[WHITE]);
		//N
		DrawLine(655, 600, 655, 400, 20, colors[WHITE]);
		DrawLine(655, 600, 710, 400, 20, colors[WHITE]);
		DrawLine(710, 600, 710, 400, 20, colors[WHITE]);
		//Main Menu
		DrawRoundRect(100, 100, 225, 40, colors[LIGHT_BLUE], 20);
		DrawString(140, 110, "MAIN MENU", colors[BLACK]);
	} else if(screens == 5){
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.25/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT);
		for(int i = 1; i <= 1050; i += 80){
			for(int j = 1; j <= 850; j += 80){
				DrawCircle(j, i, 5, colors[BLACK]);
			}
		}
		//Y
		DrawLine(40, 600, 90, 500, 20, colors[WHITE]);
		DrawLine(140, 600, 90, 500, 20, colors[WHITE]);
		DrawLine(90, 500, 90, 400, 20, colors[WHITE]);
		//O
		Torus2d(215, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		Torus2d(215, 555, 0, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(180, 445, 180, 555, 20, colors[WHITE]);
		DrawLine(250, 445, 250, 555, 20, colors[WHITE]);
		//U
		Torus2d(320, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(285, 445, 285, 600, 20, colors[WHITE]);
		DrawLine(355, 445, 355, 600, 20, colors[WHITE]);
		//L
		DrawLine(425, 600, 425, 400, 20, colors[WHITE]);
		DrawLine(415, 410, 490, 410, 20, colors[WHITE]);
		//O
		Torus2d(550, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		Torus2d(550, 555, 0, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(515, 445, 515, 555, 20, colors[WHITE]);
		DrawLine(585, 445, 585, 555, 20, colors[WHITE]);
		//S
		Torus2d(650, 445, 180, 180, 25, 20, 100, colors[WHITE]);
		Torus2d(650, 555, 0, 180, 25, 20, 100, colors[WHITE]);
		DrawLine(615, 555, 685, 445, 20, colors[WHITE]);
		//E
		DrawLine(715, 600, 715, 400, 20, colors[WHITE]);
		DrawLine(715, 590, 780, 590, 20, colors[WHITE]);
		DrawLine(715, 500, 780, 500, 20, colors[WHITE]);
		DrawLine(715, 410, 780, 410, 20, colors[WHITE]);
		//Main Menu
		DrawRoundRect(100, 100, 225, 40, colors[LIGHT_BLUE], 20);
		DrawString(140, 110, "MAIN MENU", colors[BLACK]);
	}
	
	glutSwapBuffers(); // do not modify this line..

}

/*
 *This function when called will update the passed array of
 *Bool datatype in according to the passenger's direction
 *W. R. T. the car. This is used for score deduction
*/
void PassengerCheckFunc(int x_axis, int y_axis, bool check[]){
	if((buildings[y_axis][x_axis-1] == 4)){
		 check[0] = true;
	 }else if((buildings[y_axis][x_axis+1] == 4)){
		 check[1] = true;
	 }else if((buildings[y_axis+1][x_axis] == 4)){
		 check[2] = true;
	 } else if((buildings[y_axis-1][x_axis] == 4)){
		 check[3] = true;
	 }
}
/*
 *This Function will check for other cars which are randomly generated
 * and randomly moving.This function is used for deducting scores
 * of player. Bool array is passed which is updated 
 * according to the direction of other car nearby.
*/
void OtherCarCheckFunc(int x_axis, int y_axis, bool check[]){
	if((buildings[y_axis][x_axis-1] == 5)){
		 check[0] = true;
	 }else if((buildings[y_axis][x_axis+1] == 5)){
		 check[1] = true;
	 }else if((buildings[y_axis+1][x_axis] == 5)){
		 check[2] = true;
	 } else if((buildings[y_axis-1][x_axis] == 5)){
		 check[3] = true;
	 }
}


/*
 *This function will check for obstacles such as tree and boxes.
 *This function is used for score deduction.
*/
void ObstacleCheckFunc(int x_axis, int y_axis, bool check[]){
	if((buildings[y_axis][x_axis-1] == 2) || (buildings[y_axis][x_axis-1] == 3)){
		 check[0] = true;
	}else if((buildings[y_axis][x_axis+1] == 2) || (buildings[y_axis][x_axis+1] == 3)){
		 check[1] = true;
	}else if((buildings[y_axis+1][x_axis] == 2) || (buildings[y_axis+1][x_axis] == 3)){
		 check[2] = true;
	} else if((buildings[y_axis-1][x_axis] == 2) || (buildings[y_axis-1][x_axis] == 3)){
		 check[3] = true;
	}
}
/*
 *This function will generate random destination 
 *whenever a passenger is picked up from a location.
*/
void RandDestination(){
	for(int i = 0; i < 20; i++){
		int x_axis_dest = GetRandInRange(0, 18);
		int y_axis_dest = GetRandInRange(1, 19);
		if(buildings[x_axis_dest][y_axis_dest] == 0){
			buildings[x_axis_dest][y_axis_dest] = 6;
			break;
		}
	}
}

/*
 * This function is called everytime we press a non printable
 * key. This is responsible for collision detection and score
 * deduction.
 **/
void NonPrintableKeys(int key, int x, int y) {
	bool buildingCheck[4] = {1,1,1,1};
	bool OtherCarCheck[4] = {0,0,0,0};
	bool ObstacleCheck[4] = {0,0,0,0};
	bool PassengerCheck[4] = {0,0,0,0};
	buildingCheckFunc((xI/40), (yI/40), buildingCheck);
	OtherCarCheckFunc((xI/40), (yI/40), OtherCarCheck);
	ObstacleCheckFunc((xI/40), (yI/40), ObstacleCheck);
	PassengerCheckFunc((xI/40), (yI/40), PassengerCheck);
	//bool left = leftCheck((xI / 40), (yI / 40));
	//bool right = rightCheck()
	//	Movement
	if (key == GLUT_KEY_LEFT && (xI != 0) && buildingCheck[0]/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if(taxi_color == colors[RED] && ((timeSeconds % 2) == 0))
			xI -= 40;
		else if(taxi_color == colors[ORANGE])
			xI -= 40;
	} else if (key == GLUT_KEY_RIGHT && (xI != 760) && buildingCheck[1]/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if(taxi_color == colors[RED] && ((timeSeconds % 2) == 0))
			xI += 40;
		else if(taxi_color == colors[ORANGE]){
			xI += 40;
		}
	} else if (key == GLUT_KEY_UP && (yI != 760) && buildingCheck[2]/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		if(taxi_color == colors[RED] && ((timeSeconds % 2) == 0))
			yI += 40;
		else if(taxi_color == colors[ORANGE]){
			yI += 40;
		}
	} else if (key == GLUT_KEY_DOWN && (yI != 0) && buildingCheck[3]/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if(taxi_color == colors[RED] && ((timeSeconds % 2) == 0))
			yI -= 40;
		else if(taxi_color == colors[ORANGE]){
			yI -= 40;
		}
	}
	// Score Increased by One
	if ((key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) && (OtherCarCheck[2] || OtherCarCheck[3]) && isPassenger/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		score++;
	} else if ((key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) && (OtherCarCheck[0] || OtherCarCheck[1]) && isPassenger/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		score++;
	}
	//	Score Decreased by 5 on hitting a passenger
	if((taxi_color == colors[RED] || taxi_color == colors[ORANGE]) && (key == GLUT_KEY_LEFT) && PassengerCheck[0]){
		score -= 5;
	} else if((taxi_color == colors[RED] || taxi_color == colors[ORANGE]) && (key == GLUT_KEY_RIGHT) && PassengerCheck[1]){
		score -= 5;
	} else if((taxi_color == colors[RED] || taxi_color == colors[ORANGE]) && (key == GLUT_KEY_UP) && PassengerCheck[2]){
		score -= 5;
	} else if((taxi_color == colors[RED] || taxi_color == colors[ORANGE]) && (key == GLUT_KEY_DOWN) && PassengerCheck[3]){
		score -= 5;
	}
	// Score Decreased by 2 on hitting obstacle for RED taxi
	if((taxi_color == colors[RED]) && (key == GLUT_KEY_LEFT) && ObstacleCheck[0]){
		score -= 2;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_RIGHT) && ObstacleCheck[1]){
		score -= 2;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_UP) && ObstacleCheck[2]){
		score -= 2;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_DOWN) && ObstacleCheck[3]){
		score -= 2;
	}
	// Score Decreased by 4 on hitting obstacle for YELLOW taxi
	if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_LEFT) && ObstacleCheck[0]){
		score -= 4;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_RIGHT) && ObstacleCheck[1]){
		score -= 4;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_UP) && ObstacleCheck[2]){
		score -= 4;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_DOWN) && ObstacleCheck[3]){
		score -= 4;
	}
	// Score Decreased by 3 on hitting other car for RED taxi
	if((taxi_color == colors[RED]) && (key == GLUT_KEY_LEFT) && OtherCarCheck[0]){
		score -= 3;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_RIGHT) && OtherCarCheck[1]){
		score -= 3;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_UP) && OtherCarCheck[2]){
		score -= 3;
	} else if((taxi_color == colors[RED]) && (key == GLUT_KEY_DOWN) && OtherCarCheck[3]){
		score -= 3;
	}
	// Score Decreased by 2 on hitting other car for YELLOW taxi
	if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_LEFT) && OtherCarCheck[0]){
		score -= 2;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_RIGHT) && OtherCarCheck[1]){
		score -= 2;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_UP) && OtherCarCheck[2]){
		score -= 2;
	} else if((taxi_color == colors[ORANGE]) && (key == GLUT_KEY_DOWN) && OtherCarCheck[3]){
		score -= 2;
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	bool PassengerCheck[4] = {0};
	PassengerCheckFunc((xI/40), (yI/40), PassengerCheck);
	bool DestCheck = 0;
	char ch;
	static int counter = 1;
	if((buildings[yI/ 40][xI/ 40] == 6)){
		 DestCheck = true;
	}
	if(key == ' ' && PassengerCheck[0] && !isPassenger){
		RandDestination();
		buildings[yI/40][(xI/40) - 1] = 0;
		isPassenger = true;
	} else if(key == ' ' && PassengerCheck[1] && !isPassenger){
		RandDestination();
		buildings[yI/40][(xI/40) + 1] = 0;
		isPassenger = true;
	} else if(key == ' ' && PassengerCheck[2] && !isPassenger){
		RandDestination();
		buildings[(yI/40) + 1][(xI/40)] = 0;
		isPassenger = true;
	} else if(key == ' ' && PassengerCheck[3] && !isPassenger){
		RandDestination();
		buildings[(yI/40) - 1][(xI/40)] = 0;
		isPassenger = true;
	}
	if(key == ' ' && DestCheck){
		buildings[yI/40][(xI/40)] = 0;
		score += 10;
		RandomPassenger();
		isPassenger = false;
		counter++;
		if((counter % 3) == 0){
			speed+=200;
			OtherCarGenFunc();
		}
	}
	if(((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key == ' ') || (key == 8)) && (screens == 2)){
		if(key == 8){
			name.pop_back();
		}else{
		ch = key;
		name += ch;
		}
	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	timeSeconds--;
	if(timeSeconds == 0 && timeMinutes>=0){
		if(score >= 100 && timeMinutes == 0 && timeSeconds == 0 && screens == 1){
			leaderBoardFileHandling();
			screens = 4;
		}else if(score <= 100 && timeMinutes == 0 && timeSeconds == 0 && screens == 1){
			screens = 5;
		}
		timeMinutes--;
		timeSeconds = 59;
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

void Speed(int m) {

	// implement your functionality here
	moveCar();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000-speed, Speed, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	int randomColor = GetRandInRange(1, 100);
	if (button == GLUT_LEFT_BUTTON && x >= 250 && x <= 550 && y >= 150 && y <= 300 && screens == 0) // dealing only with left button
	{
		screens = 2;
		if(randomColor >= 1 && randomColor <= 50)
			taxi_color = colors[RED];
		else if(randomColor > 50 && randomColor <= 100)
			taxi_color = colors[ORANGE];
	} else if(button == GLUT_LEFT_BUTTON && x >= 250 && x <= 550 && y >= 350 && y <= 500 && screens == 0){
		screens = 3;
	} else if(button == GLUT_LEFT_BUTTON && x >= 225 && x <= 380 && y >= 250 && y <= 400 && screens == 2){
		taxi_color = colors[RED];
	} else if(button == GLUT_LEFT_BUTTON && x >= 425 && x <= 580 && y >= 250 && y <= 400 && screens == 2){
		taxi_color = colors[ORANGE];
	} else if(button == GLUT_LEFT_BUTTON && x >= 250 && x <= 550 && y >= 550 && y <= 650 && screens == 2){
		StartGame();
		screens = 1;
	} else if((button == GLUT_LEFT_BUTTON && x >= 100 && x <= 325 && y >= 780 && y <= 820) && (screens == 2 || screens == 3) || (screens == 4 || screens == 5)){
		screens = 0;
	} else if(button == GLUT_LEFT_BUTTON && x >= 250 && x <= 550 && y >= 550 && y <= 700 && screens == 0){
		exit(1);
	}
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]){

	int width = 800, height = 900, i = 0; // i have set my window size to be 800 x 800
	string tempS;
	//	GAME
	
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Usman Naeem"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	//Random Taxi Color
	int randomColor = GetRandInRange(1, 100);
	if(randomColor >= 1 && randomColor <= 50)
		taxi_color = colors[RED];
	else if(randomColor > 50 && randomColor <= 100)
		taxi_color = colors[ORANGE];
	
	// Random taxi color
	// int randomColor = GetRandInRange(1, 100);
	// if(randomColor >= 1 && randomColor <= 50)
	// 	taxi_color = colors[RED];
	// else if(randomColor > 50 && randomColor <= 100)
	// 	taxi_color = colors[ORANGE];
	
	//Fetching Leaderboard
	ifstream l_board;
	l_board.open("leaderboard.txt", ios::in);
	while(i < 10){
		getline(l_board, names[i]);
		l_board >> individual_score[i];
		getline(l_board, tempS);
		i++;
	}
	l_board.close();
	
	
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(1000.0, Speed, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
