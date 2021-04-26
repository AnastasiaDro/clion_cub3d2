/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_z_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 01:57:00 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 01:58:26 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "exceptions.h"

int	init_z_buffer(t_data *m_struct)
{
	m_struct->z_buffer = malloc(m_struct->params->screen_w * sizeof(double));
	if (!m_struct->z_buffer)
	{
		throw_exception(MALLOC_ERROR);
		free_all(m_struct);
	}
	return (1);
}
