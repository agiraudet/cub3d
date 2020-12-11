/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 02:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 01:24:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float			deg_to_rad(int angle)
{
	return (angle * M_PI / 180);
}

unsigned int	rgb_to_i(int a, int r, int g, int b)
{
	unsigned int res;

	res = 0;
	res += b;
	res += g * 256;
	res += r * 65536;
	res += a * 16777216;
	return (res);
}

int				fix_angle(float a)
{
	if (a > 359)
		return (a - 360);
	if (a < 0)
		return (a + 360);
	return (a);
}
