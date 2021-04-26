/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:53:57 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:55:40 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser_utils.h"

void	init_parse_flags(t_parse_flags *tParseF)
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

int	ft_strchr_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	find_string_start(char *s)
{
	int	i;

	i = 2;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

int	get_tex_path(char *s, char **dst, int *flag)
{
	int	start_i;

	*flag = 1;
	start_i = find_string_start(s);
	*dst = ft_strdup(&s[start_i]);
	free(s);
	return (1);
}

int	is_symbol_valid(char *s, char *arr)
{
	int	max_index;
	int	arr_index;

	max_index = (int)ft_strlen(s) - 1;
	arr_index = 0;
	while (max_index >= 0)
	{
		arr_index = ft_strchr_index(arr, s[max_index]);
		if (arr_index == -1)
			return (max_index);
		max_index--;
	}
	return (-1);
}
