/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_wrap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:08:43 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 16:10:00 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	m_read(int *read_bytes, int fd, char *buff)
{
	*read_bytes = read(fd, buff, BUFFER_SIZE);
	return (*read_bytes);
}

char	*find_char(char **pn, char *s)
{
	*pn = ft_strchr(s, '\n');
	return (*pn);
}
