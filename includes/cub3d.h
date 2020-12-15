/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:43 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 14:02:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/includes/libft.h"
# include "settings.h"

typedef struct		s_ray
{
	float			angle;
	float			x;
	float			y;
	float			cos;
	float			sin;
	float			dist;
}					t_ray;

typedef struct		s_view
{
	void			*mlx;
	void			*win;
}					t_view;

typedef struct		s_rect
{
	int				x;
	int				y;
	int				wd;
	int				hg;
}					t_rect;


typedef struct		s_tex
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				line_len;
	int				endian;
	int				wd;
	int				hg;
}					t_tex;

typedef struct		s_tile
{
	char			data;
	t_rect			rect;
	unsigned int	color;
}					t_tile;

typedef struct		s_minimap
{
	int				size;
	int				nb_tile;
	t_tile			*tile;
	int				x;
	int				y;
	int				show_ray;
}					t_minimap;

typedef struct	s_proj
{
	int			wd;
	int			hg;
	int			half_wd;
	int			half_hg;
	int			scale;
}				t_proj;

typedef struct		s_settings
{
	int				win_x;
	int				win_y;
	char			*win_label;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	char			*tex_s;
	unsigned int	color_f;
	unsigned int	color_c;
	char			*map;
	int				mini;
	t_proj			proj;
}					t_settings;

typedef struct		s_player
{
	float				x;
	float				y;
	float				cos;
	float				sin;
	float				dx;
	float				dy;
	float				angle;
	int				fov;
}					t_player;

typedef struct		s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				la;
	int				ra;
}					t_keys;

typedef struct		s_map
{
	int				size_x;
	int				size_y;
	int				size_tile;
	char			*str;
}					t_map;

typedef struct		s_scene
{
	t_settings		set;
	t_player		plr;
	t_keys			key;
	t_map			map;
	t_view			view;
	t_minimap		mini;
	t_tex			*texs;
	t_tex			img_buf;
	int				nb_tex;
}					t_scene;

t_scene				*scene_init(char *path);
int		parse_file(t_scene *sc, char *path);
void	minimap_load(t_scene *sc);
int		key_in(int k, t_keys *keys);
int		key_out(int k, t_keys *keys);
int		player_move(t_scene *sc);
int	tex_load(t_scene *sc, int tex_nb, char *path);
void		ray_cast(t_scene *sc);
float				deg_to_rad(int angle);
unsigned int				rgb_to_i(int a, int r, int g, int b);
int				fix_angle(float a);
void			wall_draw(t_scene *sc, int ray_count, int wall_hg, t_ray *ray);
t_rect	rect_init(int x, int y, int wd, int hg);
void			minimap_draw(t_scene *sc);
void	minimap_ray_draw(t_scene *sc, t_ray *ray);
void    rect_draw(t_scene *sc, t_rect rect, int color, int outline);
void    line_draw(t_view *v, int x0, int y0, int x1, int y1);
void    line_ang_draw(t_view *v, int x, int y, float angle, int len);
int				point_in_rect(int x, int y, t_rect *rect);
int		minimap_check(t_scene *sc, int x, int y);
void	redraw_view(t_scene *sc);
int		tex_get_color(t_tex *tex, int x, int y);
int tex_draw(t_scene *sc, int tex_id, int x1, int y1);
void			i_to_rgb(int color, int *rgba);
void	pixel_put_buffer(t_scene *sc, int x, int y, int color);

#endif
