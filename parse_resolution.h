//
// Created by Cesar Erebus on 4/24/21.
//

#ifndef PARSE_RESOLUTION_H
# define  PARSE_RESOLUTION_H
# include "cub_utils.h"
# include "exceptions.h"
# define MAX_WIDTH_NUM_LENGTH 4
# define MAX_HEIGHT_NUM_LENGTH 4

int get_num_length(char *str, int *i, int *num_start);

int parse_resolution(char *s, t_data *m_struct, int *flag);

void throw_resol_except(char **s, t_data *m_struct);

int set_max_resolution(t_data *m_struct, char *s, int max_w, int max_h);

int init_z_buffer(t_data *m_struct);

#endif //CLION_CUB3D2_PARSE_RESOLUTION_H
