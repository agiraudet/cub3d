/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:31:06 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 01:41:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ray_ver_init(t_ray *ray, t_scene *sc, float ang)
{
	float	a_tan;

	ray->angle = deg_to_rad(ang);
	ray->dof = 0;
	a_tan = tan(ray->angle);
	if (cos(ray->angle) > 0.0001)
	{
		ray->x = (((int)sc->plr.x / sc->map.size_tile) * sc->map.size_tile) + sc->map.size_tile;
		ray->y = (sc->plr.x - ray-> x) * a_tan + sc->plr.y;
		ray->xoff = sc->map.size_tile;
		ray->yoff = -(ray->xoff) * a_tan;
	}
	else if (cos(ray->angle) < -0.0001)
	{
		ray->x = (((int)sc->plr.x / sc->map.size_tile) * sc->map.size_tile) - 0.0001;
		ray->y = (sc->plr.x - ray-> x) * a_tan + sc->plr.y;
		ray->xoff = -sc->map.size_tile;
		ray->yoff = -(ray->xoff) * a_tan;
	}
	else
	{
		ray->x = sc->plr.x;
		ray->y = sc->plr.y;
		ray->dof = MAX_DOF;
	}
}

void	ray_hor_init(t_ray *ray, t_scene *sc, float ang)
{
	float	a_tan;

	ray->angle = deg_to_rad(ang);
	ray->dof = 0;
	a_tan = 1.0 / tan(ray->angle);
	if (sin(ray->angle) > 0.0001)
	{
		ray->y = (((int)sc->plr.y / sc->map.size_tile) * sc->map.size_tile) - 0.0001;
		ray->x = (sc->plr.y - ray->y) * a_tan + sc->plr.x;
		ray->yoff = -sc->map.size_tile;
		ray->xoff = -(ray->yoff) * a_tan;
	}
	else if (sin(ray->angle) < -0.0001)
	{
		ray->y = (((int)sc->plr.y / sc->map.size_tile) * sc->map.size_tile) + sc->map.size_tile;
		ray->x = (sc->plr.y - ray->y) * a_tan + sc->plr.x;
		ray->yoff = sc->map.size_tile;
		ray->xoff = -(ray->yoff) * a_tan;
	}
	else
	{
		ray->x = sc->plr.x;
		ray->y = sc->plr.y;
		ray->dof = MAX_DOF;
	}
}

float	ray_dist(t_ray *ray, t_scene *sc)
{
	float	dist;

	dist = cos(ray->angle) * (ray->x - sc->plr.x) - sin(ray->angle) * (ray->y - sc->plr.y);
	return (dist);
}

void	ray_hit(t_ray *ray, t_scene *sc)
{
	int		hit_x;
	int		hit_y;
	int		hit_pos;

	while (ray->dof < MAX_DOF)
	{
		hit_x = (int)(ray->x) / sc->map.size_tile;
		hit_y = (int)(ray->y) / sc->map.size_tile;
		hit_pos = hit_y * sc->map.size_x + hit_x;
		if (hit_pos > 0 && hit_pos < sc->map.size_x * sc->map.size_y && sc->map.str[hit_pos] == '1')
			ray->dof = MAX_DOF;
		else
		{
			ray->x += ray->xoff;
			ray->y += ray->yoff;
			ray->dof += 1;
		}
	}
}

float	ray_single_cast(t_scene *sc, float ang, char *dir)
{
	t_ray	ray_h;
	t_ray	ray_v;
	float	dist_h;
	float	dist_v;

	ray_hor_init(&ray_h, sc, ang);
	ray_ver_init(&ray_v, sc, ang);
	ray_hit(&ray_h, sc);
	ray_hit(&ray_v, sc);
	dist_h = ray_dist(&ray_h, sc);
	dist_v = ray_dist(&ray_v, sc);
	if ((dist_h < dist_v || dist_v == 0) && dist_h != 0)
	{
		ray_draw(&ray_h, sc);
		*dir = 'h';
		return (dist_h);
	}
	else
	{
		ray_draw(&ray_v, sc);
		*dir = 'v';
		return (dist_v);
	}
}

void	ray_cast(t_scene *sc)
{
	int		i;
	float	ang;
	float	dist;
	char	dir;

	dir = 0;
	i = 0;
	ang = fix_angle(sc->plr.angle - (NB_RAY / 2) * RAY_OFFSET);
	while (i < NB_RAY)
	{
		dist = ray_single_cast(sc, ang, &dir);
		wall_draw(sc, i, dist, ang, dir);
		i++;
		ang += RAY_OFFSET;
	}
}

	
