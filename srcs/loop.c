/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 03:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 00:58:09 by agiraude         ###   ########.fr       */
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
	if (k == K_ESC)
		keys->esc = 1;
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
	spt_draw(sc);
	if (BONUS)
	{
		if (sc->mini.show)
			minimap_draw(sc);
		anim_next_frame(sc);
	}
	mlx_put_image_to_window(sc->view.mlx, sc->view.win, sc->img_buf.ptr, 0, 0);
	if (sc->set.prnt_scr)
	{
		sc->set.prnt_scr = 0;
		bmp_to_file(&sc->img_buf, "prnt.bmp");
	}
}

void	player_go(t_scene *sc, int dir)
{
	float	new_x;
	float	new_y;

	new_x = sc->plr.pos_x + sc->plr.dir_x * dir * PLR_SPEED;
	new_y = sc->plr.pos_y + sc->plr.dir_y * dir * PLR_SPEED;
	if (sc->map.str[(int)new_y * sc->map.size_x + (int)new_x] != '1')
	{
		sc->plr.pos_x = new_x;
		sc->plr.pos_y = new_y;
	}
}

void	player_rot(t_scene *sc, int dir)
{
	double old_dir;
	double old_plane_x;

	old_dir = sc->plr.dir_x;
	sc->plr.dir_x = sc->plr.dir_x * cos(dir * ROT_SPEED)
		- sc->plr.dir_y * sin(dir * ROT_SPEED);
	sc->plr.dir_y = old_dir * sin(dir * ROT_SPEED)
		+ sc->plr.dir_y * cos(dir * ROT_SPEED);
	old_plane_x = sc->plr.plan_x;
	sc->plr.plan_x = sc->plr.plan_x * cos(dir * ROT_SPEED)
		- sc->plr.plan_y * sin(dir * ROT_SPEED);
	sc->plr.plan_y = old_plane_x * sin(dir * ROT_SPEED)
		+ sc->plr.plan_y * cos(dir * ROT_SPEED);
}

void	player_straf(t_scene *sc, int dir)
{
	double	new_x;
	double	new_y;
	double	straf_ang_x;
	double	straf_ang_y;

	dir *= -1;
	straf_ang_x = sc->plr.dir_y;
	straf_ang_y = -sc->plr.dir_x;
	new_x = sc->plr.pos_x + straf_ang_x * dir * PLR_SPEED;
	new_y = sc->plr.pos_y + straf_ang_y * dir * PLR_SPEED;
	if (sc->map.str[(int)new_y * sc->map.size_x + (int)new_x] != '1')
	{
		sc->plr.pos_x = new_x;
		sc->plr.pos_y = new_y;
	}
}

int		player_move(t_scene *sc)
{
	if (sc->key.rotl)
		player_rot(sc, sc->dir.left);
	if (sc->key.rotr)
		player_rot(sc, sc->dir.right);
	if (sc->key.up)
		player_go(sc, sc->dir.up);
	if (sc->key.down)
		player_go(sc, sc->dir.down);
	if (sc->key.strafl)
		player_straf(sc, sc->dir.left);
	if (sc->key.strafr)
		player_straf(sc, sc->dir.right);
	if (sc->key.esc)
		scene_destroy(sc);
	redraw_view(sc);
	return (1);
}
