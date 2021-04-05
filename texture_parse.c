//
// Created by  Anastasia on 29.03.2021.
//

#include "texture_parse.h"

#include "minilibx_opengl_20191021/mlx.h"


void init_textu_arr(t_textu *textu, int height, int width)
{
	int i = 0;
	while (i < 4)
	{
		textu[i].mlx = mlx_init();
		textu[i].img = mlx_xpm_file_to_image((textu[i]).mlx, (textu[i]).adress, &width, &height);
		textu[i].addr = mlx_get_data_addr(textu[i].img, &(textu[i].bits_per_pixel), &(textu[i].line_length),
										  &(textu[i].endian));
		textu[i].height = height;
		textu[i].width = width;
		i++;
	}
}


int textu_mlx_pixel_get(t_textu *textu, int x, int y)
{
	int color;
	char *dst;
	dst = textu->addr + (y * textu->line_length + x * (textu->bits_per_pixel / 8));
	color = *(int*)dst;
	return color;
}
