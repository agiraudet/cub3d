/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:57:41 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 02:46:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/includes/libft.h"
# include "mlx_utils.h"
# include <math.h>
# include <mlx.h>

# define ROT_SPEED 5
# define ROT_MUL 10
# define MAX_DOF 8
# define NB_RAY 60
# define RAY_OFFSET 1

typedef struct	s_settings
{
	int			win_x;
	int			win_y;
	char		*win_label;
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;
	char		*tex_s;
	int			color_f;
	int			color_c;
}				t_settings;

typedef struct	s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
}				t_player;

typedef struct	s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
}				t_keys;

typedef struct	s_map
{
	int			size_x;
	int			size_y;
	int			size_tile;
	char		*str;
}				t_map;

typedef struct	s_scene
{
	t_settings	set;
	t_player	plr;
	t_keys		key;
	t_map		map;
	void		*mlx;
	void		*win;
}				t_scene;

typedef struct	s_ray
{
	float		angle;
	float		x;
	float		y;
	float		xoff;
	float		yoff;
	int			dof;
}				t_ray;


int				keys_in(int k, t_keys *keys);
int				keys_out(int k, t_keys *keys);
int				player_move(t_scene *sc);
void			view_redraw(t_scene *sc);
void			map_draw2d(t_scene *sc);
void			player_draw2d(t_scene *sc);
void			ray_draw(t_ray *ray, t_scene *sc);
t_scene			*scene_init();
void			scene_destroy(t_scene *sc);
void			ray_cast(t_scene *sc);
void			wall_draw(t_scene *sc, int i, float dist, float ang, char dir);
void			clean_view(t_scene *sc);

#endif
