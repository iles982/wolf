/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 12:14:25 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/24 18:09:30 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int ac, char **av)
{
	t_wolf		sdl[1];
	t_player	player[1];
	t_ray		ray[1280];
	t_music		music[1];

	check_input(ac, av);
	sdl->map = read_map(av[1], sdl);
	init_window(sdl);
	init_music(music);
	setup(sdl, player);
	while (1)
	{
		process(sdl, player, music);
		update(sdl, player, ray);
		render(sdl, player, ray);
	}
	destroy_window(sdl, music);
	return (0);
}
