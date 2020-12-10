/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:03:29 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 01:42:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	clean_view(t_scene *sc)
{
	t_rect	clean;
	t_view	v;

	v.mlx = sc->mlx;
	v.win = sc->win;
	clean = rect_init(sc->set.win_x / 2, 0, sc->set.win_x / 2, sc->set.win_x);
	rect_draw(&v, clean, BLACK, -1);
}

void	wall_draw(t_scene *sc, int i, float dist, float ang, char dir)
{
	t_rect	wall;
	t_view	v;
	int		wall_hg;
	int		wall_off;
	int		fish_eye;

	v.mlx = sc->mlx;
	v.win = sc->win;
	fish_eye = fix_angle(sc->plr.angle - ang);
	dist *= cos(deg_to_rad(fish_eye));
	wall_hg = (sc->map.size_tile * 420) / dist;
	if (wall_hg > 420)
		wall_hg = 420;
	wall_off = sc->set.win_y / 2 - (wall_hg>>1);

	wall = rect_init(i * 8 + sc->set.win_y, wall_off, 8, wall_hg);
	if (dir == 'v')
		rect_draw(&v, wall, RED, -1);
	else
		rect_draw(&v, wall, DARK_RED, -1);
}
