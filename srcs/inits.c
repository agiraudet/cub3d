/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:43:34 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/07 19:11:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int		setting_init(t_scene *sc, char *path)
{
	sc->map.str = ft_strdup("");
	sc->map.size_x = 0;
	sc->map.size_y = 0;
	sc->map.size_tile = 64;
	if (!parse_file(sc, path))
		return (0);
	sc->set.proj.scale = PROJ_SCALE;
	sc->set.proj.wd = sc->set.win_x / PROJ_SCALE;
	sc->set.proj.hg = sc->set.win_y / PROJ_SCALE;
	sc->set.proj.half_wd = sc->set.proj.wd / 2;
	sc->set.proj.half_hg = sc->set.proj.hg / 2;
	return (1);
}

int		buffer_init(t_scene *sc)
{
	t_tex	*buffer;

	buffer = &sc->img_buf;
	buffer->ptr = mlx_new_image(sc->view.mlx, sc->set.win_x, sc->set.win_y);
	if (!buffer->ptr)
	{
		error_set(1, "pointer to image buffer");
		return (0);
	}
	buffer->data = mlx_get_data_addr(buffer->ptr, &buffer->bpp, &buffer->line_len, &buffer->endian);
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
	sc->mini.size = MINI_SIZE / PROJ_SCALE;
	sc->mini.x = MINI_X / PROJ_SCALE;
	sc->mini.y = MINI_Y / PROJ_SCALE;
	sc->mini.show = MINI_SHOW;
	return (1);
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
				if (pos == 'E')
				{
					sc->plr.dir_x = 1.;
					sc->plr.dir_y = 0.;
					sc->plr.plan_x = 0.;
					sc->plr.plan_y = 0.66;
				}
				if (pos == 'W')
				{
					sc->plr.dir_x = -1.;
					sc->plr.dir_y = 0.;
					sc->plr.plan_x = 0.;
					sc->plr.plan_y = 0.66;
				}
				if (pos == 'S')
				{
					sc->plr.dir_x = 0.;
					sc->plr.dir_y = 1.;
					sc->plr.plan_x = 0.66;
					sc->plr.plan_y = 0.;
				}
				if (pos == 'N')
				{
					sc->plr.dir_x = 0.;
					sc->plr.dir_y = -1.;
					sc->plr.plan_x = 0.66;
					sc->plr.plan_y = 0.;
				}
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
	return (1);
}

int		view_init(t_scene *sc)
{
	sc->view.mlx = mlx_init();
	sc->view.win = mlx_new_window(sc->view.mlx, sc->set.win_x, sc->set.win_y, "cub3d");
	return (1);
}

int		hook_init(t_scene *sc)
{
	mlx_loop_hook(sc->view.mlx, &player_move, sc);
	mlx_hook(sc->view.win, 2, 1, &key_in, &sc->key);
	mlx_hook(sc->view.win, 3, 2, &key_out, &sc->key);
	return (1);
}

int		tex_init(t_scene *sc)
{
	sc->nb_tex = 5 + BONUS * 2;
	sc->texs = malloc(sizeof(t_tex) * sc->nb_tex);
	if (!sc->texs)
	{
		error_set(1, "texs array");
		return (0);
	}
	/*
	if (!tex_load(sc, TEX_NO, sc->set.tex_no))
	{
		error_set(2, sc->set.tex_no);
		free(sc->texs);
		return (0);
	}
	*/
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
		if(!tex_load(sc, TEX_BG, sc->set.tex_bg))
			return (0);
	}
	return (1);
}

int		spt_buffer_init(t_scene *sc)
{
	int		i;

	i = 0;
	sc->nb_sprite = 0;
	while (sc->map.str[i])
		if (sc->map.str[i++] == '2')
			sc->nb_sprite++;
	sc->spt_buffer = malloc(sizeof(t_sprite) * sc->nb_sprite);
	if (!sc->spt_buffer)
	{
		error_set(1, "sprite buffer");
		return (0);
	}
	return (1);
}

t_scene	*scene_init(char *path)
{
	t_scene	*sc;

	sc = malloc(sizeof(t_scene));
	if (!sc)
	{
		error_set(1, "scene object");
		return (0);
	}
	setting_init(sc, path);
	minimap_init(sc);
	spt_buffer_init(sc);
	plr_init(sc);
	key_init(sc);
	view_init(sc);
	hook_init(sc);
	buffer_init(sc);
	if (!tex_init(sc))
	{
		free(sc);
		return (0);
	}
	return (sc);
}
