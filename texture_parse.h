//
// Created by  Anastasia on 29.03.2021.
//

#ifndef TEXTURE_PARSE_H
#define TEXTURE_PARSE_H
# include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"


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
	char		**exceptions_arr;
}				t_textu;

typedef struct s_txdraw
{
	t_textu *textu;
	int texX;
	int texY;

}				t_txdraw;

int init_textu_arr(t_textu *textu, int height, int width);


int textu_mlx_pixel_get(t_textu *textu, int x, int y);

int textu_start_init(t_textu *textu);

#endif //TEXTURE_PARSE_H
