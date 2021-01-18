/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:07:37 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/17 15:21:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/Xlib.h>

void	tex_destroy(t_scene *sc, t_tex *tex)
{
	mlx_destroy_image(sc->view.mlx, tex->ptr);
}

void	settings_destroy(t_scene *sc)
{
	free(sc->set.tex_no);
	free(sc->set.tex_so);
	free(sc->set.tex_we);
	free(sc->set.tex_ea);
	free(sc->set.tex_s);
	if (BONUS)
	{
		free(sc->set.tex_f);
		free(sc->set.tex_bg);
	}
}

int		scene_destroy(t_scene *sc)
{
	int		i;

	printf("clean\n");
	i = 0;
	while (i < sc->nb_tex)
		tex_destroy(sc, &sc->texs[i++]);
	free(sc->texs);
	tex_destroy(sc, &sc->img_buf);
	settings_destroy(sc);
	free(sc->spt.z_buffer);
	free(sc->spt.buf);
	free(sc->map.str);
	if (sc->view.win_alive)
		mlx_destroy_window(sc->view.mlx, sc->view.win);
	free(sc);
	exit(0);
}
