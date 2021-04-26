/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:54:12 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:09:07 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	hlen;
	size_t	nlen;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	hlen = ft_strlen(haystack);
	nlen = ft_strlen(needle);
	while (i <= hlen - nlen && i + nlen <= len)
	{
		if (0 == ft_strncmp(&haystack[i], needle, nlen))
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
