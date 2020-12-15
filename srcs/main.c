/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:55 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 10:24:38 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		main(int argc, char **argv)
{
	t_scene *sc;

	if (argc != 2)
		return (0);
	sc = scene_init(argv[1]);
	if (!sc)
		return (1);
	redraw_view(sc);
	mlx_loop(sc->view.mlx);
	return (0);
}
