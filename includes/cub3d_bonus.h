/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:58:53 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 16:00:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

t_rect				rect_init(int x, int y, int wd, int hg);
int					anim_init(t_scene *sc);
void				rect_draw
	(t_scene *sc, t_rect rect, unsigned int color, int outline);
void				minimap_init(t_scene *sc);
void				skybox_render(t_scene *sc, int x, t_ray *ray);
void				minimap_draw(t_scene *sc);
void				anim_next_frame(t_scene *sc);
void				parse_bonus(t_scene *sc, const char *line);

#endif
