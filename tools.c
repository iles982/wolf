/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:24:45 by tclarita          #+#    #+#             */
/*   Updated: 2020/04/01 12:25:21 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	normalize_angle(double angle, t_wolf *sdl)
{
	angle = remainder(angle, sdl->two_pi);
	if (angle < 0)
		angle = sdl->two_pi + angle;
	return (angle);
}

float	distance_between(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
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
