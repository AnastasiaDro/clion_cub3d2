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
            parcer_new.c draw_utils.c textu_cub_utils.c texture_parse.c new_cub_utils.h key_hooking.c key_hooking.h \
            sprites_utils.c exceptions.c
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