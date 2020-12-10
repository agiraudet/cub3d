/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 02:55:16 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/09 22:23:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_utils.h"

t_point	point_init(float x, float y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_rect	rect_init(float x, float y, float wd, float hg)
{
	t_rect rect;

	rect.x = x;
	rect.y = y;
	rect.wd = wd;
	rect.hg = hg;
	return (rect);
}

void	rect_draw(t_view *v, t_rect rect, int color, int outline)
{
	float	x;
	float	y;
	int		draw_color;

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
			mlx_pixel_put(v->mlx, v->win, x + rect.x, y + rect.y, draw_color);
			x++;
		}
		y++;
	}
}

void	line_draw(t_view *v, t_point p1, t_point p2, int color)
{
	int dx;
	int dy;
	int x;
	int y;
	int err;

	dx = fabs(p2.x - p1.x);
	dy = fabs(p2.y - p1.y);
	x = p1.x;
	y = p1.y;
	if (dx > dy)
	{
		err = dx / 2.0;
		while (x != p2.x)
		{
			mlx_pixel_put(v->mlx, v->win, x, y, color);
			err -= dy;
			if (err < 0)
			{
				y = (p1.y > p2.y) ? y - 1 : y + 1;
				err += dx;
			}
			x = (p1.x > p2.x) ? x - 1 : x + 1;
		}
	}
	else
	{
		err = dy / 2.0;
		while (y != p2.y)
		{
			mlx_pixel_put(v->mlx, v->win, x, y, color);
			err -= dx;
			if (err < 0)
			{
				x = (p1.x > p2.x) ? x - 1 : x + 1;
				err += dy;
			}
			y = (p1.y > p2.y) ? y - 1 : y + 1;
		}
	}
	mlx_pixel_put(v->mlx, v->win, x, y, color);
}

void	line_draw_ang(t_view *v, t_point p1, float angle, int color, int len)
{
	t_point	p2;

	p2.x = p1.x + len * sin(angle);
	p2.y = p1.y + len * cos(angle);
	mlx_pixel_put(v->mlx, v->win, p1.x, p1.y, RED);
	mlx_pixel_put(v->mlx, v->win, p2.x, p2.y, RED);
	line_draw(v, p1, p2, color);
}
