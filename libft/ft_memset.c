/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:17:31 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/01 12:17:33 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	m_char;
	char			*p;

	i = 0;
	m_char = (unsigned char)c;
	p = b;
	while (i < len)
	{
		*(p + i) = m_char;
		i++;
	}
	return (b);
}
