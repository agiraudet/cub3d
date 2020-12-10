/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 03:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 02:35:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		keys_in(int k, t_keys *keys)
{
	if (k == 'w')
		keys->w = 1;
	if (k == 's')
		keys->s = 1;
	if (k == 'a')
		keys->a = 1;
	if (k == 'd')
		keys->d = 1;
	return (1);
}

int		keys_out(int k, t_keys *keys)
{
	if (k == 'w')
		keys->w = 0;
	if (k == 's')
		keys->s = 0;
	if (k == 'a')
		keys->a = 0;
	if (k == 'd')
		keys->d = 0;
	return (1);
}

void	view_redraw(t_scene *sc)
{
	map_draw2d(sc);
	player_draw2d(sc);
	clean_view(sc);
}

int		player_move(t_scene *sc)
{
	int	sign;

	ray_cast(sc);
	if (sc->key.w || sc->key.s)
	{
		sign = (sc->key.w) ? 1 : -1;
		sc->plr.x += sc->plr.dx * sign;
		sc->plr.y += sc->plr.dy * sign;
		//sc->key.w = 0;
		//sc->key.s = 0;
		view_redraw(sc);
	}
	if (sc->key.a || sc->key.d)
	{
		sign = (sc->key.a) ? 1 : -1;
		sc->plr.angle = fix_angle(sc->plr.angle + ROT_SPEED * sign);
		sc->plr.dx = cos(deg_to_rad(sc->plr.angle)) * ROT_MUL;
		sc->plr.dy = -sin(deg_to_rad(sc->plr.angle)) * ROT_MUL;
		//sc->key.a = 0;
		//sc->key.d = 0;
		view_redraw(sc);
	}
	return (1);
}
