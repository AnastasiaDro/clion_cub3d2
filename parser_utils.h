//
// Created by  Anastasia on 15.04.2021.
//

#ifndef UTILS_H
# define UTILS_H
# include "libft/libft.h"
# include "cub_utils.h"


typedef struct s_parse_flags
{
    int resol;
    int floor_color;
    int ceil_color;
    int north;
    int south;
    int west;
    int east;
    int sprite;
}               t_parse_flags;



void init_parse_flags(t_parse_flags *tParseFlags);

int ft_strchr_index(char *s, char c);

int find_string_start(char *s);

int is_symbol_valid(char *s, char *arr);

int get_texture_path(char *s, char **dst, int *flag);

#endif
