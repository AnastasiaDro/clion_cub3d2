/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 22:58:22 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:13:38 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

void	make_color_exception(char *s, t_data *m_struct)
{
	throw_exception(INVALID_FLOOR_COLOR);
	free(s);
	s = NULL;
	free_all(m_struct);
	exit(0);
}

int	go_to_the_next_color(int i, char *str)
{
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && str[i] != ',')
	{
		if ((str[i] != ' ') && !(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	i++;
	while (str[i] == ' ')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	return (i);
}

int	check_color_part(char *str)
{
	int	i;
	int	num_start;
	int	num_length;
	int	color;

	i = 0;
	num_start = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	num_length = i - num_start;
	if (num_length > 3)
		return (-1);
	color = ft_atoi(str);
	if (color > 255)
		return (-1);
	return (color);
}

int	check_color_s_end(char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i])
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

int	get_color(char *s, t_data *m_struct, int *flag)
{
	int		i;
	t_color	*m_color;
	int		color;

	*flag = 1;
	i = 0;
	m_color = malloc(sizeof(t_color));
	while ((s + 1)[i] == ' ')
		i++;
	m_color->r = check_color_part(&(s + 1)[i]);
	if (m_color->r == -1)
		make_color_exception(s, m_struct);
	i = go_to_the_next_color(i, (s + 1));
	parse_line_sect(i, s, m_struct, &m_color->g);
	i = go_to_the_next_color(i, (s + 1));
	parse_line_sect(i, s, m_struct, &m_color->b);
	if (check_color_s_end((s + 1), i) == -1)
		make_color_exception(s, m_struct);
	color = m_color->r * (int)(pow(16, 4)) + \
		m_color->g * (int)(pow(16, 2)) + m_color->b;
	free(s);
	free(m_color);
	return (color);
}
