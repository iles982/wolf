/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 12:14:25 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/19 12:21:44 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	render_player(t_wolf *sdl, t_player *player)
{
	SDL_SetRenderDrawColor(sdl->renderer, 251, 25, 25, 255);
	SDL_Rect player_rect = {player->x * sdl->scale_factor, player->y * sdl->scale_factor,
	player->width * sdl->scale_factor, player->height * sdl->scale_factor};
	SDL_RenderFillRect(sdl->renderer, &player_rect);
	SDL_RenderDrawLine(sdl->renderer, player->x * sdl->scale_factor, player->y * sdl->scale_factor,
	sdl->scale_factor * player->x + cos(player->rotat_angle) * 10,
	sdl->scale_factor * player->y + sin(player->rotat_angle) * 10);
}

void	render_rays(t_wolf *sdl, t_ray ray[1280], t_player *player)
{
	SDL_SetRenderDrawColor(sdl->renderer, 76, 0, 153, 255);
	int i = 0;
	while (i < sdl->num_rays)
	{
		SDL_RenderDrawLine(sdl->renderer, sdl->scale_factor * player->x,
		sdl->scale_factor * player->y, sdl->scale_factor * ray[i].wall_hit_x,
		sdl->scale_factor * ray[i].wall_hit_y);
		i++;
	}
}

void	render_map(t_wolf *sdl)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;
	int	tile_color;

	i = 0;
	while (i < sdl->map_num_row)
	{
		j = 0;
		while (j < sdl->map_num_col)
		{
			tile_x = j * sdl->tile_size;
			tile_y = i * sdl->tile_size;
			tile_color = sdl->map[i][j] != 0 ? 255 : 0;
			SDL_SetRenderDrawColor(sdl->renderer, tile_color, tile_color, tile_color, tile_color);
			SDL_Rect map_tile_rect = {tile_x * sdl->scale_factor, tile_y * sdl->scale_factor,
			sdl->tile_size * sdl->scale_factor, sdl->tile_size * sdl->scale_factor};
			SDL_RenderFillRect(sdl->renderer, &map_tile_rect);
			j++;
		}
		i++;
	}
}

void	clear_color_buf(Uint32 color, t_wolf *sdl)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			sdl->color_buf[WINDOW_WIDTH  * y + x] = color;
			y++;
		}
		x++;
	}
}

void	render_color_buf(t_wolf *sdl)
{
	SDL_UpdateTexture(sdl->color_buf_text, NULL, sdl->color_buf, (int)((Uint32)WINDOW_WIDTH * sizeof(Uint32)));
	SDL_RenderCopy(sdl->renderer, sdl->color_buf_text, NULL, NULL);
}

void	render(t_wolf *sdl, t_player *player, t_ray ray[1280])
{
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);

	generate_3d_projection(sdl, ray, player);

	render_color_buf(sdl);
	clear_color_buf(0xFF000000, sdl);
	render_map(sdl);
	render_rays(sdl, ray, player);
	render_player(sdl, player);
	SDL_RenderPresent(sdl->renderer);
}

void	check_input(int ac, char **av)
{
	int fd;

	if (ac != 2)
	{
		ft_putstr("Wrong input format\n");
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Wrong input format\n");
		exit(1);
	}
}

int		main(int ac, char **av)
{
	t_wolf		sdl[1];
	t_player	player[1];
	t_ray		ray[1280];

	check_input(ac, av);
	sdl->map = read_map(av[1], sdl);
	int	i = 0;
	init_window(sdl);
	setup(sdl, player); 
	while (1)
	{
		process(sdl, player);
		update(sdl, player, ray);
		render(sdl, player, ray);
	}
	destroy_window(sdl);
	return (0);
}