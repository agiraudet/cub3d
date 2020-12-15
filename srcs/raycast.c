/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:39:21 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 14:23:02 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ray_cast(t_scene *sc)
{
	t_ray	ray;
	int		ray_count;
	char	hit;
	int		wall_hg;
	int		pos;
	float		inc_ang;

	inc_ang = (float)sc->plr.fov / (float)sc->set.proj.wd;
	ray.angle = sc->plr.angle - (sc->plr.fov / 2);
	ray_count = 0;
	while (ray_count < sc->set.proj.wd)
	{
		ray.x = sc->plr.x;
		ray.y = sc->plr.y;
		ray.cos = cos(deg_to_rad(ray.angle)) / RAY_PREC;
		ray.sin = sin(deg_to_rad(ray.angle)) / RAY_PREC;
		hit = '0';
		while (hit == '0')
		{
			ray.x += ray.cos;
			ray.y += ray.sin;
			pos = ((int)floor(ray.y) * sc->map.size_x + (int)floor(ray.x));
			hit = sc->map.str[pos]; 
		}
		if (sc->set.mini && sc->mini.show_ray && ray_count % 2 == 0)
			minimap_ray_draw(sc, &ray);
		ray.dist = sqrt(pow(sc->plr.x - ray.x, 2) + pow(sc->plr.y - ray.y, 2));
		ray.dist *= cos(deg_to_rad((float)sc->plr.angle - ray.angle));
		wall_hg = floor((float)(sc->set.proj.half_hg) / ray.dist);
		wall_draw(sc, ray_count, wall_hg, &ray);

		ray.angle += inc_ang;
		ray_count++;
	}
}
