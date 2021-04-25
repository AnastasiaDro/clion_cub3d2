//
// Created by  Anastasia on 25.04.2021.
//

#include "get_next_line/get_next_line.h"
#include "parcer.h"
#include "parser_utils.h"
#include "constants.h"

int go_th_params(int fd, t_data *m_struct, t_list **last_elem, char **line)
{
	int index;
	int elems_num;
	t_parse_flags parse_f;

	init_parse_flags(&parse_f);
	elems_num = 0;
	while (get_next_line(fd, line))
	{
		index = is_map_start(*line);
		if (index == MAP_STARTED)
		{
			if (check_fe_line(*line) == MAP_ERROR)
				throw_map_except(m_struct);
			ft_lstadd_front(last_elem, ft_lstnew(*line));
			elems_num++;
			break;
		}
		else
		{
			if(is_empty(line))
				continue;
			if (!(get_n_check_textures(line[index], m_struct, &parse_f)) && !(get_n_check_params(line[index],
																								  m_struct, &parse_f)))
				throw_map_except(m_struct);
		}
	}
//	free(line);
//	line = NULL;
	return (elems_num);
}