/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:55 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 01:08:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_error		g_error;

void	error_set(int type, char *msg)
{
	g_error.flag = 1;
	g_error.type = type;
	g_error.msg = msg;
}

int		error_exit(void)
{
	if (g_error.flag)
	{
		ft_putendl("Error");
		if (g_error.type == 1)
			ft_putstr("Memory allocation failed for: ");
		if (g_error.type == 2)
			ft_putstr("Failed to load file: ");
		if (g_error.type == 3)
			ft_putstr("Bad .cub file: ");
		if (g_error.type == ARG_ERROR)
			ft_putstr("Arguments error: ");
		ft_putendl(g_error.msg);
		return (1);
	}
	else
		return (0);
}

int		arg_parse(int argc, char **argv)
{
	if (argc > 3)
	{
		error_set(ARG_ERROR, "to many argumetns");
		return (0);
	}
	else if (argc < 2)
	{
		error_set(ARG_ERROR, "missing argument");
		return (0);
	}
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
		{
			error_set(ARG_ERROR, "unknow parameter");
			return (0);
		}
		else
			return (2);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_scene *sc;
	t_view	view;
	int		arg_check;

	arg_check = arg_parse(argc, argv);
	if (arg_check == 0)
		return (error_exit());
	sc = scene_init(argv[1], arg_check);
	if (!sc)
		return (error_exit());
	mlx_loop(sc->view.mlx);
	sc->view.win_alive = 0;
	view = sc->view;
	scene_destroy(sc);
	return (0);
}
