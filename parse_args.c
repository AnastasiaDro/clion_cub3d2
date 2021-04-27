/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 04:40:59 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 04:43:11 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "exceptions.h"

void	*parse_args(int argc, char *argv, t_data *m_struct)
{
	if (argc == 1 || argc > 3)
	{
		throw_exception()
	}
	
}