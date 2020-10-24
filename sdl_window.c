/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:16:49 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/24 18:29:57 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_map(t_wolf *sdl)
{
	int i = 0;
	while (sdl->map)
	{
		free(sdl->map[i]);
		i++;
	}
	free(sdl->map);
}

void	init_music(t_music *music)
{;
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) 
	{
		printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
		exit (1);
	}
	music->music = Mix_LoadMUS("YaYo.mp3");
	Mix_VolumeMusic(30);
	Mix_PlayMusic(music->music, -1);
}

void	init_window(t_wolf *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_putstr("Error init_SDL\n");
		exit(1);
	}
	sdl->window = SDL_CreateWindow("Wolf", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (!(sdl->window))
	{
		ft_putstr("Window Error\n");
		exit(1);
	}
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
	if (!sdl->renderer)
	{
		ft_putstr("Error Renderer\n");
		exit(1);
	}
	SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);
}

void	destroy_window(t_wolf *sdl, t_music *music)
{
	int i;

	Mix_FreeMusic(music->music);
	Mix_CloseAudio();
	free_map(sdl);
	free(sdl->map);
	free(sdl->color_buf);
	SDL_RenderClear(sdl->renderer);
	SDL_DestroyTexture(sdl->color_buf_text);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit (0);
}
