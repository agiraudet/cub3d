/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 04:09:45 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 01:39:33 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <math.h>
# include <mlx.h>

# define BLACK 4278190080
# define WHITE 4294967295
# define RED 4294901760
# define DARK_RED 4289921024
# define GREEN 4278255360
# define BLUE 4278190335
# define YELLOW 4294967040
# define CYAN 4278255615
# define MAGENTA 4294902015
# define GRAY 4282400832

typedef struct	s_view
{
	void	*mlx;
	void	*win;
}				t_view;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_rect
{
	int		x;
	int		y;
	int		wd;
	int		hg;
}				t_rect;

float	deg_to_rad(int angle);
int		rgb_to_i(int a, int r, int g, int b);
int		fix_angle(float a);

t_rect	rect_init(float x, float y, float wd, float hg);
t_point	point_init(float x, float y);
void	rect_draw(t_view *v, t_rect rect, int color, int outline);
void	line_draw(t_view *v, t_point p1, t_point p2, int color);
void	line_draw_ang(t_view *v, t_point p1, float angle, int color, int len);

#endif
