/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:07:16 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 02:37:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_settings	settings_init()
{
	t_settings	set;

	set.win_x = 1024;
	set.win_y = 512;
	set.win_label = ft_strdup("TEST");
	return (set);
}

t_player	player_init()
{
	t_player	plr;

	plr.x = 256;
	plr.y = 256;
	plr.dx = ROT_MUL;
	plr.dy = 0;
	plr.angle = 0;
	return(plr);
}

t_keys		keys_init()
{
	t_keys	key;

	key.w = 0;
	key.s = 0;
	key.a = 0;
	key.d = 0;
	return (key);
}

t_map		map_init()
{
	t_map	map;

	map.size_x = 8;
	map.size_y = 8;
	map.size_tile = 64;
	map.str = ft_strdup("1111111110100001100010011000010110000101100100011000000111111111");
	return (map);
}

t_scene		*scene_init()
{
	t_scene		*sc;

	sc = malloc(sizeof(t_scene));
	if (!sc)
		return (0);
	sc->set = settings_init();
	sc->plr = player_init();
	sc->key = keys_init();
	sc->map = map_init();
	sc->mlx = mlx_init();
	sc->win = mlx_new_window(sc->mlx, sc->set.win_x, sc->set.win_y, sc->set.win_label);
	mlx_do_key_autorepeaton(sc->mlx);
	mlx_key_hook(sc->win, &keys_in, &sc->key);
	mlx_loop_hook(sc->mlx, &player_move, sc);
	mlx_hook(sc->win, 2, 0, &keys_in, &sc->key);
	mlx_hook(sc->win, 3, 0, &keys_out, &sc->key);

	
	return (sc);
}

void	scene_destroy(t_scene *sc)
{
	//mlx_destroy_window(sc->mlx, sc->win);
	mlx_destroy_display(sc->mlx);
	free(sc->set.win_label);
	free(sc->map.str);
	free(sc);
}
