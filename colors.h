//
// Created by  Anastasia on 18.04.2021.
//

#ifndef COLORS_H
# define  COLORS_H
# include "new_cub_utils.h"
# include "exceptions.h"

int check_color_part(char *str);

int go_to_the_next_color(int i, char *str);

void make_color_exception(char *s, t_data *m_struct);

int check_color_s_end(char *str, int i);

int get_color(char *s, t_data *m_struct);



#endif //CLION_CUB3D2_COLOR_H
