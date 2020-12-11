/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:21:38 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/11 01:07:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

# define BUFFER_SIZE 4096

typedef struct		s_line
{
	int				fnb;
	char			*cont;
	struct s_line	*next;
}					t_line;

int					get_next_line(int fd, char **line);
int					getnl(const char *str);
int					clean_join(char **cont, char *buf);
int					get_first_line(char **line, char **cont);

#endif
