//
// Created by  Anastasia on 25.04.2021.
//
#include <printf.h>
#include "libft/libft.h"
#include "cub_utils.h"
#include "parser_utils.h"
#include "exceptions.h"

void check_was_player(int flag_player, t_data *m_struct)
{
	if (flag_player == 0)
	{
		throwException(NO_PLAYER);
		free_all(m_struct);
		exit(0);
	}
}

void set_player_coords(t_data *m_struct, int is_player, int elems_num, char **map)
{
	m_struct->map_player_x = (double)is_player + 0.5;
	m_struct->map_player_y = (double)(elems_num - 1) + 0.5;
	map[elems_num - 1][is_player] = '0';
}

void find_player(int *elems_num, t_list **elem, t_data *m_struct, char **map)
{
	int is_player;
	int flag_player;

	flag_player = 0;
	while (*elems_num)
	{
		map[(*elems_num) - 1] = (char *)(*elem)->content;
		(*elem)->content = NULL;
		is_player = check_symbols(map[(*elems_num)-1], m_struct, &flag_player);
		if(is_player)
			set_player_coords(m_struct, is_player, *elems_num, map);
		get_sprites_list(map[(*elems_num) - 1], m_struct, *elems_num);
		(*elem) = (*elem)->next;
		(*elems_num)--;
	}
	check_was_player(flag_player, m_struct);
}

int fill_map(t_list **last_elem, int elems_num, t_data *m_struct)
{
	char **map;
	t_list *elem;
	char *st;
	int el_num;

	map = ft_calloc(elems_num +1 , sizeof(char *)); //количество наших строчек + 1 для зануления
	elem = *last_elem;
	st = (char *)elem->content;
	while('\0' == *st)
	{
		elem = elem->next;
		elems_num--;
		st = (char *)elem->content;
	}
	el_num = elems_num;
	find_player(&elems_num, &elem, m_struct, map);
	m_struct->map = map;
	return (el_num);
}
