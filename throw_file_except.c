/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_file_except.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:12:01 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:12:02 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exceptions.h"

void	throw_file_except(t_data *m_struct)
{
	throw_exception(INVALID_FILE);
	free_all(m_struct);
	exit(0);
}
