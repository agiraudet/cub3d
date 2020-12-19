/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 03:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/19 23:16:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_in(int k, t_keys *keys)
{
	if (k == K_UP)
		keys->up = 1;
	if (k == K_DOWN)
		keys->down = 1;
	if (k == K_ROT_L)
		keys->rotl = 1;
	if (k == K_ROT_R)
		keys->rotr = 1;
	if (k == K_STRAF_R)
		keys->strafr = 1;
	if (k == K_STRAF_L)
		keys->strafl = 1;
	return (1);
}

int		key_out(int k, t_keys *keys)
{
	if (k == K_UP)
		keys->up = 0;
	if (k == K_DOWN)
		keys->down = 0;
	if (k == K_ROT_L)
		keys->rotl = 0;
	if (k == K_ROT_R)
		keys->rotr = 0;
	if (k == K_STRAF_R)
		keys->strafr = 0;
	if (k == K_STRAF_L)
		keys->strafl = 0;
	return (1);
}

void	redraw_view(t_scene *sc)
{
	raycast(sc);
	if (sc->mini.show)
		minimap_draw(sc);
	mlx_put_image_to_window(sc->view.mlx, sc->view.win, sc->img_buf.ptr, 0, 0);
}

void	player_go(t_scene *sc, int dir)
{
	float	new_x;
	float	new_y;

	new_x = sc->plr.pos_x + sc->plr.dir_x * dir * PLR_SPEED;
	new_y = sc->plr.pos_y + sc->plr.dir_y * dir * PLR_SPEED;
	if (1)
	{
		sc->plr.pos_x = new_x;
		sc->plr.pos_y = new_y;
	}
}

void	player_rot(t_scene *sc, int dir)
{
		double	old_dir = sc->plr.dir_x;
		sc->plr.dir_x = sc->plr.dir_x * cos(dir * ROT_SPEED) - sc->plr.dir_y * sin(dir * ROT_SPEED);
		sc->plr.dir_y = old_dir * sin(dir * ROT_SPEED) + sc->plr.dir_y * cos(dir * ROT_SPEED);
		double	old_plane_x = sc->plr.plan_x;
		sc->plr.plan_x = sc->plr.plan_x * cos(dir * ROT_SPEED) - sc->plr.plan_y * sin(dir * ROT_SPEED);
		sc->plr.plan_y = old_plane_x * sin(dir * ROT_SPEED) + sc->plr.plan_y * cos(dir * ROT_SPEED);
}

int		player_move(t_scene *sc)
{
	if (sc->key.rotl)
		player_rot(sc, LEFT);
	if (sc->key.rotr)
		player_rot(sc, RIGHT);
	if (sc->key.up)
		player_go(sc, UP);
	if (sc->key.down)
		player_go(sc, DOWN);
	redraw_view(sc);
	return (1);
}
