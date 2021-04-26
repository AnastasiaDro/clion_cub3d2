/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:46:09 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:53:14 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_params.h"

int	set_player_direction(t_data *m_struct, double dirX, double dirY)
{
	m_struct->dir_x = dirX;
	m_struct->dir_y = dirY;
	return (1);
}

int	set_camera_plane(t_data *m_struct, double planeY, double PlaneX)
{
	m_struct->plane_y = planeY;
	m_struct->plane_x = PlaneX;
	return (1);
}

int	set_player_vision(char c, t_data *m_struct)
{
	if (c == 'N')
	{
		set_player_direction(m_struct, 0, -1);
		set_camera_plane(m_struct, 0, -0.66);
		return (1);
	}
	if (c == 'S')
	{
		set_player_direction(m_struct, 0, 1);
		set_camera_plane(m_struct, 0, 0.66);
		return (1);
	}
	if (c == 'E')
	{
		set_player_direction(m_struct, 1, 0);
		set_camera_plane(m_struct, -0.66, 0);
		return (1);
	}
	if (c == 'W')
	{
		set_player_direction(m_struct, -1, 0);
		set_camera_plane(m_struct, 0.66, 0);
		return (1);
	}
	return (0);
}
