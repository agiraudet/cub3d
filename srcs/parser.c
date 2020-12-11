/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:58:27 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 01:32:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../includes/get_next_line.h"
#include <fcntl.h>

int			cmp_id(const char *str, const char *id)
{
	if (*str == *id && *(str + 1) == *(id + 1))
		return (1);
	return (0);
}

void	setting_res_set(t_settings *sets, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	sets->win_x = ft_atoi(values[1]);
	sets->win_y = ft_atoi(values[2]);
	i = 0;
	while (values[i])
		free(values[i++]);
}

void	setting_tex_set(char **tex, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	*tex = values[1];
	i = 0;
	while (values[i])
	{
		if (i != 1)
			free(values[i]);
		i++;
	}
}

void	setting_color_set(unsigned int *color, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	*color = rgb_to_i(255, atoi(values[1]), atoi(values[2]), atoi(values[3]));
	i = 0;
	while (values[i])
		free(values[i++]);
}

t_settings	setting_init(char *path)
{
	t_settings	sets;
	int			fd;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (sets);
	while (get_next_line(fd, &line) > 0)
	{
		if (cmp_id(line, "R "))
			setting_res_set(&sets, line);
		else if (cmp_id(line, "NO"))
			setting_tex_set(&sets.tex_no, line);
		else if (cmp_id(line, "SO"))
			setting_tex_set(&sets.tex_so, line);
		else if (cmp_id(line, "WE"))
			setting_tex_set(&sets.tex_we, line);
		else if (cmp_id(line, "EA"))
			setting_tex_set(&sets.tex_ea, line);
		else if (cmp_id(line, "S "))
			setting_tex_set(&sets.tex_s, line);
		else if (cmp_id(line, "F "))
			setting_color_set(&sets.color_f, line);
		else if (cmp_id(line, "C "))
			setting_color_set(&sets.color_c, line);
		free(line);
	}
	sets.win_label = ft_strdup("TEST");
	return (sets);
}
