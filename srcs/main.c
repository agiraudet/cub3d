/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:05:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 01:49:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		main()
{
	t_scene		*sc;

	sc = scene_init();
	view_redraw(sc);
	mlx_loop(sc->mlx);
	scene_destroy(sc);
	return (0);
}
