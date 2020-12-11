/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:03:29 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 11:06:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	clean_view(t_scene *sc)
{
	t_rect	ceil;
	t_rect	floor;
	t_view	v;

	v.mlx = sc->mlx;
	v.win = sc->win;
	ceil = rect_init(0, 0, sc->set.win_x, sc->set.win_y / 2);
	floor = rect_init(0, sc->set.win_y / 2, sc->set.win_x, sc->set.win_y);
	rect_draw(&v, ceil, sc->set.color_c, -1);
	rect_draw(&v, floor, sc->set.color_f, -1);
}

t_rect		wall_init(t_scene *sc, int i, float dist)
{
	t_rect	wall;
	int		wall_hg;
	int		wall_off;
	int		res;

	res = (sc->set.win_x / NB_RAY);
	wall_hg = (sc->map.size_tile * sc->set.win_y) / dist;
	if (wall_hg > sc->set.win_y)
		wall_hg = sc->set.win_y;
	wall_off = sc->set.win_y / 2 - wall_hg / 2;
	wall = rect_init(i * res, wall_off, res, wall_hg);
	return (wall);
}

void	wall_draw(t_scene *sc, int i, float dist, float ang, char dir)
{
	t_rect	wall;
	t_view	v;
	int		fish_eye;

	v.mlx = sc->mlx;
	v.win = sc->win;
	fish_eye = fix_angle(sc->plr.angle - ang);
	dist *= cos(deg_to_rad(fish_eye));
	wall = wall_init(sc, i, dist);
	if (dir == 'v')
		rect_draw(&v, wall, RED, -1);
	else
		rect_draw(&v, wall, DARK_RED, -1);
}
