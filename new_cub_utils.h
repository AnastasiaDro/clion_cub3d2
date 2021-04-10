//
// Created by  Anastasia on 25.03.2021.
//

#ifndef NEW_CUB_UTILS_H
#define NEW_CUB_UTILS_H
# include "math.h"
#include "texture_parse.h"
#include "libft/libft.h"
#include "sprites_utils.h"
#include "params_struct.h"

typedef struct  s_data {
	void        *img;
	char        *addr;

	void       *mlx_win;
	void        *mlx;
	int         bits_per_pixel;
	int         line_length;
	int         endian;

	int side;

	char **map;

    double map_player_x;
    double map_player_y;
	//ширина и высота экрана
	int screen_width;
	int screen_higth;

	// параметры
	t_params *params;

	//позиция игрока
	float player_x;
	float player_y;
	//угол наклона
	float player_a;
	//угол зрения
	float fov;

	//размер воксела
	int voxel_size;

	//вектор направления
	double dirX;
	double dirY;
	//camera plane
	double planeX;
	double planeY;

//текстуры
	t_textu *textu;
//инфа о текстуре
	t_spr_info *sprite_info;
//список для очистки
	t_list *lst;

	t_sprite *sprites_list;
}               t_data;

int change_x_p_coors(t_data *m_struct);

int change_y_p_coords(t_data *m_struct);

void     cerebus_mlx_pixel_put(t_data *data, int x, int y, int color);

//void throwException(char *msg, t_data *m_struct);

int draw_voxel1(t_data *m_struct, int voxel_size, int color);

int draw_lab_dda(t_data *m_struct);


int draw_floor_ceil1(t_data *m_struct, int screen_higth, int screen_width);

int cerebus_mlx_pixel_get(t_data *data, int x, int y);


#endif
