/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_sect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:15:28 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:15:51 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

void	parse_line_sect(int i, char *s, t_data *m_struct, int *color_part)
{
	if (i == -1)
		make_color_exception(s, m_struct);
	*color_part = check_color_part(&(s + 1)[i]);
	if (*color_part == -1)
		make_color_exception(s, m_struct);
}
