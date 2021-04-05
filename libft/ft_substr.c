/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:50:09 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/23 17:19:58 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
		sublen = (len > ft_strlen(&s[start])) ? ft_strlen(&s[start]) : len;
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
