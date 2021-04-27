/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:12:05 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 16:09:00 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_increase_tail(char **tail, char **buff, int *start, int read_bytes)
{
	char	*tail_tmp;

	tail_tmp = NULL;
	if (*start == 0)
		*start = ft_strlen(*tail);
	else
		*start = *start + read_bytes;
	(*buff)[read_bytes] = '\0';
	tail_tmp = *tail;
	*tail = ft_gstrjoin(*tail, *buff);
	free(tail_tmp);
	if (!(*tail))
	{
		free(*buff);
		return (-1);
	}
	return (1);
}

int	ft_split_n_tail(char *pn, char **tail, char **line)
{
	char	*tmp;

	tmp = NULL;
	*pn = '\0';
	*line = ft_strdup(*tail);
	tmp = *tail;
	*tail = ft_strdup(++pn);
	free(tmp);
	tmp = NULL;
	if (!(*line) || !(*tail))
		return (-1);
	return (1);
}

int	ft_get_from_tail(char **line, char **tail)
{
	*line = ft_strdup(*tail);
	free(*tail);
	*tail = NULL;
	if (!(*line))
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*tail;
	char		*buff;
	int			read_bytes;
	char		*pn;
	int			start;

	read_bytes = -2;
	start = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line || (read(fd, NULL, 0) == -1) || BUFFER_SIZE < 1 || !(buff))
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	if (!tail)
		tail = ft_strdup("");
	*line = NULL;
	while (!find_char(&pn, &tail[start]) && m_read(&read_bytes, fd, buff))
	{
		if (ft_increase_tail(&tail, &buff, &start, read_bytes) == -1)
			return (-1);
	}
	free(buff);
	if (pn)
		return (ft_split_n_tail(pn, &tail, line));
	else
		return (ft_get_from_tail(line, &tail));
}
