/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_th_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:24:42 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 14:25:39 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "parser.h"
#include "parser_utils.h"
#include "constants.h"

void	add_to_list(char **line, t_data *m_struct, t_list **last_elem)
{
	if (check_fe_line(*line) == MAP_ERROR)
		throw_map_except(m_struct);
	ft_lstadd_front(last_elem, ft_lstnew(*line));
}

int		go_th_params(int fd, t_data *m_struct, t_list **last_elem, char **line)
{
	int				index;
	int				elems_num;
	t_parse_flags	parse_f;

	init_parse_flags(&parse_f);
	elems_num = 0;
	while (get_next_line(fd, line))
	{
		index = is_map_start(*line);
		if (index == MAP_STARTED)
		{
			add_to_list(line, m_struct, last_elem);
			elems_num++;
			break ;
		}
		else
		{
			if (is_empty(line))
				continue;
			if (!(get_n_check_textures(line[index], m_struct, &parse_f)) && \
				!(get_n_check_params(line[index], m_struct, &parse_f)))
				throw_map_except(m_struct);
		}
	}
	return (elems_num);
}
