/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:54:15 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/14 15:35:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		minimap_check(t_scene *sc, int x, int y)
{
	int		i;

	if (x < sc->mini.x || x > sc->map.size_x * sc->mini.size + sc->mini.x)
		return (1);
	//if (y < sc->mini.y || y > sc->map.size_y * sc->mini.size + sc->mini.y)
	//	return (1);
	i = 0;
	while (i < sc->mini.nb_tile)
		if (point_in_rect(x, y, &sc->mini.tile[i++].rect))
				return (0);
	return (1);
}

void	minimap_load(t_scene *sc)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			if (sc->map.str[y * sc->map.size_x + x] != ' ')
			{
				if (sc->map.str[y * sc->map.size_x + x] == '0')
					sc->mini.tile[i].color = BLACK;
				if (sc->map.str[y * sc->map.size_x + x] == '1')
					sc->mini.tile[i].color = WHITE;
			 	sc->mini.tile[i].data = sc->map.str[y * sc->map.size_x + x];
				sc->mini.tile[i].rect = rect_init(x * sc->mini.size + sc->mini.x, y * sc->mini.size + sc->mini.y, sc->mini.size, sc->mini.size);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	minimap_plr_draw(t_scene *sc)
{
	t_rect	rect;
	float		posx;
	float		posy;

	posx = sc->plr.x * sc->mini.size + sc->mini.x;
	posy = sc->plr.y * sc->mini.size + sc->mini.y;
	rect = rect_init(posx - 2, posy - 2, 4, 4);
	rect_draw(sc, rect, GREEN, -1);
}

void	minimap_ray_draw(t_scene *sc, t_ray *ray)
{
	int x0,y0,x1,y1;

	x0 = sc->plr.x * sc->mini.size + sc->mini.x;
	y0 = sc->plr.y * sc->mini.size + sc->mini.y;
	x1 = ray->x * sc->mini.size + sc->mini.x;
	y1 = ray->y * sc->mini.size + sc->mini.y;
	line_draw(&sc->view, x0, y0, x1, y1);
}

void	minimap_draw(t_scene *sc)
{
	int		i;

	i = 0;
	while (i < sc->mini.nb_tile)
	{
		rect_draw(sc, sc->mini.tile[i].rect, sc->mini.tile[i].color, GRAY);
		i++;
	}
	minimap_plr_draw(sc);
}
