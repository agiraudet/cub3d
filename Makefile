# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2021/01/17 19:23:39 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR		= 	/usr/local/lib/minilibx

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

INC_DIR		=	includes/

SRCS_DIR	=	srcs/

SRCS_FILES	=	inits.c \
				loop.c \
				main.c \
				get_next_line.c \
				get_next_line_utils.c \
				bitmap.c \
				raycast.c \
				parser.c \
				texture.c \
				check_map.c \
				utils.c \
				sprite.c \
				sprite_render.c \
				minimap.c \
				destroy.c \
				render.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

CC			=	clang

BONUS		= 	1

CFLAGS		=	-Wall -Wextra -D BONUS=$(BONUS)

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
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

gflag:			$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

debug:			
				make fclean
				make gflag
clean:
				$(RM) $(OBJS)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				$(RM) $(NAME) $(LIBFT)
				make fclean -C $(LIBFT_DIR)

re:				fclean all

.PHONY:			all clean fclean re
