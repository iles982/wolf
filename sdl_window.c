/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:16:49 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/20 10:30:35 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    init_window(t_wolf *sdl)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("%s", "Error init_SDL");
	sdl->window = SDL_CreateWindow("Wolf", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (!(sdl->window))
		printf("%s", "Window Error");
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
	if (!sdl->renderer)
		printf("%s", "Error Renderer");
	SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);
}

void	destroy_window(t_wolf *sdl)
{
	free(sdl->color_buf);
	free(sdl->wall_text);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
}
