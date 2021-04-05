/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:52:07 by cerebus           #+#    #+#             */
/*   Updated: 2020/10/29 15:52:10 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NOT_END str[i] != '\0'
#define NOT_SPACE ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')

int	ft_atoi(char *str)
{
	int		i;
	int		coef;
	long	result;

	i = 0;
	coef = 1;
	result = 0;
	while (NOT_END && NOT_SPACE)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		coef = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (NOT_END && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += (str[i] - '0') * coef;
		if (coef > 0 && result < 0)
			return (-1);
		if (coef < 0 && result > 0)
			return (0);
		i++;
	}
	return (result);
}
