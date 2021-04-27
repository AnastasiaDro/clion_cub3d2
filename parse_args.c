/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 04:40:59 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:13:37 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "exceptions.h"
#include <stdio.h>

void	check_args_num(int argc)
{
	if (argc < 2 || argc > 3)
	{
		throw_exception(INVALID_ARGS_NUM);
		exit(0);
	}
}

void	check_save(char *save)
{
	if (ft_strncmp(save, "--save", ft_strlen(save)))
	{
		throw_exception(INVALID_THIRD_ARGUMENT);
		exit(0);
	}
}

void	check_map_arg(int argc, char *argv[])
{
	int	s_len;

	s_len = (int)ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &(argv[1][s_len - 4]), 4))
	{
		throw_exception(INVALID_FORMAT);
		exit(0);
	}
}
