cmake_minimum_required(VERSION 3.17)
project(clion_cub3d2 C)

set(CMAKE_C_STANDARD 99)


#imagetest.c mlx.c
add_executable(clion_cub3d2 mlx.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
        parcer.c draw_utils.c textu_cub_utils.c texture_parse.c new_cub_utils.h key_hooking.c key_hooking.h minilibx_opengl_20191021/mlx_get_screen_size.m
        sprites_utils.c sprites_utils.h exceptions.h params.h exceptions.c utils.h utils.c colors.h colors.c params.c main_inits.c main_inits.h dda_utils.h ray.c)


#дом
target_link_libraries(clion_cub3d2 "-framework OpenGL -framework AppKit")
target_link_libraries(clion_cub3d2 "/Users/anastasia/CLionProjects/clion_cub3d/minilibx_opengl_20191021/libmlx.a")
target_link_libraries(clion_cub3d2 "/Users/anastasia/CLionProjects/clion_cub3d/libft.a")

#школа
#target_link_libraries(clion_cub3d2 "-framework OpenGL -framework AppKit")
#target_link_libraries(clion_cub3d2 "/Users/cerebus/projects/clion_cub3d2/minilibx_opengl_20191021/libmlx.a")
#target_link_libraries(clion_cub3d2 "/Users/cerebus/projects/clion_cub3d2/libft.a")