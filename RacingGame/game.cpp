#include<bits/bits-stdc++.h>
#include <SDL.h>
#include <SDL_image.h>	
#include <stdio.h>
#include <string>
#include "draw.h"
#include "game.h"

int min(int x, int y) {
	if (x > y)return y;
	return x;
}

int max(int x, int y) {
	if (x < y)return y;
	return x;
}


void Game::init() {

	for (int i = 0; i < numCar; i++) police[i].y = finishY + 1000;
	speed = 3;
	posBg = { 0,550 };
	posCar = { 250,400 };
	score = 0;
	level = 0;
	moveStep = 20;
	endGame = false;
	restart = false;
	startTime = std::clock();

}

void Game::checkPos() {
	posBg.y -= speed;
	if (posBg.y <= 2) posBg.y = 550;
	posCar.x = max(posCar.x, startX);
	posCar.y = max(posCar.y, startY);
	posCar.x = min(posCar.x, finishX);
	posCar.y = min(posCar.y, finishY);
}

bool Game::createCar(int x, int y) {

	for (int i = 0; i < numCar; i++)
		if (police[i].y < 0 && ((y <= police[i].y && police[i].y <= y + 4 * carHeight) || (police[i].y <= y && y <= police[i].y + 4 * carHeight))) {
			if (abs(x - police[i].x) < 2 * carHeight)return false;
		}
	return true;
}

void Game::update() {
	for (int i = 0; i < numCar; i++)
		if (police[i].y > finishY + carHeight)
		{
			int x, y;
			while (true) {
				x = ((rand() / 10) % (finishX - startX)) + startX;
				y = -(rand() % ((finishY - startY) * 10 * (level + 1)));
				if (createCar(x, y))break;
			}
			int z = rand() % 2;
			police[i] = { x,y,z };
		}
	for (int i = 0; i < numCar; i++)police[i].y += speed;
	if (score >= targetScore[level])
	{
		level++;
		speed += 3;
		moveStep += 10;
		posBg.y = 550;
	}
}

bool Game::collision() {
	//chekiar cuando se pruebe el juego
	for (int i = 0; i < numCar; i++) {

		if ((police[i].x < posCar.x && posCar.x < police[i].x + carWidth && police[i].y < posCar.y && posCar.y < police[i].y + carHeight)
			|| (police[i].x < posCar.x && posCar.x < police[i].x + carWidth && police[i].y < posCar.y + carHeight && posCar.y + carHeight < police[i].y + carHeight)
			|| (police[i].x < posCar.x - carWidth && posCar.x + carWidth < police[i].x + carWidth && police[i].y < posCar.y && posCar.y < police[i].y + carHeight)
			|| (police[i].x < posCar.x + carWidth && posCar.x + carWidth < police[i].x + carWidth && police[i].y < posCar.y + carHeight && posCar.y + carHeight < police[i].y + carHeight)
			)
		{
			return true;
		}

	}
	return false;
}


void Game::run() {
	srand(time(NULL));
	bool quit = false;
	SDL_Event e;

	int mouseX, mouseY;

	initWindow();
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	startGame();
	while (!quit) {

		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) quit = true;
			if (played || e.type == SDL_MOUSEBUTTONDOWN && mouseX >= 140 && mouseY >= 465 && mouseX <= 465 && mouseY <= 540)
			{
				played = true;
				if (restart) {
					init();
				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP]) {
					posCar.y -= moveStep;
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
					posCar.y += moveStep;
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
					posCar.x -= moveStep;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
					posCar.x += moveStep;
				}
				if (endGame)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN && mouseX >= 140 && mouseY >= 465 && mouseX <= 465 && mouseY <= 540)
					{
						restart = true;
					}
				}
			}


		}
		if (played)
		{
			checkPos();
			update();
			if (!endGame)render();
			if (!endGame && collision())
			{
				endGame = true;
				for (int i = 0; i < 250; i++)render();
			}
			if (endGame)
			{
				endG();
			}

		}
		if (e.type == SDL_MOUSEMOTION) {
			mouseX = e.button.x;
			mouseY = e.button.y;
		}
	 frameTime = SDL_GetTicks() - frameStart;
	 if (frameDelay > frameTime) {
		 SDL_Delay(frameDelay - frameTime);
	 }
	
	}
	close();
}























