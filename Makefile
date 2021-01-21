# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2021/01/21 17:17:50 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR		= 	minilibx-linux

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

INC_DIR		=	includes/ -I $(MLX_DIR)

SRCS_DIR	=	srcs/

SRCS_FILES	=	anim_bonus.c \
				bitmap.c \
				check_map.c \
				destroy.c \
				get_next_line.c \
				get_next_line_utils.c \
				inits.c \
				loop.c \
				main.c \
				map.c \
				minimap_bonus.c \
				parser.c \
				parser_bonus.c \
				player.c \
				player_set.c \
				raycast.c \
				rect_bonus.c \
				render_bonus.c \
				render.c \
				settings.c \
				sprite.c \
				sprite_render.c \
				texture.c \
				utils.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS_BONUS	=	$(SRCS:.c=_b.o)

OBJS		=	$(SRCS:.c=.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

NAME		=	cub3d

DEP			=	-lft -lmlx_Linux -lXext -lX11 -lm

%.o:			%.c
				$(CC) $(CFLAGS) -D BONUS=0 -c $< -o $(<:.c=.o) -I $(INC_DIR)

%_b.o:			%.c
				$(CC) $(CFLAGS) -D BONUS=1 -c $< -o $(<:.c=_b.o) -I $(INC_DIR)


all:			$(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR)
				cp $(LIBFT_DIR)$(LIBFT) $(NAME)

$(NAME):		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

gflag:			$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

bonus:			$(OBJS_BONUS) $(LIBFT)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

debug:			
				make fclean
				make gflag
clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				$(RM) $(NAME) $(LIBFT)
				make fclean -C $(LIBFT_DIR)

re:				fclean all

.PHONY:			all clean fclean re
