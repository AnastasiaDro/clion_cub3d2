# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 14:00:35 by cerebus           #+#    #+#              #
#    Updated: 2021/03/15 10:43:08 by cerebus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
SRC		=	mlx.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
            parcer.c draw_utils.c cub_utils.c texture_parse.c key_hooking.c minilibx_opengl_20191021/mlx_get_screen_size.m \
            sprites_utils.c exceptions.c parser_utils.c colors.c params.c main_inits.c \
            ray.c dda_utils.c wall_utils.c draw_sprites.c player_params.c \
            parse_resolution.c map_checker.c map_line_checkers.c fill_map.c is_empty.c \
            get_sprites_list.c check_symbols.c go_th_params.c

LIBFT	= 	libft.a
LIBMX   =   minilibx_opengl_20191021/libmlx.a

$(NAME):	
			gcc $(SRC) -L . $(LIBFT) $(LIBMX) -framework OpenGL -framework AppKit


all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus bclean