//
// Created by Cesar Erebus on 4/24/21.
//

#ifndef MAP_CHECKERS_H
# define MAP_CHECKERS_H
# include "constants.h"
# include "libft/libft.h"
#include "exceptions.h"

    int check_map (char **map, int elems_num);



    int big_first_str(char *cur_s, int next_s_len, int cur_s_len);

    int small_first_str(char *next_s, int next_s_len, int cur_s_len);

    int check_spc_borders(int start_i, int end_i, char **map, char *cur_s, int s_num);

    int check_borders(char **map, int l_i, int i, int coef);
#endif
