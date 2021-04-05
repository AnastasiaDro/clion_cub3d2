/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 08:06:15 by marvin            #+#    #+#             */
/*   Updated: 2020/11/03 08:06:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	c_ch;
	size_t			i;

	i = 0;
	p_s = (unsigned char *)s;
	c_ch = (unsigned char)c;
	while (i < n)
	{
		if (*(p_s + i) == c_ch)
			return (p_s + i);
		else
			(i++);
	}
	return (NULL);
}
