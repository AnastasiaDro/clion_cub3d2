/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:05:36 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 17:08:01 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "sprites_utils.h"

void	cerebus_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_background(int y, int limit, int color, t_data *m_struct)
{
	int	x;

	while (y < limit)
	{
		x = 0;
		while (x < m_struct->params->screen_w)
		{
			cerebus_mlx_pixel_put(m_struct, x, y, color);
			x++;
		}
		y++;
	}
	return (y);
}

int	draw_floor_ceil(t_data *m_struct, int screen_higth)
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

int	sprite_mlx_pixel_get(t_spr_info *spr_info, int x, int y)
{
	int		color;
	char	*dst;

	dst = spr_info->addr + (y * spr_info->line_length + \
			x * (spr_info->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}

int	textu_mlx_pixel_get(t_textu *textu, int x, int y)
{
	int		color;
	char	*dst;

	dst = textu->addr + (y * textu->line_length + \
			x * (textu->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}
