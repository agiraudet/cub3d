/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:31:09 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 13:40:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	line_ver_draw(t_scene *sc, int x, int y, int y2, int color)
{
	while (y <= y2)
	{
		if (minimap_check(sc, x, y))
			if (y >= 0 && y <= sc->set.proj.hg && x >= 0 && x <= sc->set.proj.wd)
				mlx_pixel_put(sc->view.mlx, sc->view.win, x, y, color);
		y++;
	}
}

void	line_ver_draw_buffer(t_scene *sc, int x, int y, int y2, int color)
{

	while (y <= y2)
	{
		if (y >= 0 && y <= sc->set.proj.hg && x >= 0 && x <= sc->set.proj.wd)
			pixel_put_buffer(sc, x, y, color);
		y++;
	}
}


void	line_tex_draw(t_scene *sc, int tex_id, t_ray *ray, int x, int wall_hg)
{
	t_tex	*tex;
	int		tex_x;
	int		y;
	float	i;
	float	i_inc;
	int		color;
	
	tex = &sc->texs[tex_id];
	tex_x = (int)floor((int)floor(tex->wd * (ray->x + ray->y)) % tex->wd);
	i_inc = (float)tex->hg / (float)(wall_hg * 2);
	y = sc->set.proj.half_hg - wall_hg;
	i = 0;
	while (y < sc->set.proj.half_hg + wall_hg )
	{
		color = tex_get_color(tex, tex_x, ceil(i));
		mlx_pixel_put(sc->view.mlx, sc->view.win, x, y, color);
		i += i_inc;
		if (ceil(i) >= tex->hg)
			i = tex->hg - 1;
		y++;
	}
}

void	line_tex_draw_buffer(t_scene *sc, int tex_id, t_ray *ray, int x, int wall_hg)
{
	t_tex	*tex;
	int		tex_x;
	int		y;
	float	i;
	float	i_inc;
	int		color;
	
	tex = &sc->texs[tex_id];
	tex_x = (int)floor((int)floor(tex->wd * (ray->x + ray->y)) % tex->wd);
	i_inc = (float)tex->hg / (float)(wall_hg * 2);
	y = sc->set.proj.half_hg - wall_hg;
	i = 0;
	while (y < sc->set.proj.half_hg + wall_hg )
	{
		color = tex_get_color(tex, tex_x, ceil(i));
		pixel_put_buffer(sc, x, y, color);
		i += i_inc;
		if (ceil(i) >= tex->hg)
			i = tex->hg - 1;
		y++;
	}
}
void	wall_draw(t_scene *sc, int ray_count, int wall_hg, t_ray *ray)
{
	line_ver_draw_buffer(sc, ray_count, 0, sc->set.proj.half_hg - wall_hg, sc->set.color_c);	
	line_tex_draw_buffer(sc, TEX_NO, ray, ray_count, wall_hg);
	//line_ver_draw(sc, ray_count, sc->set.proj.half_hg - wall_hg, sc->set.proj.half_hg + wall_hg, RED);
	//line_ver_draw(sc, ray_count, sc->set.proj.half_hg + wall_hg, sc->set.proj.hg, sc->set.color_f);
	line_ver_draw_buffer(sc, ray_count, sc->set.proj.half_hg + wall_hg, sc->set.proj.hg, sc->set.color_f);
}
