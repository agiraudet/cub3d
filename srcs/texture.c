/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:53:26 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 12:35:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		tex_load(t_scene *sc, int tex_nb, char *path)
{
	t_tex	tex;

	tex.ptr = mlx_xpm_file_to_image(sc->view.mlx, path, &tex.wd, &tex.hg);
	if (!tex.ptr)
		return (0);
	tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_len, &tex.endian);
	if (!tex.data)
	{
		free(tex.ptr);
		return (0);
	}
	sc->texs[tex_nb] = tex;
	return (1);
}

int		tex_get_color(t_tex *tex, int x, int y)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	int	div;

	div = tex->bpp / 4;
	b = tex->data[tex->line_len * y + tex->bpp / div * x];
	g = tex->data[tex->line_len * y + tex->bpp / div * x + 1];
	r = tex->data[tex->line_len * y + tex->bpp / div * x + 2];
	a = tex->data[tex->line_len * y + tex->bpp / div * x + 3];
	return (rgb_to_i(a, r, g, b));
}

int tex_draw(t_scene *sc, int tex_id, int x1, int y1)
{
	t_tex	*tex;
	int color;
	int x;
	int y;

	tex = &sc->texs[tex_id];
	y = 0;
	while (y < tex->hg)
	{
		x = 0;
		while (x < tex->wd)
		{
			color = tex_get_color(tex, x, y);
			mlx_pixel_put(sc->view.mlx, sc->view.win, x + x1, y + y1, color);
			x++;
		}
		y++;
	}
	return (0);
}
