/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 02:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 13:44:46 by agiraude         ###   ########.fr       */
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

void			i_to_rgb(int color, int *rgba)
{
	rgba[0] = color >> 24;
	rgba[1] = (color >> 16)  & 255;
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

t_rect	rect_init(int x, int y, int wd, int hg)
{
	t_rect rect;

	rect.x = x;
	rect.y = y;
	rect.wd = wd;
	rect.hg = hg;
	return (rect);
}

void	rect_draw(t_scene *sc, t_rect rect, int color, int outline)
{
	int	x;
	int	y;
	int	draw_color;

	x = 0;
	y = 0;
	while (y < rect.hg)
	{
		x = 0;
		while (x < rect.wd)
		{
			if ((outline != -1) && (x == 0 || y == 0 || y == rect.hg - 1 || x == rect.wd - 1))
				draw_color = outline;
			else
				draw_color = color;
			pixel_put_buffer(sc, x, y, draw_color);
			x++;
		}
		y++;
	}
}

void	line_draw(t_view *v, int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;){  /* loop */
	mlx_pixel_put(v->mlx, v->win, x0, y0, RED);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void	line_ang_draw(t_view *v, int x, int y, float angle, int len)
{
	int	x1, y1;

	x1 = x + len * sin(angle);
	y1 = y + len * cos(angle);
	mlx_pixel_put(v->mlx, v->win, x, y, RED);
	mlx_pixel_put(v->mlx, v->win, x1, y1, RED);
	line_draw(v, x, y, x1, y1);
}

int		point_in_rect(int x, int y, t_rect *rect)
{
	if (x >= rect->x && x <= rect->x + rect->wd)
		if (y >= rect->y && y <= rect->y + rect->wd)
			return (1);
	return (0);
}

void	pixel_put_buffer(t_scene *sc, int x, int y, int color)
{
	t_tex	*buf;
	int		rgba[4];
	int		div;

	if (x < 0 || x > sc->set.proj.wd || y < 0 || y > sc->set.proj.hg)
		return ;
	buf = &sc->img_buf;
	div = buf->bpp / 4;
	i_to_rgb(color, rgba);
	buf->data[buf->line_len * y + buf->bpp / div * x] = rgba[3];
	buf->data[buf->line_len * y + buf->bpp / div * x + 1] = rgba[2];
	buf->data[buf->line_len * y + buf->bpp / div * x + 2] = rgba[1];
	buf->data[buf->line_len * y + buf->bpp / div * x + 3] = rgba[0];
}
