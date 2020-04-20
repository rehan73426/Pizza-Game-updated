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

static SDL_Texture *pete[2];

void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	player->health = 4;
	stage.gameover = 0;
	pete[0] = loadTexture("gfx/Hunter01.png");
	pete[1] = loadTexture("gfx/Hunter02.png");

	player->texture = pete[0];

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
	player->dx = 0;
	stage.x = player->x;
	stage.y = player->y;
	if (stage.playing == 1){
		if (app.keyboard[SDL_SCANCODE_A])
		{
			player->dx = -PLAYER_MOVE_SPEED;

			player->texture = pete[1];
			

		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			player->dx = PLAYER_MOVE_SPEED;

			player->texture = pete[0];
		}

		if (app.keyboard[SDL_SCANCODE_SPACE] && player->isOnGround)
		{
			player->riding = NULL;

			player->dy = -30;

			playSound(SND_JUMP, CH_PLAYER);
		}

		if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			player->x = player->y = 10;

			app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
		}
	}

	//////////////////////////////////Changes////////////////////////////////////////

	//	Keys fixed I to space and space to Escape/////////////


	//////////////////////////////////////////////////////
}
