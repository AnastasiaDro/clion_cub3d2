//
// Created by  Anastasia on 29.03.2021.
//

#include "texture_parse.h"

#include "minilibx_opengl_20191021/mlx.h"
#include "exceptions.h"


void made_exceptions_arr(t_textu *textu)
{
	textu->exceptions_arr = ft_calloc(sizeof (char *), 5);
	textu->exceptions_arr[0] = NORTH_TEX_PATH_ERROR;
	textu->exceptions_arr[1] = SOUTH_TEX_PATH_ERROR;
	textu->exceptions_arr[2] = WEST_TEX_PATH_ERROR;
	textu->exceptions_arr[3] = EAST_TEX_PATH_ERROR;
}

int textu_start_init(t_textu *textu)
{
    int i;

    i = 0;
    while (i < 4)
    {
        textu[i].mlx = NULL;
        textu[i].adress = NULL;
        textu[i].img = NULL;
        i++;
    }
    return (1);
}

int init_textu_arr(t_textu *textu, int height, int width)
{
	made_exceptions_arr(textu);
	int i = 0;
	while (i < 4)
	{
		textu[i].mlx = mlx_init();
		if((textu[i].img = mlx_xpm_file_to_image((textu[i]).mlx, (textu[i]).adress, &width, &height)) == NULL)
		{
			throwException(textu->exceptions_arr[i]);
			return (-1);
		}
		textu[i].addr = mlx_get_data_addr(textu[i].img, &(textu[i].bits_per_pixel), &(textu[i].line_length),
										  &(textu[i].endian));
		textu[i].height = height;
		textu[i].width = width;
		i++;
	}
	return (1);
}

