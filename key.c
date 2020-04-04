/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:18:51 by tclarita          #+#    #+#             */
/*   Updated: 2020/04/01 12:21:25 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	process(t_wolf *sdl, t_player *player)
{
	SDL_PollEvent(&sdl->event);
	switch (sdl->event.type)
	{
		case SDL_QUIT: 
			destroy_window(sdl);
		case SDL_KEYDOWN:
		{
			if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
				destroy_window(sdl);
			if (sdl->event.key.keysym.sym == SDLK_UP)
				player->walk_direction = 1;
			if (sdl->event.key.keysym.sym == SDLK_DOWN)
				player->walk_direction = -1;
			if (sdl->event.key.keysym.sym == SDLK_RIGHT)
				player->turn_direction = 1;
			if (sdl->event.key.keysym.sym == SDLK_LEFT)
				player->turn_direction = -1;
			break ;
		}
		case SDL_KEYUP:
		{
			if (sdl->event.key.keysym.sym == SDLK_UP)
				player->walk_direction = 0;
			if (sdl->event.key.keysym.sym == SDLK_DOWN)
				player->walk_direction = 0;
			if (sdl->event.key.keysym.sym == SDLK_RIGHT)
				player->turn_direction = 0;
			if (sdl->event.key.keysym.sym == SDLK_LEFT)
				player->turn_direction = 0;
			break;
		}
	}
}
