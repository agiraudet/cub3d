/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:41:51 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/07 19:09:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sprite_swap(t_scene *sc, int i)
{
	t_sprite	spt_tmp;

	spt_tmp = sc->spt_buffer[i];
	sc->spt_buffer[i] = sc->spt_buffer[i - 1];
	sc->spt_buffer[i - 1] = spt_tmp;
}

void	sprite_sort(t_scene *sc)
{
	int		i;

	i = 1;
	while (i < sc->nb_sprite)
	{
		if (sc->spt_buffer[i].dist < sc->spt_buffer[i - 1].dist)
		{
			sprite_swap(sc, i);
			i = 1;
		}
		else
			i++;
	}
}
