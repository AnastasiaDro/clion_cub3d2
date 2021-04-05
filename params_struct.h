//
// Created by Cesar Erebus on 4/4/21.
//

#ifndef PARAMS_STRUCT_H
#define PARAMS_STRUCT_H
typedef struct s_params
{
    int screen_height;
    int screen_weight;

    char *north_texture_path;
    char *south_texture_path;
    char *west_texture_path;
    char *east_texture_path;
    char *sprite_texture_path;

    int floor_color;
    int ceil_color;
}               t_params;
#endif //CLION_CUB3D_PARAMS_STRUCT_H
