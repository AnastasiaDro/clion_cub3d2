//
// Created by  Anastasia on 25.03.2021.
//

#ifndef RAY_H
#define RAY_H
#include "new_cub_utils.h"
typedef struct s_ray
{
    //вектор направления луча
    double DirX;
    double DirY;

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX;
    double deltaDistY;

    //точка на векторе камеры, счиается за 100% ширина экрана
    double cameraX;

    int hit;

    int stepX;
    int stepY;

    int mapX;
    int mapY;

    //расстояние до стены?
    double perpWallDist;
}               t_ray;

void calc_ray_dir(t_ray *ray, t_data *m_struct, int x);

void calc_ray_length(t_ray *ray);

void calc_step_side_dist(t_ray *ray, t_data *m_struct);

void set_ray_params(t_ray *ray, t_data *m_struct, int x);

#endif //CLION_CUB3D_RAY_H
