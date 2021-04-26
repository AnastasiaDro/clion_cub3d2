/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:58:22 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 19:11:13 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_resolution.h"

int	get_num_length(char *str, int *i, int *num_start)
{
	while (str[*i] && (str[*i] == ' '))
		(*i)++;
	*num_start = *i;
	while (str[*i] >= '0' && str[*i] <='9')
		(*i)++;
	return ((*i) - (*num_start));
}

int	set_max_resolution(t_data *m_struct, char *s, int max_w, int max_h)
{
	m_struct->params->screen_w = max_w;
	m_struct->params->screen_h = max_h;
	init_z_buffer(m_struct);
	free(s);
	s = NULL;
	return (1);
}

void	throw_resol_except(char **s, t_data *m_struct)
{
	throw_exception(INVALID_RESOLUTION);
	free(*s);
	*s = NULL;
	free_all(m_struct);
	exit(0);
}

int	check_s_end(char *str, int i)
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

int	parse_resolution(char *s, t_data *m_struct, int *flag)
{
	int	num_start;
	int	num_length;
	int	i;
	int	mx_w;
	int	mx_h;

	*flag = 1;
	i = 0;
	num_start = 0;
	num_length = get_num_length(s + 1, &i, &num_start);
	mlx_get_screen_size(&mx_w, &mx_h);
	if (num_length > MAX_WIDTH_NUM_LENGTH)
		return (set_max_resolution(m_struct, s, mx_w, mx_h));
	m_struct->params->screen_w = ft_atoi(s + 1);
	num_length = get_num_length(s + 1, &i, &num_start);
	if (num_length > MAX_HEIGHT_NUM_LENGTH)
		return (set_max_resolution(m_struct, s, mx_w, mx_h));
	m_struct->params->screen_h = ft_atoi(&(s + 1)[num_start]);
	if (m_struct->params->screen_w > mx_w || m_struct->params->screen_h > mx_h)
		return (set_max_resolution(m_struct, s, mx_w, mx_h));
	if (m_struct->params->screen_w <= 0 || m_struct->params->screen_h <= 0 \
		|| check_s_end(s + 1, i) == -1)
		throw_resol_except(&s, m_struct);
	free(s);
	return (init_z_buffer(m_struct));
}
