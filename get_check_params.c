/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_check_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 02:00:52 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:01:03 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "parser_utils.h"
#include "parse_resolution.h"
#include "colors.h"

int	get_check_params(char *s, t_data *m_struct, t_parse_flags *parse_f)
{
	t_params	*params;

	params = m_struct->params;
	if (*s == 'R' && !parse_f->resol)
		return (parse_resolution(s, m_struct, &parse_f->resol));
	if (*s == 'F' && !parse_f->floor_color)
	{
		params->floor_color = get_color(s, m_struct, &parse_f->floor_color);
		return (1);
	}
	if (*s == 'C' && !parse_f->ceil_color)
	{
		params->ceil_color = get_color(s, m_struct, &parse_f->ceil_color);
		return (1);
	}
	return (0);
}
