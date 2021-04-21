/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:12:26 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/21 20:41:12 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_hooking.h"
#include "stdio.h"

int	rotate(t_data *m_struct, double rotSpeed, int keycode)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == 123)
		rotSpeed = rotSpeed * (-1);
	oldDirX = m_struct->dirX;
	m_struct->dirX = m_struct->dirX * cos(rotSpeed) \
		- m_struct->dirY * sin(rotSpeed);
	m_struct->dirY = oldDirX * sin(rotSpeed) + m_struct->dirY * cos(rotSpeed);
	oldPlaneX = m_struct->planeX;
	m_struct->planeX = m_struct->planeX * cos(rotSpeed) \
		- m_struct->planeY * sin(rotSpeed);
	m_struct->planeY = oldPlaneX * sin(rotSpeed) \
		+ m_struct->planeY * cos(rotSpeed);
	return (1);
}

int	step_forw_back(t_data *m_struct, double moveSpeed, int keycode)
{
	double	coef;
	char	**map;

	if (keycode == 13)
		coef = 1;
	if (keycode == 1)
		coef = -1;
	map = m_struct->map;
	if (map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x \
		+ coef * m_struct->dirX * moveSpeed)] == '0')
		m_struct->map_player_x += coef * m_struct->dirX * moveSpeed;
	if (map[(int)(m_struct->map_player_y + coef * m_struct->dirY * moveSpeed)] \
		[(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef * m_struct->dirY * moveSpeed;
	return (1);
}

int	step_left_rigth(t_data *m_struct, double moveSpeed, int keycode)
{
	int		coef;
	char	**map;

	if (keycode == 0)
		coef = 1;
	if (keycode == 2)
		coef = -1;
	map = m_struct->map;
	if (map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x \
		+ coef * m_struct->planeX * moveSpeed)] == '0')
		m_struct->map_player_x += coef * m_struct->planeX * moveSpeed;
	if (map[(int)(m_struct->map_player_y + coef * m_struct->planeY \
		* moveSpeed)][(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef * m_struct->planeY * moveSpeed;
	return (1);
}
