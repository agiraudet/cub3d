# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2020/12/10 02:16:36 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR		= 	/usr/local/lib/minilibx

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

INC_DIR		=	includes/

SRCS_DIR	=	srcs/

SRCS_FILES	=	inits.c loop.c main.c mlx_draw.c mlx_utils.c wip.c raycast.c render.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

NAME		=	cub3d

DEP			=	-lft -lmlx_Linux -lXext -lX11 -lm

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INC_DIR)

all:			$(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR)
				cp $(LIBFT_DIR)$(LIBFT) $(NAME)

$(NAME):		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP)

debug:			$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -fsanitize=address -g -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP)
clean:
				$(RM) $(OBJS)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				$(RM) $(NAME) $(LIBFT)
				make fclean -C $(LIBFT_DIR)

re:				fclean all

.PHONY:			all clean fclean re
