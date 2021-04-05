/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d        		                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:14:07 by cerebus           #+#    #+#             */
/*   Updated: 2021/02/25 16:14:07 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H
# include "math.h"
# define NORTH_COLOR 0x990099 //фиолетовый
# define SOUTH_COLOR 0xFFFFFF // белый
# define WEST_COLOR  0x11bfff // голубой
# define EAST_COLOR  0xFF8000 // оранжевый
//
typedef struct  s_data {
    void        *img;
    char        *addr;
    void       *mlx_win;
    void        *mlx;
    int         bits_per_pixel;
    int         line_length;
    int         endian;

    char **map;

    int map_player_x;
    int map_player_y;
    //ширина и высота экрана
    int screen_width;
    int screen_higth;

    //позиция игрока
    float player_x;
    float player_y;
    //угол наклона
    float player_a;
    //угол зрения
    float fov;

    //размер воксела
    int voxel_size;
    int voxel_x;
    int voxel_y;

    char *north_texture_path;
    void *north_image;
}               t_data;

void     cerebus_mlx_pixel_put(t_data *data, int x, int y, int color);

int draw_voxel1(t_data *m_struct, int voxel_size, int color);

int draw_walls(t_data *m_struct);

int draw_labyrinth(t_data *m_struct);

int draw_line(t_data *m_struct);

int draw_lines(t_data *m_struct);

int draw_player(t_data *m_struct, int voxel_size, int color);

int change_x_p_coors(t_data *m_struct);

int change_y_p_coords(t_data *m_struct);

int draw_column(t_data *m_struct, float x, float y_start, float higth, int color);

int draw_lab_dda(t_data *m_struct);
#endif