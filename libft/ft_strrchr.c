/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:09:59 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 00:13:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		len;

	p = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (p[len] == c)
			return (&p[len]);
		len--;
	}
	return (NULL);
}
