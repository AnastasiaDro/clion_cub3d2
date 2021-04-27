/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:19:53 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 16:10:53 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		slen;
	int		i;

	i = 0;
	slen = ft_strlen(s);
	new_s = malloc((slen + 1) * sizeof(char));
	if (new_s)
	{
		while (i <= (slen))
		{
			new_s[i] = s[i];
			i++;
		}
	}
	return (new_s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while ((i < dstsize - 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_gstrjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	new_s_flen;

	if (!s1 || !s2)
		return (NULL);
	new_s_flen = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(sizeof(char) * (new_s_flen + 1));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(&newstr[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (c == '\0')
		return (&str[ft_strlen(str)]);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}
