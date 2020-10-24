/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:18:51 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/24 17:52:11 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sdl_key_down(t_wolf *sdl, t_player *player, t_music *music)
{
	if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
		destroy_window(sdl, music);
	if (sdl->event.key.keysym.sym == SDLK_UP)
		player->walk_direction = 1;
	if (sdl->event.key.keysym.sym == SDLK_DOWN)
		player->walk_direction = -1;
	if (sdl->event.key.keysym.sym == SDLK_RIGHT)
		player->turn_direction = 1;
	if (sdl->event.key.keysym.sym == SDLK_LEFT)
		player->turn_direction = -1;
}

void	sdl_key_up(t_wolf *sdl, t_player *player)
{
	if (sdl->event.key.keysym.sym == SDLK_UP)
		player->walk_direction = 0;
	if (sdl->event.key.keysym.sym == SDLK_DOWN)
		player->walk_direction = 0;
	if (sdl->event.key.keysym.sym == SDLK_RIGHT)
		player->turn_direction = 0;
	if (sdl->event.key.keysym.sym == SDLK_LEFT)
		player->turn_direction = 0;
}

void	process(t_wolf *sdl, t_player *player, t_music *music)
{
	SDL_PollEvent(&sdl->event);
		if(sdl->event.type == SDL_QUIT)
			destroy_window(sdl, music);
		if(sdl->event.type == SDL_KEYDOWN)
			sdl_key_down(sdl, player, music);
		if(sdl->event.type == SDL_KEYUP)
			sdl_key_up(sdl, player);
}
