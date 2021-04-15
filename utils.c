//
// Created by  Anastasia on 15.04.2021.
//
#include "utils.h"

int ft_strchr_index(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

