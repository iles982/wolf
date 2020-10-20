/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 12:14:25 by tclarita          #+#    #+#             */
/*   Updated: 2020/10/20 10:29:35 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int ac, char **av)
{
	t_wolf		sdl[1];
	t_player	player[1];
	t_ray		ray[1280];

	check_input(ac, av);
	sdl->map = read_map(av[1], sdl);
	init_window(sdl);
	setup(sdl, player);
	int i = 1;
	while (i)
	{
		process(sdl, player);
		update(sdl, player, ray);
		render(sdl, player, ray);
		if (wait(3))
			i = 0;
	}
	destroy_window(sdl);
	return (0);
}
