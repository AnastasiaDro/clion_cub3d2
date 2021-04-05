/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:40:37 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/03 13:40:39 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*f_s;
	unsigned char	*s_s;
	size_t			i;
	int				res;

	f_s = (unsigned char *)s1;
	s_s = (unsigned char *)s2;
	i = 0;
	res = 0;
	while (i < n)
	{
		res = *(f_s + i) - *(s_s + i);
		if (*(f_s + i) != *(s_s + i))
			return (res);
		i++;
	}
	return (res);
}
