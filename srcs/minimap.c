/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:20:56 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/21 13:32:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	minimap_draw(t_scene *sc)
{
	t_rect	tile;
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			color = 0;
			if (ft_strchr("02NEWS", sc->map.str[y * sc->map.size_x + x]))
				color = LIGHT_GRAY;
			else if (sc->map.str[y * sc->map.size_x + x] == '1')
				color = 0;
			if (color)
			{
				tile = rect_init(x * sc->mini.size + sc->mini.x, y * sc->mini.size + sc->mini.y, sc->mini.size, sc->mini.size);
				rect_draw(sc, tile, color, -1);
			}
			x++;
		}
		y++;
	}
	tile = rect_init(sc->plr.pos_x * sc->mini.size + sc->mini.x - 2, sc->plr.pos_y * sc->mini.size + sc->mini.y - 2, 4, 4);
	rect_draw(sc, tile, YELLOW, -1);
}
