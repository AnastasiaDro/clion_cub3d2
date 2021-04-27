/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_th_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:24:42 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 22:27:34 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "parser.h"
#include "parser_utils.h"
#include "constants.h"
#include "parse_params_except.h"

void	add_to_list(char **line, t_data *m_struct, \
			t_list **last_elem, int *elems_num)
{
	if (check_fe_line(*line) == MAP_ERROR)
        throw_map_except(m_struct);
	(*elems_num)++;
	ft_lstadd_front(last_elem, ft_lstnew(*line));
}

int	go_th_params(int fd, t_data *m_s, t_list **last_elem, char **line)
{
	int				i;
	int				elems_num;
	t_parse_flags	parse_f;

	init_parse_flags(&parse_f);
	elems_num = 0;
	while (get_next_line(fd, line))
	{
		i = is_map_start(*line);
		if (i == MAP_STARTED)
		{
			add_to_list(line, m_s, last_elem, &elems_num);
			break ;
		}
		else
		{
			if (is_empty(line))
				continue ;
			if (!(get_check_tex(line[i], m_s, &parse_f)) \
			        && !(get_check_params(line[i], m_s, &parse_f)))
                throw_map_except(m_s);
		}
	}
	was_params(parse_f, m_s);
	return (elems_num);
}
