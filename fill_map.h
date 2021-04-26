/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:20:47 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 14:21:30 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_MAP_H
# define FILL_MAP_H

int		fill_map(t_list **last_elem, int elems_num, t_data *m_struct);

void	find_player(int *elems_num, t_list **elem, \
				t_data *m_struct, char **map);

void	set_player_coords(t_data *m_struct, \
				int is_player, int elems_num, char **map);

void	check_was_player(int flag_player, t_data *m_struct);

#endif
