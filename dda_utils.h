//
// Created by Cesar Erebus on 4/22/21.
//

#ifndef DDA_UTILS_H
# define DDA_UTILS_H
# include "cub_utils.h"
# include "ray.h"
#include "wall_utils.h"

//проходим клетки, пока луч не врежется в стену
void go_to_the_wall(t_ray *ray, t_data *m_struct);

//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
void calc_camera_dist(t_ray *ray, t_data *m_struct);

void calc_x_textu_coord(t_data *m_struct, t_ray *ray, t_wall *wall, t_txdraw *txdraw);

void cast_walls(t_data *m_struct, t_ray *ray, t_wall *wall, double *z_buffer);

void cast_sprites(t_data *m_struct, double const *z_buffer);


#endif //CLION_CUB3D2_DDA_UTILS_H
