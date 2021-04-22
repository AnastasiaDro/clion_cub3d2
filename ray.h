//
// Created by  Anastasia on 25.03.2021.
//

#ifndef RAY_H
#define RAY_H
typedef struct s_ray
{
    //вектор направления луча
    double rayDirX;
    double rayDirY;

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX;
    double deltaDistY;

}               t_ray;

#endif //CLION_CUB3D_RAY_H
