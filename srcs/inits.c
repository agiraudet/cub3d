/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:43:34 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 01:18:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		setting_init(t_scene *sc, char *path, int prnt_scr)
{
	if (prnt_scr == 2)
		sc->set.prnt_scr = 1;
	else
		sc->set.prnt_scr = 0;
	sc->map.str = ft_strdup("");
	sc->map.size_x = 0;
	sc->map.size_y = 0;
	sc->map.size_tile = 64;
	if (!parse_file(sc, path))
		return (0);
	return (1);
}

int		buffer_init(t_scene *sc)
{
	t_tex	*buffer;

	buffer = &sc->img_buf;
	buffer->wd = sc->set.win_x;
	buffer->hg = sc->set.win_y;
	buffer->ptr = mlx_new_image(sc->view.mlx, sc->set.win_x, sc->set.win_y);
	if (!buffer->ptr)
	{
		error_set(1, "pointer to image buffer");
		return (0);
	}
	buffer->data = mlx_get_data_addr(buffer->ptr, &buffer->bpp,
										&buffer->line_len, &buffer->endian);
	if (!buffer->data)
	{
		error_set(1, "data space of image buffer");
		free(buffer->ptr);
		return (0);
	}
	return (1);
}

int		minimap_init(t_scene *sc)
{
	int	mini_size;
	int	mini_offset;

	mini_size = sc->set.proj.wd >> 6;
	mini_offset = mini_size >> 4;
	sc->mini.size = mini_size / PROJ_SCALE;
	sc->mini.x = mini_offset / PROJ_SCALE;
	sc->mini.y = mini_offset / PROJ_SCALE;
	sc->mini.show = MINI_SHOW;
	return (1);
}

void	plr_plan_set(t_scene *sc, double px, double py)
{
	sc->plr.plan_x = px;
	sc->plr.plan_y = py;
}

void	plr_dir_set(t_scene *sc, double dx, double dy)
{
	sc->plr.dir_x = dx;
	sc->plr.dir_y = dy;
}

void	move_dir_set_ns(t_scene *sc, char pos)
{
	if (pos == 'N' || pos == 'S')
	{
		sc->dir.up = 1;
		sc->dir.down = -1;
		if (pos == 'N')
		{
			sc->dir.left = -1;
			sc->dir.right = 1;
		}
		else
		{
			sc->dir.left = 1;
			sc->dir.right = -1;
		}
	}
}

void	move_dir_set_we(t_scene *sc, char pos)
{
	if (pos == 'W' || pos == 'E')
	{
		sc->dir.up = 1;
		sc->dir.down = -1;
		if (pos == 'W')
		{
			sc->dir.left = 1;
			sc->dir.right = -1;
		}
		else
		{
			sc->dir.left = -1;
			sc->dir.right = 1;
		}
	}
}

void	plr_dir_init(t_scene *sc, char pos)
{
	if (pos == 'E')
	{
		plr_dir_set(sc, 1., 0.);
		plr_plan_set(sc, 0., 0.66);
	}
	if (pos == 'W')
	{
		plr_dir_set(sc, -1., 0.);
		plr_plan_set(sc, 0., 0.66);
	}
	if (pos == 'S')
	{
		plr_dir_set(sc, 0., 1.);
		plr_plan_set(sc, 0.66, 0.);
	}
	if (pos == 'N')
	{
		plr_dir_set(sc, 0., -1.);
		plr_plan_set(sc, 0.66, 0.);
	}
}

