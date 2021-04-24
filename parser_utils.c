//
// Created by  Anastasia on 15.04.2021.
//
#include <stdlib.h>
#include "parser_utils.h"

void init_parse_flags(t_parse_flags *tParseF)
{
    tParseF->resol = 0;
    tParseF->floor_color = 0;
    tParseF->ceil_color = 0;
    tParseF->north = 0;
    tParseF->south = 0;
    tParseF->west = 0;
    tParseF->east = 0;
    tParseF->sprite = 0;
}


int ft_strchr_index(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int find_string_start(char *s)
{
	int i;

	i = 2; //третий индекс в массиве
	while (s[i] && s[i] == ' ' )
		i++;
	return (i); //вернем индекс символа
}

int get_texture_path(char *s, char **dst, int *flag)
{
    int start_i;

    *flag = 1;
    start_i = find_string_start(s);
    *dst = ft_strdup(&s[start_i]);
    free(s);
    return (1);
}

int is_symbol_valid(char *s, char *arr)
{
	int max_index;

	max_index = (int)ft_strlen(s) - 1;
	int arr_index = 0;
	while (max_index >= 0)
	{
		arr_index = ft_strchr_index(arr, s[max_index]);
		if(arr_index == -1)
			return (max_index);
		max_index--;
	}
	return (-1);
}
