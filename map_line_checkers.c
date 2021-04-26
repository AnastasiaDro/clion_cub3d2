/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_checkers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:37:39 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 22:39:53 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_line_checkers.h"

int	check_lines_ends(char **map, int i, char *cur_s)
{
	char	*next_s;
	int		next_s_len;
	int		cur_s_len;

	cur_s_len = (int) ft_strlen(cur_s);
	next_s = map[i + 1];
	next_s_len = (int) ft_strlen(next_s);
	if (cur_s_len < next_s_len)
	{
		if (small_first_str(next_s, next_s_len, cur_s_len) == MAP_ERROR)
			return (MAP_ERROR);
	}
	else if (cur_s_len > next_s_len)
	{
		if (big_first_str(cur_s, next_s_len, cur_s_len) == MAP_ERROR)
			return (MAP_ERROR);
	}
	else
	{
		if (next_s[next_s_len - 1] == '0')
			return (MAP_ERROR);
	}
	return (1);
}

int	check_line_start(int *l_i, int cur_s_len, char *cur_s)
{
	while (*l_i < cur_s_len)
	{
		if (cur_s[*l_i] == '0')
			return (MAP_ERROR);
		if (cur_s[*l_i] == '1')
			break ;
		(*l_i)++;
	}
	return (1);
}

int	check_line_middle(char *cur_s, int *l_i, int i, char **map)
{
	int	cur_s_len;

	cur_s_len = (int) ft_strlen(cur_s);
	while (*l_i < cur_s_len)
	{
		if (cur_s[*l_i] == '0')
		{
			if (check_borders(map, (*l_i), i, 1) == MAP_ERROR)
				return (MAP_ERROR);
		}
		(*l_i)++;
	}
	return (1);
}
