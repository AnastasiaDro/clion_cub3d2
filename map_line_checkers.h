//
// Created by Cesar Erebus on 4/24/21.
//

#ifndef MAP_LINE_CHECKERS_H
# define MAP_LINE_CHECKERS_H
# include "map_checker.h"

int check_line_middle(char *cur_s, int *l_i, int i, char **map);

int check_line_start(int *l_i, int cur_s_len, char *cur_s);

int check_lines_ends(char **map, int i, char *cur_s);

#endif
