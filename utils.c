//
// Created by  Anastasia on 15.04.2021.
//
#include "utils.h"


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