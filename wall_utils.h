//
// Created by  Anastasia on 23.04.2021.
//

#ifndef WALL_UTILS_H
# define WALL_UTILS_H
# include "ray.h"
#include "new_cub_utils.h"

typedef struct s_wall
{
	int line_height;
	int drawStart;
	int draw_end;
	double wallX; //where exactly the wall was hit
}				t_wall;

void calc_line_height(t_wall *wall, t_ray *ray, t_data *m_struct);

void calc_sart_pixels(t_wall *wall, t_data *m_struct);

void calc_wall_x(t_wall *wall, t_ray *ray, t_data *m_struct);


#endif //CLION_CUB3D2_WALL_UTILS_H
