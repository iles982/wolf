/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:13:57 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/19 14:07:22 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "textures.h"

void	get_player_pos(t_wolf *sdl, t_player *player)
{
	int y;
	int x;

	x = 1;
	while (x < sdl->map_num_col)
	{
		y = 1;
		while (y < sdl->map_num_row)
		{
			if (sdl->map[y][x] == 0)
			{
				player->x = x * sdl->tile_size + 1;
				player->y = y * sdl->tile_size + 1;
				return ;
			}
			y++;
		}
		x++;
	}
}

void	setup(t_wolf *sdl, t_player *player)
{
	sdl->frame_ticks = 0;
	sdl->pi = 3.14159265;
	sdl->two_pi = 6.28318530;
	sdl->tile_size = 64;
	sdl->fov_angle = 60 * (sdl->pi / 180);
	sdl->num_rays = 1280;
	sdl->scale_factor = 0.27;
	sdl->color_buf = (Uint32 *)malloc(sizeof(Uint32) * (Uint32)WINDOW_HEIGHT * (Uint32)WINDOW_WIDTH);
	sdl->color_buf_text = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ABGR8888,
	SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	sdl->textures[3] = (Uint32 *)DIRT;
	sdl->textures[2] = (Uint32 *)BOOK;
	sdl->textures[1] = (Uint32 *)STONE;
	sdl->textures[0] = (Uint32 *)WALL;
	get_player_pos(sdl, player);
	player->height = 1;
	player->width = 1;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotat_angle = sdl->pi / 2;
	player->walk_speed = 5;
	player->turn_speed = 2 * 45 * (sdl->pi / 180);
}