//
// Created by Cesar Erebus on 4/19/21.
//
#include "params_struct.h"
#include "unistd.h"

int init_params(t_params *params)
{
    params->north_texture_path = NULL;
    params->south_texture_path = NULL;
    params->west_texture_path = NULL;
    params->east_texture_path = NULL;
    params->sprite_texture_path = NULL;
    return (1);
}

