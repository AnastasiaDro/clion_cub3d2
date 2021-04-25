/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 22:53:57 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/25 22:56:17 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "constants.h"
#include "player_params.h"

int	check_symbols(char *s, t_data *m_struct, int *flag_player)
{
	int player_i;

	player_i = is_symbol_valid(s, MAP_SYMBOL);
	if (player_i != -1)
	{
		if (ft_strchr(PLAYER_SYMBOLS, s[player_i]) == NULL)
			throw_map_except(m_struct);
		else
		{
			if (*flag_player == 1)
				throw_map_except(m_struct);
			else
			{
				set_player_vision(s[player_i], m_struct);
				*flag_player = 1;
				return (player_i);
			}
		}
	}
	return (0);
}
