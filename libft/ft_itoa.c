/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:55:57 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/16 15:56:01 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (NULL);
	while ((i < dstsize - 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_make_intmin(void)
{
	char *s;

	s = malloc(12 * sizeof(char));
	if (!s)
		return (NULL);
	return (ft_strlcpy(s, "-2147483648", 12));
}

static char	*ft_fill_s(char *s, int n, int i)
{
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
	}
	while (i > 0)
	{
		s[i - 1] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (s);
}

static int	ft_get_capacity(int n)
{
	int nm;
	int num_cap;

	nm = n;
	num_cap = 0;
	while (nm != 0)
	{
		nm = nm / 10;
		num_cap++;
	}
	return (num_cap);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		num_cap;
	int		start;
	int		size;

	num_cap = 0;
	start = 0;
	if (n == -2147483648)
		return (ft_make_intmin());
	num_cap = ft_get_capacity(n);
	size = (n < 1) ? num_cap + 2 : num_cap + 1;
	s = malloc(size * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[start] = '-';
		n = n * (-1);
		start++;
	}
	ft_fill_s(&s[start], n, num_cap);
	s[size - 1] = '\0';
	return (s);
}
