#include<iostream>
#ifndef game_h_
#define game_h_

struct point {
	int x,y,z;
};
const int targetScore[4] = {20,40,70,7000};
const int numCar = 5;
int min(int x , int y);
int max(int x , int y);
class Game 
{
 
	int speed = 4;
	point posBg = {0,550};
	point posCar = {250,400};
	point police[numCar];
	bool played = false;
	int score = 0;
	int level = 0;
	int moveStep = 20;
	bool endGame = false;
	bool restart = true;
	int startTime;


public:
	void init();
	void run();
	void update();
private:
	void checkPos();
	bool createCar(int x, int y);
	bool collision();
	void render();
	void printScoreAndLevel();
};
#endif game_h_h;

