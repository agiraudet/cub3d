/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:43 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 01:12:53 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include <math.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/includes/libft.h"
# include "settings.h"

typedef struct	s_sptbuf
{
	double			x;
	double			y;
	int				hit;
	double			dist;
}				t_sptbuf;

typedef struct	s_spt_render
{
	double		inv_det;
	double		tsfm_x;
	double		tsfm_y;
	double		x;
	double		y;
	int			screen_x;
	int			hg;
	int			wd;
	int			draw_start_y;
	int			draw_start_x;
	int			draw_end_y;
	int			draw_end_x;
}				t_spt_render;

typedef struct	s_sprite
{
	int			nb;
	double		*z_buffer;
	t_sptbuf	*buf;
	t_spt_render	data;
	int			count;
}				t_spt;


typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
}				t_player;

typedef struct	s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			hit;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	double		perp_wall_dist;
	int			line_hg;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct		s_view
{
	void			*mlx;
	void			*win;
	int				win_alive;
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

typedef struct	s_floor
{
	double		ray_dir_x0;
	double		ray_dir_x1;
	double		ray_dir_y0;
	double		ray_dir_y1;
	int			p;
	double		pos_z;
	double		row_dist;
	double		step_x;
	double		step_y;
	double		x;
	double		y;
	int			cell_x;
	int			cell_y;
	int			tex_x;
	int			tex_y;
	t_tex		*tex;
}				t_floor;

typedef struct		s_minimap
{
	int				size;
	int				show;
	int				x;
	int				y;
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
	char			*tex_s1;
	char			*tex_s2;
	char			*tex_f;
	char			*tex_bg;
	unsigned int	color_f;
	unsigned int	color_c;
	char			*map;
	int				mini;
	int				prnt_scr;
	t_proj			proj;
}					t_settings;

typedef struct		s_keys
{
	int				up;
	int				down;
	int				rotl;
	int				rotr;
	int				strafl;
	int				strafr;
	int				esc;
}					t_keys;

typedef struct		s_map
{
	int				size_x;
	int				size_y;
	int				size_tile;
	char			*str;
}					t_map;

typedef struct		s_error
{
	int				flag;
	int				type;
	char			*msg;
}					t_error;

typedef struct		s_dir
{
	int				up;
	int				down;
	int				left;
	int				right;
}					t_dir;

typedef struct	s_anim
{
	int				frame;
	int				speed;
}				t_anim;


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
	t_spt			spt;
	t_dir			dir;
	t_anim			anim;
	int				nb_tex;
}					t_scene;

t_scene				*scene_init(char *path, int prnt_scr);
int					parse_file(t_scene *sc, char *path);
int					key_in(int k, t_keys *keys);
int					key_out(int k, t_keys *keys);
int					player_move(t_scene *sc);
int					tex_load(t_scene *sc, int tex_nb, char *path);
float				deg_to_rad(int angle);
unsigned int		rgb_to_i(int a, int r, int g, int b);
int					fix_angle(float a);
t_rect				rect_init(int x, int y, int wd, int hg);
void				rect_draw(t_scene *sc, t_rect rect, unsigned int color, int outline);
void				redraw_view(t_scene *sc);
void				i_to_rgb(unsigned int color, int *rgba);
void				pixel_put_buffer(t_scene *sc, int x, int y, unsigned int color);
void				minimap_draw(t_scene *sc);
void				raycast(t_scene *sc);
void				error_set(int type, char *msg);

unsigned int		tex_get_color(t_tex *tex, int x, int y);

void	ray_draw(t_scene *sc, t_ray *ray, int x);
void		ceil_render(t_scene *sc, int x, t_ray *ray);
void		floor_render(t_scene *sc, int x, t_ray *ray);
void		strip_render(t_scene *sc, int x, t_ray *ray);
void	ground_render(t_scene *sc);
int		check_map(t_scene *sc);
int		check_extension(char *file);
void	tex_put(t_scene *sc, t_tex *tex, int x, int y);

void		spt_init(t_scene *sc);
void		spt_get_dist(t_scene *sc);
void		spt_sort(t_spt *spt);
void		sp_d(t_scene *sc);
void		spt_draw(t_scene *sc);

void				anim_next_frame(t_scene *sc);
t_tex				*tex_load2(t_view *view, char *path);
int					bmp_to_file(t_tex *img, char *path);
int					scene_destroy(t_scene *sc);
#endif
