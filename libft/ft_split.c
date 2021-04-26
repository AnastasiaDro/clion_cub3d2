/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:34:13 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:10:03 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words_num;

	i = 0;
	words_num = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words_num++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (words_num);
}

static char	**ft_free(int arr_num, char **res)
{
	arr_num = arr_num - 1;
	while (arr_num >= 0)
	{
		free(res[arr_num]);
		arr_num--;
	}
	free(res);
	return (NULL);
}

static char	**ft_fill_res(char **res, char const *s, char c, int words_num)
{
	int	i;
	int	start;
	int	end;
	int	arr_num;

	i = 0;
	start = 0;
	end = 0;
	arr_num = 0;
	while (s[i] != '\0' && arr_num < words_num)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		end = i - 1;
		res[arr_num] = ft_substr(s, start, end - start + 1);
		if (!(res[arr_num]))
			return (ft_free(arr_num, res));
		arr_num++;
	}
	res[arr_num] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		words_num;
	char	**res;

	if (!s)
		return (NULL);
	words_num = ft_count_words(s, c);
	res = (char **)malloc((words_num + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_fill_res(res, s, c, words_num));
}
