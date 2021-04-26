/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:53:11 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 17:10:28 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_sprites.h"
#include "draw_utils.h"
#include "sortSprites.h"

void	set_sprite_data(t_data *m_struct)
{
	t_sprite	*sprite_lst;
	int			m_x;
	int			m_y;

	m_x = m_struct->map_player_x;
	m_y = m_struct->map_player_y;
	sprite_lst = *(m_struct->sprite_info->sprite_lst);
	while (sprite_lst != NULL)
	{
		sprite_lst->dist = ((m_x - sprite_lst->x) * (m_x - sprite_lst->x) + (m_y \
				- sprite_lst->y) * (m_y - sprite_lst->y));
		sprite_lst = sprite_lst->next;
	}
	sprite_lst = *(m_struct->sprite_info->sprite_lst);
	sortSprites(&sprite_lst);
}

void	set_sprite_pos(t_spr_draw *spr_drw, t_sprite *spr_lst, t_data *m_struct)
{
	double	inv_det;
	int		screen_w;
	double	pl_x;
	double	pl_y;

	screen_w = m_struct->params->screen_w;
	pl_x = m_struct->plane_x;
	pl_y = m_struct->plane_y;
	spr_drw->s_x = spr_lst->x - m_struct->map_player_x;
	spr_drw->s_y = spr_lst->y - m_struct->map_player_y;
	inv_det = 1.0 / (pl_x * m_struct->dir_y - m_struct->dir_x * pl_y);
	spr_drw->transf_x = inv_det * (m_struct->dir_y * spr_drw->s_x \
		- m_struct->dir_x * spr_drw->s_y);
	spr_drw->transf_y = inv_det * (-pl_y * spr_drw->s_x + pl_x * spr_drw->s_y);
	spr_drw->screen_x = (int)((screen_w * 0.5) * \
		(1 + spr_drw->transf_x / spr_drw->transf_y));
}

void	set_s_draw_limits(t_spr_draw *spr_draw, t_data *m_struct, double coef)
{
	int	screen_h;
	int	screen_w;

	screen_h = m_struct->params->screen_h;
	screen_w = m_struct->params->screen_w;
	spr_draw->h = fabs(screen_h / (spr_draw->transf_y) * coef);
	spr_draw->start_y = (int)round(-spr_draw->h / 2 + (double)screen_h / 2);
	if (spr_draw->start_y < 0)
		spr_draw->start_y = 0;
	spr_draw->end_y = (int)round(spr_draw->h / 2 + (double)screen_h / 2);
	if (spr_draw->end_y >= screen_h)
		spr_draw->end_y = screen_h - 1;
	spr_draw->w = fabs((screen_h / (spr_draw->transf_y) * coef));
	spr_draw->start_x = (int)round(-spr_draw->w / 2 + spr_draw->screen_x);
	if (spr_draw->start_x < 0)
		spr_draw->start_x = 0;
	spr_draw->end_x = (int)round(spr_draw->w / 2 + spr_draw->screen_x);
	if (spr_draw->end_x >= screen_w)
		spr_draw->end_x = screen_w - 1;
}

void	draw_s_line(t_spr_draw *spr_draw, t_data *m_struct, int l_i, int tex_x)
{
	int	y;
	int	tex_y;
	int	d;
	int	color;
	int	screen_w;

	y = spr_draw->start_y;
	screen_w = m_struct->params->screen_w;
	while (y < spr_draw->end_y)
	{
		d = (y) * 256 - m_struct->params->screen_h * 128 + \
			spr_draw->h * 128;
		tex_y = ((d * m_struct->sprite_info->h) / spr_draw->h) / 256;
		color = sprite_mlx_pixel_get(m_struct->sprite_info, tex_x, tex_y);
		if ((color & 0xFFFFFF) != 0)
			cerebus_mlx_pixel_put(m_struct, screen_w - l_i, y, color);
		y++;
	}
}

void	draw_sprite(t_spr_draw *spr_draw, t_data *m_struct)
{
	int		line_i;
	int		tex_x;
	double	multi;
	int		sprite_w;

	line_i = spr_draw->start_x;
	sprite_w = m_struct->sprite_info->w;
	while (line_i < spr_draw->end_x)
	{
		multi = (line_i - (-spr_draw->w / 2 + spr_draw->screen_x));
		tex_x = (int)(256 * multi * sprite_w / spr_draw->w) / 256;
		if (spr_draw->transf_y > 0 && (spr_draw->end_x - line_i) > 0 && \
			(spr_draw->end_x - line_i) < m_struct->params->screen_w \
 && spr_draw->transf_y < m_struct->z_buffer[line_i])
		{
			draw_s_line(spr_draw, m_struct, line_i, tex_x);
		}
		line_i++;
	}
}
