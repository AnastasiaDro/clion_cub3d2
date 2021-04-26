/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:19:02 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:23:15 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall_utils.h"
#include "draw_utils.h"

void	calc_line_height(t_wall *wall, t_ray *ray, t_data *m_struct)
{
	double	coef;
	double	h;
	double	w;

	h = m_struct->params->screen_h;
	w = m_struct->params->screen_w;
	coef = w / h * 0.77;
	wall->line_height = (int)(h / ray->perpWallDist * coef);
}

void	calc_sart_pixels(t_wall *wall, t_data *m_struct)
{
	int	screen_h;

	screen_h = m_struct->params->screen_h;
	wall->drawStart = -(wall->line_height) / 2 + screen_h / 2;
	if (wall->drawStart < 0)
		wall->drawStart = 0;
	wall->draw_end = wall->line_height / 2 + screen_h / 2;
	if (wall->draw_end >= screen_h)
		wall->draw_end = screen_h - 1;
}

void	calc_wall_x(t_wall *wall, t_ray *ray, t_data *m_struct)
{
	if (m_struct->side == 0)
		wall->wallX = m_struct->map_player_y + ray->perpWallDist * ray->DirY;
	else
		wall->wallX = m_struct->map_player_x + ray->perpWallDist * ray->DirX;
	wall->wallX -= floor(wall->wallX);
}

void	draw_wall_line(t_wall *wall, t_data *m_struct, t_txdraw *tdraw, int g)
{
	double	step;
	double	texPos;
	double	h;
	int		y;
	int		color;

	h = m_struct->params->screen_h;
	step = 1.0 * tdraw->textu->height / wall->line_height;
	y = wall->drawStart;
	texPos = (wall->drawStart - h / 2 + (double)wall->line_height / 2) * step;
	while (y < wall->draw_end)
	{
		tdraw->texY = (int) texPos;
		texPos += step;
		color = textu_mlx_pixel_get(tdraw->textu, tdraw->texX, tdraw->texY);
		cerebus_mlx_pixel_put(m_struct, g, y, color);
		y++;
	}
}
