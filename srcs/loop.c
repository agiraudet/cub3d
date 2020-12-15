/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 03:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 13:47:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_in(int k, t_keys *keys)
{
	if (k == 'w')
		keys->w = 1;
	if (k == 's')
		keys->s = 1;
	if (k == 'a')
		keys->a = 1;
	if (k == 'd')
		keys->d = 1;
	if (k == 65363)
		keys->ra = 1;
	if (k == 65361)
		keys->la = 1;
	return (1);
}

int		key_out(int k, t_keys *keys)
{
	if (k == 'w')
		keys->w = 0;
	if (k == 's')
		keys->s = 0;
	if (k == 'a')
		keys->a = 0;
	if (k == 'd')
		keys->d = 0;
	if (k == 65363)
		keys->ra = 0;
	if (k == 65361)
		keys->la = 0;
	return (1);
}

void	redraw_view(t_scene *sc)
{
	ray_cast(sc);
	if (sc->set.mini)
		minimap_draw(sc);
	mlx_put_image_to_window(sc->view.mlx, sc->view.win, sc->img_buf.ptr, 0, 0);
}

int		player_move(t_scene *sc)
{
	int	sign;

	if (sc->key.a || sc->key.d)
	{
		sign = (sc->key.a) ? -1 : 1;
		sc->plr.angle += ROT_SPEED * sign;
		sc->plr.cos = cos(deg_to_rad(sc->plr.angle)) * PLR_SPEED;
		sc->plr.sin = sin(deg_to_rad(sc->plr.angle)) * PLR_SPEED;
	}
	if (sc->key.w || sc->key.s)
	{
		sign = (sc->key.w) ? 1 : -1;
		sc->plr.x += sc->plr.cos * sign;
		sc->plr.y += sc->plr.sin * sign;
	}
	if (sc->key.la)
	{
		sc->plr.x -= cos(deg_to_rad(sc->plr.angle + 90)) * PLR_SPEED;
		sc->plr.y -= sin(deg_to_rad(sc->plr.angle + 90)) * PLR_SPEED;
	}
	if (sc->key.ra)
	{
		sc->plr.x += cos(deg_to_rad(sc->plr.angle + 90)) * PLR_SPEED;
		sc->plr.y += sin(deg_to_rad(sc->plr.angle + 90)) * PLR_SPEED;
	}
	if (sc->key.w || sc->key.s || sc->key.a || sc->key.d || sc->key.la || sc->key.ra)
		redraw_view(sc);
	return (1);
}
