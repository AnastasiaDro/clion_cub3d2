/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_except.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:33:09 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 05:23:50 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_params_except.h"

void	throw_params_exception(char *msg, int *is_error)
{
	throw_exception(msg);
	(*is_error)--;
}

void	throw_params_except(t_parse_flags pFlags, t_data *m_struct, int is_err)
{
	while (is_err)
	{
		if (pFlags.resol == 0)
			throw_params_exception(NO_RESOL, &is_err);
		if (pFlags.ceil_color == 0)
			throw_params_exception(NO_CEIL, &is_err);
		if (pFlags.floor_color == 0)
			throw_params_exception(NO_FLOOR, &is_err);
		if (pFlags.north == 0)
			throw_params_exception(NO_NORTH, &is_err);
		if (pFlags.south == 0)
			throw_params_exception(NO_SOUTH, &is_err);
		if (pFlags.west == 0)
			throw_params_exception(NO_WEST, &is_err);
		if (pFlags.east == 0)
			throw_params_exception(NO_EAST, &is_err);
		if (pFlags.sprite == 0)
			throw_params_exception(NO_SPRITE, &is_err);
	}
	free_all(m_struct);
	exit(0);
}

void	throw_empty_file(t_data *m_struct)
{
	throw_exception(EMPTY_FILE);
	free_all(m_struct);
	exit(0);
}

void	was_params(t_parse_flags parseFlags, t_data *m_struct)
{
	int	is_error;

	is_error = 0;
	if (parseFlags.resol == 0)
		is_error++;
	if (parseFlags.ceil_color == 0)
		is_error++;
	if (parseFlags.floor_color == 0)
		is_error++;
	if (parseFlags.north == 0)
		is_error++;
	if (parseFlags.south == 0)
		is_error++;
	if (parseFlags.west == 0)
		is_error++;
	if (parseFlags.east == 0)
		is_error++;
	if (parseFlags.sprite == 0)
		is_error++;
	if (is_error == 8)
		throw_empty_file(m_struct);
	if (is_error > 0 && is_error < 8)
		throw_params_except(parseFlags, m_struct, is_error);
}
