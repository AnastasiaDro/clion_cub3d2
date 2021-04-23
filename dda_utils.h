//
// Created by Cesar Erebus on 4/22/21.
//

#ifndef DDA_UTILS_H
# define DDA_UTILS_H
# include "new_cub_utils.h"
# include "ray.h"

//проходим клетки, пока луч не врежется в стену
void go_to_the_wall(t_ray *ray, t_data *m_struct);

//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
void calc_camera_dist(t_ray *ray, t_data *m_struct);

#endif //CLION_CUB3D2_DDA_UTILS_H
