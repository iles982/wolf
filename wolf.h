/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 12:14:40 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/23 13:07:26 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_F
# define WOLF_F
# include <unistd.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 832

typedef struct		s_wolf
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Rect		rect;
	int				**map;
	double			pi;
	double			two_pi;
	double			fov_angle;
	double			scale_factor;
	int				num_rays;
	int				tile_size;
	int				map_num_row;
	int				map_num_col;
	int				frame_ticks;
}					t_wolf;

typedef struct		s_player
{
	double			x;
	double			y;
	double			width;
	double			height;
	int				turn_direction;
	int				walk_direction;
	double			rotat_angle;
	double			walk_speed;
	double			turn_speed;
}					t_player;

typedef struct		s_ray
{
	double			ray_angle;
	double			wall_hit_x;
	double			wall_hit_y;
	double			distance;
	int				was_hit_vertical;
	int				ray_face_up;
	int				ray_face_down;
	int				ray_face_left;
	int				ray_face_right;
	int				wall_hit;
}					t_ray;

int			**read_map(char	*file, t_wolf *sdl);

#endif