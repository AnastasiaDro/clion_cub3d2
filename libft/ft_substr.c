/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:50:09 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:08:38 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	calc_sublen(int len, char *s)
{
	int	sublen;

	if (len > (int)ft_strlen(s))
		sublen = ft_strlen(s);
	else
		sublen = len;
	return (sublen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		sublen;
	char		*substr;

	if (!s)
		return (NULL);
	i = 0;
	sublen = 0;
	if (start >= ft_strlen(s))
		substr = malloc(1 * sizeof(char));
	else
	{
		sublen = calc_sublen(len, (char *)&s[start]);
		substr = malloc((sublen + 1) * sizeof(char));
	}
	if (!substr)
		return (NULL);
	while (i < sublen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