int		plr_init(t_scene *sc)
{
	int		x;
	int		y;
	char	pos;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			pos = sc->map.str[y * sc->map.size_x + x];
			if (ft_strchr("NEWS", pos))
			{
				sc->plr.pos_x = x;
				sc->plr.pos_y = y;
				plr_dir_init(sc, pos);
				move_dir_set_ns(sc, pos);
				move_dir_set_we(sc, pos);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		key_init(t_scene *sc)
{
	sc->key.up = 0;
	sc->key.down = 0;
	sc->key.rotl = 0;
	sc->key.rotr = 0;
	sc->key.strafl = 0;
	sc->key.strafr = 0;
	sc->key.esc = 0;
	return (1);
}

int		view_init(t_scene *sc)
{
	int screen_x;
	int screen_y;

	sc->view.mlx = mlx_init();
	screen_x = 0;
	screen_y = 0;
	mlx_get_screen_size(sc->view.mlx, &screen_x, &screen_y);
	if (screen_x < sc->set.win_x)
		sc->set.win_x = screen_x;
	if (screen_y < sc->set.win_y)
		sc->set.win_y = screen_y;
	sc->set.proj.scale = PROJ_SCALE;
	sc->set.proj.wd = sc->set.win_x / PROJ_SCALE;
	sc->set.proj.hg = sc->set.win_y / PROJ_SCALE;
	sc->set.proj.half_wd = sc->set.proj.wd / 2;
	sc->set.proj.half_hg = sc->set.proj.hg / 2;
	sc->view.win = mlx_new_window(sc->view.mlx,
			sc->set.win_x, sc->set.win_y, "cub3d");
	sc->view.win_alive = 1;
	return (1);
}

int		hook_init(t_scene *sc)
{
	mlx_loop_hook(sc->view.mlx, &player_move, sc);
	mlx_hook(sc->view.win, KeyPress, KeyPressMask, &key_in, &sc->key);
	mlx_hook(sc->view.win, KeyRelease, KeyReleaseMask, &key_out, &sc->key);
	return (1);
}

int		anim_init(t_scene *sc)
{
	sc->anim.frame = TEX_S;
	sc->anim.speed = 0;
	return (1);
}

int		tex_init(t_scene *sc)
{
	sc->nb_tex = 5 + BONUS * (2 + NB_FRAME);
	sc->texs = malloc(sizeof(t_tex) * sc->nb_tex);
	if (!sc->texs)
	{
		error_set(1, "texs array");
		return (0);
	}
	if (!tex_load(sc, TEX_NO, sc->set.tex_no))
		return (0);
	if (!tex_load(sc, TEX_SO, sc->set.tex_so))
		return (0);
	if (!tex_load(sc, TEX_WE, sc->set.tex_we))
		return (0);
	if (!tex_load(sc, TEX_EA, sc->set.tex_ea))
		return (0);
	if (!tex_load(sc, TEX_S, sc->set.tex_s))
		return (0);
	if (BONUS)
	{
		if (!tex_load(sc, TEX_F, sc->set.tex_f))
			return (0);
		if (!tex_load(sc, TEX_BG, sc->set.tex_bg))
			return (0);
		if (!tex_load(sc, TEX_S1, sc->set.tex_s1))
			return (0);
		if (!tex_load(sc, TEX_S2, sc->set.tex_s2))
			return (0);
	}
	return (1);
}

int		spt_buffer_init(t_scene *sc)
{
	int		i;

	i = 0;
	sc->spt.nb = 0;
	while (sc->map.str[i])
		if (sc->map.str[i++] == '2')
			sc->spt.nb++;
	sc->spt.z_buffer = malloc(sizeof(double*) * sc->set.proj.wd);
	if (!sc->spt.z_buffer)
	{
		error_set(1, "z_buffer");
		return (0);
	}
	sc->spt.buf = malloc(sizeof(t_sptbuf) * sc->spt.nb);
	if (!sc->spt.buf)
	{
		return (0);
	}
	spt_init(sc);
	return (1);
}

t_scene	*scene_init(char *path, int prnt_scr)
{
	t_scene	*sc;

	sc = malloc(sizeof(t_scene));
	if (!sc)
	{
		error_set(1, "scene object");
		return (0);
	}
	if (!setting_init(sc, path, prnt_scr))
	{
		free(sc);
		return (0);
	}
	view_init(sc);
	minimap_init(sc);
	spt_buffer_init(sc);
	plr_init(sc);
	key_init(sc);
	hook_init(sc);
	buffer_init(sc);
	if (!tex_init(sc))
		return (0);
	return (sc);
}
