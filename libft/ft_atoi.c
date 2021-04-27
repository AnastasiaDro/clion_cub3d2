/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:52:07 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:28:21 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	calc_coef(char c)
{
	int	coef;

	if (c == '-')
		coef = -1;
	else
		coef = 1;
	return (coef);
}

int	ft_atoi(char *str)
{
	int		i;
	int		coef;
	long	result;

	i = 0;
	coef = 1;
	result = 0;
	while ((str[i] != '\0' && (str[i] >= '\t' && str[i] <= '\r')) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		coef = calc_coef(str[i]);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
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
