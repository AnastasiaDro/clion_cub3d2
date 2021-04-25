//
// Created by  Anastasia on 25.04.2021.
//
#include "cub_utils.h"

int get_sprites_list(char *s, t_data *m_struct, int elems_num)
{
	int i;
	double x;
	double y;

	i = 0;
	while (s[i])
	{
		if (s[i] == '2')
		{
			x = i + 0.5;
			y = elems_num - 1 + 0.5;
			sprite_lstadd_front(m_struct->sprite_info->sprite_list, sprite_lstnew(x, y));
			m_struct->sprite_info->num_sprites += 1;
		}
		i++;
	}
	return i;
}
