/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:05:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 01:33:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		main(int argc, char **argv)
{
	t_scene		*sc;

	if (argc == 2)
		sc = scene_init(argv[1]);
	else
		sc = scene_init(0);
	view_redraw(sc);
	mlx_loop(sc->mlx);
	scene_destroy(sc);
	return (0);
}
