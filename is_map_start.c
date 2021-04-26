/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 01:56:10 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 01:56:27 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int	is_map_start(char *line)
{
	char	*ptr;
	int		i;

	ptr = line;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == ' ')
		{
			i++;
			continue ;
		}
		if (ptr[i] >= '0' && ptr[i] <= '9')
			return (MAP_STARTED);
		else if (ptr[i] == '0')
			return (ZERO_START_LINE);
		else
			return (i);
	}
	return (i);
}
