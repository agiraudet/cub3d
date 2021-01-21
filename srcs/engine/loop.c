/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 03:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 12:58:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_init(t_scene *sc)
{
	mlx_loop_hook(sc->view.mlx, &player_move, sc);
	mlx_hook(sc->view.win, KeyPress, KeyPressMask, &key_in, &sc->key);
	mlx_hook(sc->view.win, KeyRelease, KeyReleaseMask, &key_out, &sc->key);
}

void	key_init(t_scene *sc)
{
	sc->key.up = 0;
	sc->key.down = 0;
	sc->key.rotl = 0;
	sc->key.rotr = 0;
	sc->key.strafl = 0;
	sc->key.strafr = 0;
	sc->key.esc = 0;
}

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
	if (sc->key.esc)
		scene_destroy(sc);
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
