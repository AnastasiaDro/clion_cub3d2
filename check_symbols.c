/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 22:53:57 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 22:47:46 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "constants.h"
#include "player_params.h"
#include "exceptions.h"

int	check_symbols(char *s, t_data *m_struct, int *flag_player)
{
	int	player_i;

	player_i = is_symbol_valid(s, MAP_SYMBOL);
	if (player_i != -1)
	{
		if (ft_strchr(PLAYER_SYMBOLS, s[player_i]) == NULL)
			throw_map_except(m_struct);
		else
		{
			if (*flag_player == 1)
			{
				throw_exception(MORE_PLAYERS);
				free_all(m_struct);
				exit(0);
			}
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

 int cmp_space_str(char *line)
 {
     int slen;
     char *cmp_str;
     int res;

     if (*line == '\0')
         return (0);
     slen = (int)ft_strlen(line);
     cmp_str = malloc((slen + 1) * sizeof(char));
     while(slen >= 0)
     {
         cmp_str[slen-1] = ' ';
         slen--;
     }
     res = ft_strncmp(line, cmp_str, slen);
     free(cmp_str);
     return (res);
 }

