/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 23:17:19 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/16 18:18:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ceil_render(t_scene *sc, int x, t_ray *ray)
{
	int y;

	y = 0;
	while (y < ray->draw_start)
		pixel_put_buffer(sc, x, y++, sc->set.color_c);
}

void	skybox_render(t_scene *sc, int x, t_ray *ray)
{
	int		offset;
	double	angle;
	int		tex_x;
	double	tex_y;
	int		y;

	angle = atan2(ray->dir_y, ray->dir_x);
	offset = fix_angle(angle * 180 / M_PI);
	tex_y = (double)sc->texs[TEX_BG].hg / (double)sc->set.proj.half_hg;
	y = 0;
	while (y < ray->draw_start)
	{
		tex_x = sc->texs[TEX_BG].wd / 360 * offset;
		pixel_put_buffer(sc, x, y,
				tex_get_color(&sc->texs[TEX_BG], tex_x, y * tex_y));
		y++;
	}
}

void	floor_render(t_scene *sc, int x, t_ray *ray)
{
	int y;

	y = ray->draw_end;
	while (y < sc->set.proj.hg)
		pixel_put_buffer(sc, x, y++, sc->set.color_f);
}

void	ground_next_stripe(t_floor *floor)
{
	floor->cell_x = (int)(floor->x);
	floor->cell_y = (int)(floor->y);
	floor->tex_x = (int)(floor->tex->wd *
			(floor->x - floor->cell_x)) & (floor->tex->wd - 1);
	floor->tex_y = (int)(floor->tex->hg *
			(floor->y - floor->cell_y)) & (floor->tex->hg - 1);
	floor->x += floor->step_x;
	floor->y += floor->step_y;
}

void	ground_set_stripe(t_scene *sc, t_floor *floor, int y)
{
	floor->ray_dir_x0 = sc->plr.dir_x - sc->plr.plan_x;
	floor->ray_dir_y0 = sc->plr.dir_y - sc->plr.plan_y;
	floor->ray_dir_x1 = sc->plr.dir_x + sc->plr.plan_x;
	floor->ray_dir_y1 = sc->plr.dir_y + sc->plr.plan_y;
	floor->p = y - sc->set.proj.half_hg;
	floor->pos_z = 0.5 * sc->set.proj.hg;
	floor->row_dist = floor->pos_z / floor->p;
	floor->step_x = floor->row_dist *
		(floor->ray_dir_x1 - floor->ray_dir_x0) / sc->set.proj.wd;
	floor->step_y = floor->row_dist *
		(floor->ray_dir_y1 - floor->ray_dir_y0) / sc->set.proj.wd;
	floor->x = sc->plr.pos_x + floor->row_dist * floor->ray_dir_x0;
	floor->y = sc->plr.pos_y + floor->row_dist * floor->ray_dir_y0;
}

void	ground_render(t_scene *sc)
{
	t_floor	floor;
	int		x;
	int		y;

	floor.tex = &sc->texs[TEX_F];
	y = sc->set.proj.half_hg;
	while (y < sc->set.proj.hg)
	{
		ground_set_stripe(sc, &floor, y);
		x = 0;
		while (x < sc->set.proj.wd)
		{
			ground_next_stripe(&floor);
			pixel_put_buffer(sc, x, y,
					tex_get_color(floor.tex, floor.tex_x, floor.tex_y));
			x++;
		}
		y++;
	}
}

int		strip_get_tex_x(t_scene *sc, t_tex *tex, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0 || ray->side == 1)
		wall_x = sc->plr.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = sc->plr.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)tex->wd);
	if ((ray->side == 0 || ray->side == 1) && ray->dir_x > 0)
		tex_x = tex->wd - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->dir_y < 0)
		tex_x = tex->wd - tex_x - 1;
	return (tex_x);
}

void	strip_render(t_scene *sc, int x, t_ray *ray)
{
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	t_tex	*tex;

	tex = &sc->texs[ray->side];
	tex_x = strip_get_tex_x(sc, tex, ray);
	step = 1.0 * tex->hg / ray->line_hg;
	tex_pos = (ray->draw_start - sc->set.proj.half_hg
			+ ray->line_hg / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->hg - 1);
		tex_pos += step;
		pixel_put_buffer(sc, x, ray->draw_start++,
				tex_get_color(tex, tex_x, tex_y));
	}
}

void	ray_draw(t_scene *sc, t_ray *ray, int x)
{
	ray->draw_start = -ray->line_hg / 2 + sc->set.proj.hg / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_hg / 2 + sc->set.proj.hg / 2;
	if (ray->draw_end >= sc->set.proj.hg)
		ray->draw_end = sc->set.proj.hg;
	if (BONUS)
		skybox_render(sc, x, ray);
	else
		ceil_render(sc, x, ray);
	strip_render(sc, x, ray);
	if (!BONUS)
		floor_render(sc, x, ray);
}
