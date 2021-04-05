//
// Created by  Anastasia on 29.03.2021.
//

#ifndef TEXTURE_PARSE_H
#define TEXTURE_PARSE_H
# include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
# define NORTH_TEXTURE "/Users/anastasia/CLionProjects/clion_cub3d2/textures/128caves_wall.xpm"
# define SOUTH_TEXTURE "/Users/anastasia/CLionProjects/clion_cub3d2/textures/128gate.xpm"
# define WEST_TEXTURE  "/Users/anastasia/CLionProjects/clion_cub3d2/textures/128mcity_wall11.xpm"
# define EAST_TEXTURE  "/Users/anastasia/CLionProjects/clion_cub3d2/textures/128hell_nasty03.xpm"
//
//# define NORTH_TEXTURE "/Users/cerebus/Documents/clion_cub3d/textures/128caves_wall.xpm"
//# define SOUTH_TEXTURE "/Users/cerebus/Documents/clion_cub3d/textures/128gate.xpm"
//
//# define EAST_TEXTURE  "/Users/cerebus/Documents/clion_cub3d/textures/128mcity_wall11.xpm"
//# define WEST_TEXTURE  "/Users/cerebus/Documents/clion_cub3d/textures/128hell_nasty03.xpm"

typedef struct s_textu
{
	char 		*adress;
	void 		*mlx;
	void 		*img;
	char    	*addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int         height;
	int         width;
}				t_textu;


void init_textu_arr(t_textu *textu, int height, int width);


int textu_mlx_pixel_get(t_textu *textu, int x, int y);

#endif //TEXTURE_PARSE_H
