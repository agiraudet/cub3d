/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:43:34 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 12:26:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		setting_init(t_scene *sc, char *path)
{
	sc->set.mini = MINIMAP;
	sc->map.str = ft_strdup("");
	sc->map.size_x = 0;
	sc->map.size_y = 0;
	sc->map.size_tile = 64;
	parse_file(sc, path);
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
		return (0);
	buffer->data = mlx_get_data_addr(buffer->ptr, &buffer->bpp, &buffer->line_len, &buffer->endian);
	if (!buffer->data)
	{
		free(buffer->ptr);
		return (0);
	}
	return (1);
}

int		minimap_init(t_scene *sc)
{
	int		i;

	sc->mini.size = MINI_SIZE;
	sc->mini.x = MINI_X;
	sc->mini.y = MINI_Y;
	sc->mini.show_ray = MINI_SHOW_RAY;
	i = 0;
	while (sc->map.str[i])
		if (sc->map.str[i++] != ' ')
			sc->mini.nb_tile += 1;
	sc->mini.tile = malloc(sizeof(t_tile) * sc->mini.nb_tile);
	if (!sc->mini.tile)
		return (0);
	minimap_load(sc);
	return (1);
}

int		plr_init(t_scene *sc)
{
	sc->plr.x = 5;
	sc->plr.y = 5;
	sc->plr.dx = PLR_SPEED;
	sc->plr.dy = 0;
	sc->plr.angle = 90;
	sc->plr.cos = cos(deg_to_rad(sc->plr.angle)) * PLR_SPEED;
	sc->plr.sin = sin(deg_to_rad(sc->plr.angle)) * PLR_SPEED;
	sc->plr.fov = 60;
	return (1);
}

int		key_init(t_scene *sc)
{
	sc->key.w = 0;
	sc->key.s = 0;
	sc->key.a = 0;
	sc->key.d = 0;
	sc->key.la = 0;
	sc->key.ra = 0;
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
	sc->nb_tex = 4;
	sc->texs = malloc(sizeof(t_tex) * sc->nb_tex);
	if (!sc->texs)
		return (0);
	if (!tex_load(sc, TEX_NO, sc->set.tex_no))
	{
		free(sc->texs);
		return (0);
	}
	return (1);
}

t_scene	*scene_init(char *path)
{
	t_scene	*sc;

	sc = malloc(sizeof(t_scene));
	if (!sc)
		return (0);
	setting_init(sc, path);
	minimap_init(sc);
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
