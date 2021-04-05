/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:48:24 by marvin            #+#    #+#             */
/*   Updated: 2020/11/02 11:48:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		*(d + i) = *(s + i);
		if (s[i] == (unsigned char)c)
		{
			return ((void *)(d + i + 1));
		}
		i++;
	}
	return (NULL);
}
