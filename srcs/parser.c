/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:46:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/21 13:34:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	wip_str(t_map *map)
{
	char *str;
	int	i;

	str = map->str;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0')
			str[i] = '0';
		i++;
	}
}

void	map_put(t_scene *sc)
{
	int y;
	int x;

	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
			ft_putchar(sc->map.str[y * sc->map.size_x + x++]);
		ft_putchar('\n');
		y++;
	}
}

char	*map_correct_len(char *str, int old_len, int new_len, int nb_line)
{
	char	*new_str;
	int		i;
	int		j;
	int		line_count;

	new_str = malloc(sizeof(char) * (nb_line * new_len + 1));
	if (!new_str)
		return (0);
	line_count = 0;
	j = 0;
	while (line_count < nb_line)
	{
		i = 0;
		while (i < old_len)
			new_str[j++] = str[line_count * old_len + i++];
		while (i < new_len)
		{
			new_str[j++] = ' ';
			i++;
		}
		line_count++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*map_add_len(int new_len, const char *line)
{
	char *new_line;
	int	i;

	new_line = malloc(sizeof(char) * new_len + 1);
	i  = 0;
	while (i < new_len)
	{
		if (*line)
			new_line[i++] = *line++;
		else
			new_line[i++] = ' ';
	}
	new_line[i] = '\0';
	return(new_line);
}

void	map_add(t_map *map, const char *line)
{
	static int	nb_line = 0;
	char	*tmp;
	int		len;

	len = ft_strlen(line);
	if (len > map->size_x)
	{
		if (nb_line > 0)
			map->str = map_correct_len(map->str, map->size_x, len, nb_line);
		map->size_x = len;
	}
	else if (len < map->size_x)
		line = map_add_len(map->size_x, line);
	tmp = map->str;
	map->str = ft_strjoin(tmp, line);
	free(tmp);
	map->size_y += 1;
	nb_line++;
}

int		parse_file(t_scene *sc, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_set(2, path);
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (cmp_id(line, "R "))
			setting_res_set(&sc->set, line);
		else if (cmp_id(line, "NO"))
			setting_tex_set(&sc->set.tex_no, line);
		else if (cmp_id(line, "SO"))
			setting_tex_set(&sc->set.tex_so, line);
		else if (cmp_id(line, "WE"))
			setting_tex_set(&sc->set.tex_we, line);
		else if (cmp_id(line, "EA"))
			setting_tex_set(&sc->set.tex_ea, line);
		else if (cmp_id(line, "S "))
			setting_tex_set(&sc->set.tex_s, line);
		else if (cmp_id(line, "F "))
			setting_color_set(&sc->set.color_f, line);
		else if (cmp_id(line, "C "))
			setting_color_set(&sc->set.color_c, line);
		else if (cmp_id(line, "TF") && BONUS)
			setting_tex_set(&sc->set.tex_f, line);
		else if (cmp_id(line, "BG") && BONUS)
			setting_tex_set(&sc->set.tex_bg, line);
		else if (ft_strchr(" 1", *line) && *line)
			map_add(&sc->map, line);
		free(line);
	}
	map_put(sc);
	return (1);
}
