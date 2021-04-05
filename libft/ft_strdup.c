/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:58:57 by marvin            #+#    #+#             */
/*   Updated: 2020/11/13 10:59:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		slen;

	slen = ft_strlen(s);
	new_s = malloc((slen + 1) * sizeof(char));
	if (new_s)
		new_s = (char *)ft_memcpy(new_s, s, (slen + 1));
	return (new_s);
}
