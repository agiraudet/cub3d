/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 04:12:59 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 01:32:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub.h"

void	map_draw2d(t_scene *sc)
{
	t_view	v;
	int x;
	int y;
	int color;
	t_rect tile;

	v.mlx = sc->mlx;
	v.win = sc->win;
	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			color = (sc->map.str[y * sc->map.size_y + x] == '1') ? WHITE : BLACK;
			tile = rect_init(x * sc->map.size_tile, y * sc->map.size_tile,
				sc->map.size_tile, sc->map.size_tile);
			rect_draw(&v, tile, color, GRAY);
			x++;
		}
		y++;
	}
}

void	player_draw2d(t_scene *sc)
{
	t_view	v;
	t_rect	rect;

	v.mlx = sc->mlx;
	v.win = sc->win;
	rect = rect_init(sc->plr.x - 10, sc->plr.y - 10, 20, 20);
	rect_draw(&v, rect, YELLOW, YELLOW);
	line_draw_ang(&v, point_init(sc->plr.x, sc->plr.y), deg_to_rad(sc->plr.angle + 90), YELLOW, 20);
}

void	ray_draw(t_ray *ray, t_scene *sc)
{
	t_view	v;
	t_point	p1;
	t_point	p2;

	v.mlx = sc->mlx;
	v.win = sc->win;
	p1 = point_init(sc->plr.x, sc->plr.y);
	p2 = point_init(ray->x, ray->y);
	line_draw(&v, p1, p2, GREEN);
}

void	show_sets(t_settings *s)
{
	printf("win_x: %d\nwin_y: %d\nwin_label: %s\ntex_no: %s\ntex_so: %s\ntex_we: %s\ntex_ea: %s\ntex_s: %s\nclf: %u\nclc: %u\n", s->win_x, s->win_y, s->win_label, s->tex_no, s->tex_so, s->tex_we, s->tex_ea, s->tex_s, s->color_f, s->color_c);
}
