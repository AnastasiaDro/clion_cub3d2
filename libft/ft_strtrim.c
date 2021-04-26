/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:09:39 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:08:53 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_compare(char check_ch, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (check_ch == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_compare(s1[start], set) && s1[start] != '\0')
		start++;
	if (!s1[start])
		return (ft_strdup("\0"));
	while (ft_compare(s1[end], set) && (end > 0))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
