#include<string>
#include "game.h"
#ifndef draw_h_
#define draw_h_


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 650;

const int carHeight = 160;
const int carWidth = 70;
const int startX = 150;
const int startY = 0;
const int finishX = 380;
const int finishY = 490;

const std :: string road[4] = {"road1.png", "road2.png", "road3.png", "road4.png"};


void initWindow();
void updateBg(int level);
void close();
void startGame();
void endG();

#endif draw_h_h;

