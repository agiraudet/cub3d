/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 02:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/17 20:57:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float			deg_to_rad(int angle)
{
	return (angle * M_PI / 180);
}

unsigned int	rgb_to_i(int a, int r, int g, int b)
{
	unsigned int res;

	res = 0;
	res += b;
	res += g * 256;
	res += r * 65536;
	res += a * 16777216;
	return (res);
}

void			i_to_rgb(unsigned int color, int *rgba)
{
	rgba[0] = color >> 24;
	rgba[1] = (color >> 16) & 255;
	rgba[2] = (color >> 8) & 255;
	rgba[3] = color & 255;
}

int				fix_angle(float a)
{
	if (a > 359)
		return (a - 360);
	if (a < 0)
		return (a + 360);
	return (a);
}

t_rect			rect_init(int x, int y, int wd, int hg)
{
	t_rect rect;

	rect.x = x;
	rect.y = y;
	rect.wd = wd;
	rect.hg = hg;
	return (rect);
}

void			rect_draw
	(t_scene *sc, t_rect rect, unsigned int color, int outline)
{
	int				x;
	int				y;
	unsigned int	draw_color;

	x = 0;
	y = 0;
	while (y < rect.hg)
	{
		x = 0;
		while (x < rect.wd)
		{
			if ((outline != -1) &&
					(x == 0 || y == 0 || y == rect.hg - 1 || x == rect.wd - 1))
				draw_color = outline;
			else
				draw_color = color;
			pixel_put_buffer(sc, rect.x + x, rect.y + y, draw_color);
			x++;
		}
		y++;
	}
}

void			pixel_write(t_tex *buf, int *rgba, int x, int y)
{
	int		div;
	int		offset;

	div = buf->bpp / 4;
	offset = rgba[4];
	buf->data
		[offset + (buf->bpp / div * x) + (buf->line_len * y) + 0] = rgba[3];
	buf->data
		[offset + (buf->bpp / div * x) + (buf->line_len * y) + 1] = rgba[2];
	buf->data
		[offset + (buf->bpp / div * x) + (buf->line_len * y) + 2] = rgba[1];
	buf->data
		[offset + (buf->bpp / div * x) + (buf->line_len * y) + 3] = rgba[0];
}

void			pixel_put_buffer(t_scene *sc, int x, int y, unsigned int color)
{
	t_tex	*buf;
	int		rgba[5];
	int		scx;
	int		scy;

	if (x < 0 || x > sc->set.proj.wd || y < 0 || y > sc->set.proj.hg)
		return ;
	buf = &sc->img_buf;
	rgba[4] = (buf->line_len * y + buf->bpp / (buf->bpp / 4) * x) * PROJ_SCALE;
	i_to_rgb(color, rgba);
	scy = 0;
	while (scy < PROJ_SCALE)
	{
		scx = 0;
		while (scx < PROJ_SCALE)
		{
			pixel_write(buf, rgba, scx, scy);
			scx++;
		}
		scy++;
	}
}
