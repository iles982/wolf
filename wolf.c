/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 12:14:25 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/23 13:07:41 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    init_window(t_wolf *sdl)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("%s", "Error init_SDL");
    }
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
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
}

void	cast_ray(double ray_angle, int strip_id)
{
	
}

void	cast_all_rays(t_ray ray[1280], t_player *player, t_wolf *sdl)
{
	double	ray_angle;
	int		strip_id;

	strip_id = 0;
	ray_angle = player->rotat_angle - (sdl->fov_angle / 2);
	while (strip_id < sdl->num_rays)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += sdl->fov_angle / sdl->num_rays;
		strip_id++;
	}
}

int		map_has_wall(float y, float x, t_wolf *sdl)
{
	int		map_y;
	int		map_x;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (0);
	map_y = floor(y / sdl->tile_size);
	map_x = floor(x / sdl->tile_size);
	return (sdl->map[map_y][map_x] != 0);
}

void	move_player(t_wolf *sdl, t_player *player, float delta_time)
{
	float move_step;
	float new_player_x;
	float new_player_y;

	player->rotat_angle += player->turn_direction * player->turn_speed * delta_time;
	move_step = player->walk_direction * player->walk_speed;
	new_player_x = player->x + cos(player->rotat_angle) * move_step;
	new_player_y = player->y + sin(player->rotat_angle) * move_step;
	if (!(map_has_wall(new_player_y, new_player_x, sdl)))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void	update(t_wolf *sdl, t_player *player, t_ray ray[1280])
{
	float	delta_time;
	float	frame_time;

	frame_time = 1000 / 30;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), sdl->frame_ticks + frame_time))
		;
	delta_time = (SDL_GetTicks() - sdl->frame_ticks) / 1000.0;
	sdl->frame_ticks = SDL_GetTicks();
	move_player(sdl, player, delta_time);
	cast_all_rays(ray, player, sdl);
}

void	render_player(t_wolf *sdl, t_player *player)
{
	SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255);
	SDL_Rect player_rect = {player->x * sdl->scale_factor, player->y * sdl->scale_factor,
	player->width * sdl->scale_factor, player->height * sdl->scale_factor};
	SDL_RenderFillRect(sdl->renderer, &player_rect);
	SDL_RenderDrawLine(sdl->renderer, player->x * sdl->scale_factor, player->y * sdl->scale_factor,
	sdl->scale_factor * player->x + cos(player->rotat_angle) * 40,
	sdl->scale_factor * player->y + sin(player->rotat_angle) * 40);
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

void	render(t_wolf *sdl, t_player *player)
{
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);

	render_map(sdl);
	// render_rays();
	render_player(sdl, player);
	SDL_RenderPresent(sdl->renderer);
}

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

void	setup(t_wolf *sdl, t_player *player)
{
	sdl->frame_ticks = 0;
	sdl->pi = 3.14159265;
	sdl->two_pi = 6.28318530;
	sdl->tile_size = 64;
	sdl->fov_angle = 60 * (sdl->pi / 180);
	sdl->num_rays = 1280;
	sdl->scale_factor = 1;
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->height = 1;
	player->width = 1;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotat_angle = sdl->pi / 2;
	player->walk_speed = 10;
	player->turn_speed = 2 * 45 * (sdl->pi / 180);

}

int		main(int ac, char **av)
{
	t_wolf		sdl[1];
	t_player	player[1];
	t_ray		ray[1280];

	sdl->map = read_map(av[1], sdl);
	init_window(sdl);
    setup(sdl, player); 
    while (1)
    {
        process(sdl, player);
        update(sdl, player, ray);
        render(sdl, player);
    }
	destroy_window(sdl);
    return (0);
}