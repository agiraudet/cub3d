/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:55 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/20 23:43:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_error		g_error;

void		error_set(int type, char *msg)
{
	g_error.flag = 1;
	g_error.type = type;
	g_error.msg = msg;
}

int			error_exit(void)
{
	if (g_error.flag)
	{
		ft_putendl("Error");
		if (g_error.type == 1)
			ft_putstr("Memory allocation failed for: ");
		if (g_error.type == 2)
			ft_putstr("Failed to load file: ");
		ft_putendl(g_error.msg);
		return (1);
	}
	else
		return (0);
}

int		main(int argc, char **argv)
{
	t_scene *sc;

	if (argc != 2)
		return (0);
	sc = scene_init(argv[1]);
	if (!sc)
		return (error_exit());
	mlx_loop(sc->view.mlx);
	return (0);
}
