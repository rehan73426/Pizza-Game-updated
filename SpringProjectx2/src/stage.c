/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

static void logic(void);
static void draw(void);
static void drawHud(void);

void initStage(void)
{

	stage.playing = 1;
	//////////////////////////////////////////
	///////////////////Playing/////////////////////
	///////////////////////////
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 192, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();

	drawEntities();

	drawHud();
}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
	FILE *fptr;

	fptr = fopen("score.dat", "r");

	// display numbers=
	fscanf(fptr, "%d", &stage.HiScore);
	fclose(fptr);
	drawText(5, 5, 255, 255, 255, TEXT_LEFT, "HI:%d", stage.HiScore);
	//////////////////////////////////////////////////////
	/////////hi SCORE ADDED/////////////////
	////////////////////////////////////
	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "PIZZA %d/%d", stage.pizzaFound, stage.pizzaTotal);
	//drawText(SCREEN_WIDTH - 205, 5, 255, 255, 255, TEXT_RIGHT, "LIFE %d,%d", stage.x, stage.y);
	drawText(SCREEN_WIDTH - 205, 5, 255, 255, 255, TEXT_RIGHT, "LIFE %d", player->health-1);
	
	if (stage.playing == 0&&app.keyboard[SDL_SCANCODE_P]){
		stage.playing = 1;


	}
	if (app.keyboard[SDL_SCANCODE_F1]){
		stage.playing = 0;

	}



	if (stage.playing==0)
	{
		r.x = 0;
		r.y = 0;
		r.w = SCREEN_WIDTH;
		r.h = SCREEN_HEIGHT;
		SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(app.renderer, &r);
		SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "PRESS P TO START GAME");
		drawText(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)+40, 255, 255, 255, TEXT_CENTER, "PRESS F1 TO RESUME");

	}

	if (stage.gameover == 1)
	{
		r.x = 0;
		r.y = 0;
		r.w = SCREEN_WIDTH;
		r.h = SCREEN_HEIGHT;
		SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(app.renderer, &r);
		SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

		drawText(SCREEN_WIDTH / 2,( SCREEN_HEIGHT / 2)-40, 255, 255, 255, TEXT_CENTER, "GAME OVER");
		drawText(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 20, 255, 255, 255, TEXT_CENTER, "HI SCORE:%d",stage.HiScore);
		drawText(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 80, 255, 255, 255, TEXT_CENTER, "YOUR SCORE IS:%d ", stage.pizzaFound);
		if (app.keyboard[SDL_SCANCODE_ESCAPE]){
			stage.playing = 0;

		}
	}
}
