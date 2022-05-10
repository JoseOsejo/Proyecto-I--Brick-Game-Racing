#include<bits/bits-stdc++.h>
#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "draw.h"
#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer;
SDL_Surface* surface[9];
SDL_Texture* texture[9];
TTF_Font* font = NULL;
SDL_Color textColor = {255, 255, 255};



void initWindow() 
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0) 
	{
		window = SDL_CreateWindow("Racing Game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if (window != NULL) 
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer != NULL)
			SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF);
		}

		
	}
	//modificar imagenes 
	surface[0] = IMG_Load("images/background.png");
	texture[0] = SDL_CreateTextureFromSurface(renderer, surface[0]);
	surface[1] = IMG_Load("images/car.png");
	texture[1] = SDL_CreateTextureFromSurface(renderer, surface[1]);
	surface[2] = IMG_Load("images/car2.png");
	texture[2] = SDL_CreateTextureFromSurface(renderer, surface[2]);	
	surface[3] = IMG_Load("images/car3.png");
	texture[3] = SDL_CreateTextureFromSurface(renderer, surface[3]);
	surface[4] = IMG_Load("images/car4.png");
	texture[4] = SDL_CreateTextureFromSurface(renderer, surface[4]);
	surface[5] = IMG_Load("images/car5.png");
	texture[5] = SDL_CreateTextureFromSurface(renderer, surface[5]);
	surface[6] = IMG_Load("images/car6.png");
	texture[6] = SDL_CreateTextureFromSurface(renderer, surface[6]);
	surface[7] = IMG_Load("images/car7.png");
	texture[7] = SDL_CreateTextureFromSurface(renderer, surface[7]);
	surface[8] = IMG_Load("images/car8.png");
	texture[8] = SDL_CreateTextureFromSurface(renderer, surface[8]);
	
	TTF_Init();
	font = TTF_OpenFont("superstar.ttf", 50);
}


void printText(std::string text, int x, int y) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dest;
	dest.x = x+(20*(5-text.size())/2);
	dest.y = y;
	dest.x = 20 * text.size();
	dest.h = 50;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Game::printScoreAndLevel() 
{
	std::string text;
	text = "LEVEL";
	printText(text, 24, 240);
	text = "SCORE";
	printText(text, 470,240);
	char buffer[100];
	itoa(level + 1, buffer, 10);
	text = std::string(buffer);
	printText(text, 24, 250);
	itoa(score, buffer, 10);
	text = std::string(buffer);
	printText(text, 470, 290);
}

void loadMedia(int ob, point rect1, point rect2) 
{
	SDL_Rect dest1 = {rect1.x, rect1.y,min(SCREEN_WIDTH,surface[ob]->w),min(SCREEN_HEIGHT,surface[ob]->h)};
	SDL_Rect dest2 = {rect2.x, rect2.y,min(SCREEN_WIDTH,surface[ob]->w),min(SCREEN_HEIGHT,surface[ob]->h)};
	SDL_RenderCopy(renderer, texture[ob], &dest1, &dest2);
}

void startGame() 
{
	point po = { 0,0 };
	loadMedia(7,po,po);
	SDL_RenderPresent (renderer);
}

void endG() 
{
	point po = { 0,0 };
	loadMedia(8, po, po);
	SDL_RenderPresent(renderer);
}


void Game::render() 
{
	if(!endGame)score = ((std::clock() - startTime) / (double)CLOCKS_PER_SEC);
	point po = { 0,0 };

	loadMedia(level, posBg, po);
	loadMedia(4, po, posCar);
	for (int i = 0; i < numCar; i++) 
		if (police[i].y + carHeight >= startY && police[i].y <= finishY + carHeight) 
		{
			loadMedia(police[i].z + 5, po, police[i]);
		}
	printScoreAndLevel();
	SDL_RenderPresent(renderer);
}

void close() 
{

	SDL_DestroyTexture (texture[0]);
	texture[0] = NULL;
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}





















