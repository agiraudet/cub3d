/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:53:26 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/17 19:29:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				tex_load(t_scene *sc, int tex_nb, char *path)
{
	t_tex	tex;

	tex.ptr = mlx_xpm_file_to_image(sc->view.mlx, path, &tex.wd, &tex.hg);
	if (!tex.ptr)
	{
		error_set(2, path);
		return (0);
	}
	tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_len, &tex.endian);
	if (!tex.data)
	{
		error_set(2, path);
		free(tex.ptr);
		return (0);
	}
	sc->texs[tex_nb] = tex;
	return (1);
}

unsigned int	tex_get_color(t_tex *tex, int x, int y)
{
	int r;
	int g;
	int b;
	int a;
	int	div;

	div = tex->bpp / 4;
	if (div <= 0)
		div = 1;
	b = tex->data[tex->line_len * y + tex->bpp / div * x];
	g = tex->data[tex->line_len * y + tex->bpp / div * x + 1];
	r = tex->data[tex->line_len * y + tex->bpp / div * x + 2];
	a = tex->data[tex->line_len * y + tex->bpp / div * x + 3];
	return (rgb_to_i(a, r, g, b));
}

void			tex_put(t_scene *sc, t_tex *tex, int x, int y)
{
	int				y1;
	int				x1;
	unsigned int	color;

	y1 = 0;
	while (y1 < tex->hg)
	{
		x1 = 0;
		while (x1 < tex->wd)
		{
			color = tex_get_color(tex, x1, y1);
			if (color != 4278190080)
				pixel_put_buffer(sc, x + x1, y + y1, color);
			x1++;
		}
		y1++;
	}
}
