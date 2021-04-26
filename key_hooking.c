/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:12:26 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 14:29:32 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_hooking.h"
#include "stdio.h"

int	rotate(t_data *m_struct, double rot_speed, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 123)
		rot_speed = rot_speed * (-1);
	old_dir_x = m_struct->dir_x;
	m_struct->dir_x = m_struct->dir_x * cos(rot_speed) \
			- m_struct->dir_y * sin(rot_speed);
	m_struct->dir_y = old_dir_x * sin(rot_speed) + \
		m_struct->dir_y * cos(rot_speed);
	old_plane_x = m_struct->plane_x;
	m_struct->plane_x = m_struct->plane_x * cos(rot_speed) \
		- m_struct->plane_y * sin(rot_speed);
	m_struct->plane_y = old_plane_x * sin(rot_speed) \
		+ m_struct->plane_y * cos(rot_speed);
	return (1);
}

int	step_forw_back(t_data *m_struct, double move_speed, int keycode)
{
	double	coef;
	char	**map;

	if (keycode == 13)
		coef = 1;
	if (keycode == 1)
		coef = -1;
	map = m_struct->map;
	if (map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x \
		+ coef * m_struct->dir_x * move_speed)] == '0')
		m_struct->map_player_x += coef * m_struct->dir_x * move_speed;
	if (map[(int)(m_struct->map_player_y + coef * \
		m_struct->dir_y * move_speed)][(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef * m_struct->dir_y * move_speed;
	return (1);
}

int	step_left_rigth(t_data *m_struct, double move_speed, int keycode)
{
	int		coef;
	char	**map;

	if (keycode == 0)
		coef = 1;
	if (keycode == 2)
		coef = -1;
	map = m_struct->map;
	if (map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x \
		+ coef * m_struct->plane_x * move_speed)] == '0')
		m_struct->map_player_x += coef * m_struct->plane_x * move_speed;
	if (map[(int)(m_struct->map_player_y + coef * m_struct->plane_y \
			* move_speed)][(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef * m_struct->plane_y * move_speed;
	return (1);
}
