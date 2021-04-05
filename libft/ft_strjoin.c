/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:10:23 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/15 16:10:39 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	src_len;
	size_t	new_s_flen;

	if (!s1 || !s2)
		return (NULL);
	new_s_flen = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(new_s_flen * sizeof(char));
	if (!newstr)
		return (NULL);
	src_len = ft_strlcpy(newstr, s1, new_s_flen);
	src_len = ft_strlcpy(&newstr[src_len], s2, new_s_flen - src_len);
	newstr[new_s_flen - 1] = '\0';
	return (newstr);
}
