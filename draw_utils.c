/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:05:36 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/21 20:10:19 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_cub_utils.h"

int	draw_background(int y, int limit, int color, t_data *m_struct)
{
	int	x;

	while (y < limit)
	{
		x = 0;
		while (x < m_struct->params->screen_width)
		{
			cerebus_mlx_pixel_put(m_struct, x, y, color);
			x++;
		}
		y++;
	}
	return (y);
}

int	draw_floor_ceil(t_data *m_struct, int screen_higth, int screen_width)
{
	int	half;
	int	y;
	int	floor_color;
	int	ceiling_color;

	half = screen_higth / 2;
	floor_color = m_struct->params->floor_color;
	ceiling_color = m_struct->params->ceil_color;
	y = draw_background(y, half, ceiling_color, m_struct);
	draw_background(y, screen_higth, floor_color, m_struct);
	return (0);
}
