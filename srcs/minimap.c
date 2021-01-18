/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:20:56 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 01:17:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	minimap_get_color(t_scene *sc, int x, int y)
{
	unsigned int	color;

	if (ft_strchr("0NEWS", sc->map.str[y * sc->map.size_x + x]))
		color = LIGHT_GRAY;
	else if (sc->map.str[y * sc->map.size_x + x] == '1')
		color = 0;
	else if (sc->map.str[y * sc->map.size_x + x] == '2')
		color = GREEN;
	else
		color = 0;
	return (color);
}

void			minimap_draw(t_scene *sc)
{
	t_rect			tile;
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			if ((color = minimap_get_color(sc, x, y)))
			{
				tile = rect_init(x * sc->mini.size + sc->mini.x,
				y * sc->mini.size + sc->mini.y, sc->mini.size, sc->mini.size);
				rect_draw(sc, tile, color, -1);
			}
			x++;
		}
		y++;
	}
	tile = rect_init(sc->plr.pos_x * sc->mini.size + sc->mini.x - 2,
	sc->plr.pos_y * sc->mini.size + sc->mini.y - 2, 4, 4);
	rect_draw(sc, tile, YELLOW, -1);
}

t_tex		*tex_load2(t_view *view, char *path)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
	{
		error_set(1, "tex");
		return (0);
	}
	tex->ptr = mlx_xpm_file_to_image(view->mlx, path, &tex->wd, &tex->hg);
	if (!tex->ptr)
	{
		free(tex);
		error_set(2, path);
		return (0);
	}
	tex->data = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->data)
	{
		error_set(2, path);
		free(tex->ptr);
		free(tex);
		return (0);
	}
	return (tex);
}

void		anim_next_frame(t_scene *sc)
{
	if (sc->anim.speed >= ANIM_SPEED)
	{
		sc->anim.speed = 0;
		if (sc->anim.frame == TEX_S1)
			sc->anim.frame = TEX_S2;
		else
			sc->anim.frame = TEX_S1;
	}
	else
		sc->anim.speed += 1;
}
