# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 14:00:35 by cerebus           #+#    #+#              #
#    Updated: 2021/04/27 05:05:00 by cerebus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
SRC		=	mlx.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
            parser.c draw_utils.c cub_utils.c texture_parse.c key_hooking.c \
            sprites_utils.c exceptions.c parser_utils.c colors.c params.c main_inits.c \
            ray.c dda_utils.c wall_utils.c draw_sprites.c player_params.c \
            parse_resolution.c map_checker.c map_line_checkers.c fill_map.c is_empty.c \
            get_sprites_list.c check_symbols.c go_th_params.c init_z_buffer.c parse_line_sect.c \
            parse_params_except.c is_map_start.c get_check_params.c get_check_tex.c sortSprites.c \
            parse_args.c increase_lst.c get_next_line/gnl_wrap_utils.c turn_on_off_flags.c make_move.c \
            do_screenshot.c throw_file_except.c key_press_release.c
CFLAGS	= 	-Wall -Wextra -Werror
LIBFT	= 	libft/libft.a
LIBMX   =   minilibx_opengl_20191021/libmlx.a
OBJS	= 	$(SRC:.c=.o)
BMP		= 	cub3d.bmp

$(NAME):	$(OBJS)
			@make -C libft
			@make -C minilibx_opengl_20191021
			gcc $(SRC) -L . $(LIBFT) $(LIBMX) -framework OpenGL -framework AppKit -o $(NAME)

all:		$(NAME)


clean:
			rm -f $(OBJS)
			@make clean -C libft
			@make clean -C minilibx_opengl_20191021

fclean:		clean
			@make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re