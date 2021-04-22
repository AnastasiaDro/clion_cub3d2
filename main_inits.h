//
// Created by Cesar Erebus on 4/22/21.
//

#ifndef MAIN_INITS_H
# define MAIN_INITS_H
#include "new_cub_utils.h"

void get_textures_paths(t_textu *textu, t_data *m_struct);

void init_t_data(t_data *m_struct);

void set_data(t_data *m_struct, t_params *params, t_textu *textu, t_spr_info *spr_info);

void init_all(t_data *m_struct);
#endif
