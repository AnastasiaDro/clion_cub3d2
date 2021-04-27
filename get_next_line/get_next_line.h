/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:15:29 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 16:09:58 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>

int		get_next_line(int fd, char **line);

int		ft_increase_tail(char **tail, char **buff, int *start, int read_bytes);

int		ft_split_n_tail(char *pn, char **tail, char **line);

int		ft_get_from_tail(char **line, char **tail);

int		m_read(int *read_bytes, int fd, char *buff);

char	*find_char(char **pn, char *s);

char	*ft_gstrjoin(char *s1, char *s2);

char	*ft_strchr(const char *s, int c);

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
